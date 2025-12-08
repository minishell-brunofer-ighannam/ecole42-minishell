/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 13:58:37 by brunofer          #+#    #+#             */
/*   Updated: 2025/12/08 15:33:43 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZE_H
# define TOKENIZE_H

# include <stdbool.h>
# include "./expandable_object/expandable_object.h"
# include "../../../data_structures/data_structures.h"

/**
 * # t_token_type
 *
 * Enum compacto que representa tipos de tokens.
 * Cada item combina chars usando bit-shifts para permitir
 * identificação rápida e comparação direta por inteiro.
 *
 * Lógica:
 * - Tokens de 1 char usam diretamente o próprio caractere.
 * - Tokens de 2 chars usam (c1 << 8 | c2).
 * - TOKEN_UNKNOWN usa 'u''n''k' empacotado como inteiro.
 */
typedef enum e_token_type			t_token_type;
enum e_token_type
{
	TOKEN_UNKNOWN = 'u' << 16 | 'n' << 8 | 'k',
	TOKEN_CMD = 'c' << 16 | 'm' << 8 | 'd',
	TOKEN_ARG = 'a' << 16 | 'r' << 8 | 'g',
	TOKEN_PIPE = '|',
	TOKEN_OR = '|' << 8 | '|',
	TOKEN_AND = '&' << 8 | '&',
	TOKEN_SEMICOLON = ';',
	TOKEN_BACKGROUND = '&',
	TOKEN_PAREN_OPEN = '(',
	TOKEN_PAREN_CLOSE = ')',
	TOKEN_REDIRECT_IN = '<',
	TOKEN_REDIRECT_OUT = '>',
	TOKEN_HERE_DOC_IN = '<' << 8 | '<',
	TOKEN_APPEND_OUT = '>' << 8 | '>',
	TOKEN_REDIRECT_IN_OUT = '<' << 8 | '>',
	TOKEN_REDIRECT_FORCE_OUT = '>' << 8 | '|',
	TOKEN_REDIRECT_ERR_OUT = '2' << 8 | '>',
	TOKEN_REDIRECT_OUT_ERR = '&' << 8 | '>',
	TOKEN_REDIRECT_OUT_MERGE = '>' << 8 | '&',
	TOKEN_END = '\0'
};

/**
 * # t_expansion_build
 *
 * Armazena o resultado final de uma expansão de variável/glob.
 * Contém:
 * - glob_error: mensagem se falha na expansão de glob.
 * - token_expanded: token final sem aspas e com expansões aplicadas.
 * - destroy: libera a estrutura.
 */
typedef struct s_expansion_build	t_expansion_build;
struct s_expansion_build
{
	char	*glob_error;
	char	*token_expanded;
	void	*(*destroy)(t_expansion_build **self_ref);
};

/**
 * # t_token
 *
 * Representa um token já classificado e apto a expansão.
 * Campos:
 * - value: string original do token.
 * - type: tipo classificado via ft_get_token_type().
 * - position: índice do token na linha original.
 * - coord_in_src: coordenadas de início/fim na string original.
 * - sintaxe_error: erro sintático detectado.
 * - feature_out_of_scope: indica recursos ainda não suportados.
 * - last_build: cache da expansão realizada (para evitar refazer).
 * - expand_var: callback para expansão de variáveis.
 * - expand_glob: callback para expansão glob.
 * - build_expansion: função que executa toda a lógica de expansão.
 * - destroy: destrói o token.
 * - expandable_object: dados sobre o que pode ser expandido.
 */
typedef struct s_token				t_token;
struct s_token
{
	const char			*value;
	t_expansion_build	*last_build;
	t_token_type		type;
	int					position;
	int					*coord_in_src;
	bool				sintaxe_error;
	bool				feature_out_of_scope;
	char				*(*remove_quotes)(t_token *self);
	char				*(*expand_var)(
			const char *token, t_linkedlist_array *ht_env);
	char				**(*expand_glob)(const char *token);
	t_expansion_build	*(*build_expansion)(
			t_token *self, t_linkedlist_array *ht_env);
	void				*(*destroy)(t_token **self_ref);
	t_expandable_object	*expandable_object;
};

typedef char						*(*t_expand_var_clbk)(const char *token,
										t_linkedlist_array *ht_env);
typedef char						**(*t_expand_glob_clbk)(
										const char *token);
/**
 * # t_expander_callbacks
 *
 * Guarda os callbacks necessários:
 * - expand_var: variável → string expandida
 * - expand_glob: glob → lista de strings
 */
typedef struct s_expander_callbacks	t_expander_callbacks;
struct s_expander_callbacks
{
	t_expand_var_clbk	expand_var;
	t_expand_glob_clbk	expand_glob;
};

t_token					*ft_tokenize(
							const char *chunck,
							int idx,
							int *coord_in_src,
							t_expander_callbacks callbacks);

t_expander_callbacks	ft_create_expander_callbacks(
							t_expand_var_clbk	expand_var,
							t_expand_glob_clbk	expand_glob);

#endif
