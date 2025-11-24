/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 14:56:21 by brunofer          #+#    #+#             */
/*   Updated: 2025/11/24 20:31:16 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer_internal.h"
#include "tokenizer.h"

static void					*ft_destroy_tokenized_prompt(
								t_tokenized_prompt	**self_ref);
static t_tokenized_prompt	*ft_create_tokenized_prompt(
								const char *prompt,
								t_splited_prompt **splited,
								t_expander_callbacks callbacks);

/**
*  # ft_tokenizer
*
* Função de alto nível. Une splitter + tokenizer.
*
* Lógica:
* - Chama ft_splitter() para dividir a linha bruta em chunks.
* - Prepara callbacks de expansão (variáveis e glob).
* - Cria a estrutura final via ft_create_tokenized_prompt().
*
* Responsabilidade:
* É a entrada principal. Entrega um t_tokenized_prompt completamente
* preparado para a fase de expansão.
*/
t_tokenized_prompt	*ft_tokenizer(
						const char *prompt,
						t_expand_var_clbk expand_var,
						t_expand_glob_clbk expand_glob)
{
	t_splited_prompt		*splited;
	t_tokenized_prompt		*tokenized_prompt;
	t_expander_callbacks	callbacks;

	splited = ft_splitter(prompt);
	if (!splited)
		return (NULL);
	callbacks.expand_glob = expand_glob;
	callbacks.expand_var = expand_var;
	tokenized_prompt = ft_create_tokenized_prompt(prompt, &splited, callbacks);
	if (!tokenized_prompt)
		return (NULL);
	return (tokenized_prompt);
}

/**
*  # ft_create_tokenized_prompt
*
* Constrói t_tokenized_prompt a partir do resultado do splitter.
*
* Lógica:
* - Aloca a estrutura principal.
* - Copia a prompt original (para debug e reconstruções).
* - Cria o array de tokens com tamanho exato.
* - Percorre o splitter de trás para frente:
*       - Para cada chunk, cria um token via ft_tokenize().
*       - Passa coordenadas e callbacks de expansão.
* - Em caso de erro: destrói tudo com segurança.
* - Associa o callback destroy().
*
* Papel:
* Converter cada substring do splitter em um token completo,
* preservando posição, tipos e metadados necessários.
*/
static t_tokenized_prompt	*ft_create_tokenized_prompt(
								const char *prompt,
								t_splited_prompt **split,
								t_expander_callbacks callbacks)
{
	t_tokenized_prompt		*tk_prompt;
	t_token					**curr_token;

	tk_prompt = ft_calloc(1, sizeof(t_tokenized_prompt));
	if (!tk_prompt)
		return (NULL);
	tk_prompt->size = (*split)->len;
	tk_prompt->original_prompt = (const char *)ft_strdup(prompt);
	tk_prompt->tokens = ft_calloc((*split)->len + 1, sizeof(t_token *));
	while (--(*split)->len >= 0)
	{
		curr_token = &tk_prompt->tokens[(*split)->len];
		*curr_token = ft_tokenize((*split)->chuncks[(*split)->len],
				(*split)->len, (*split)->coords[(*split)->len], callbacks);
		if (!*curr_token)
		{
			(*split)->destroy(split);
			return (ft_destroy_tokenized_prompt(&tk_prompt));
		}
	}
	(*split)->destroy(split);
	tk_prompt->destroy = ft_destroy_tokenized_prompt;
	return (tk_prompt);
}

/**
*  # ft_destroy_tokenized_prompt
*
* Destrutor completo da estrutura t_tokenized_prompt.
*
* Lógica:
* - Libera a prompt original copiada.
* - Percorre o vetor de tokens em ordem reversa:
*       - Para cada token, chama token->destroy().
* - Libera o vetor de tokens.
* - Libera a própria estrutura.
* - Zera o ponteiro externo.
*
* Papel:
* Garantir limpeza total da árvore de tokens,
* evitando qualquer vazamento de memória.
*/
static void	*ft_destroy_tokenized_prompt(t_tokenized_prompt	**self_ref)
{
	t_tokenized_prompt	*self;

	if (!self_ref || !*self_ref)
		return (NULL);
	self = *self_ref;
	if (self->original_prompt)
		free((char *)self->original_prompt);
	if (self->tokens)
	{
		while (--self->size >= 0)
			if (self->tokens[self->size])
				self->tokens[self->size]->destroy(&self->tokens[self->size]);
		free(self->tokens);
	}
	free(self);
	*self_ref = NULL;
	return (NULL);
}
