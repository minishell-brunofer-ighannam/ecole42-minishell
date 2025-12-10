/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 19:09:42 by valero            #+#    #+#             */
/*   Updated: 2025/12/10 12:52:50 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize_internal.h"
#include "tokenize.h"

static void	ft_build_chuncks(t_token *token, t_linkedlist_array *ht_env);
static char	*ft_expand_globs(t_token *token);

/**
 * # ft_build_expansion
 *
 * Função central da expansão.
 *
 * Lógica:
 * - Se já existe last_build → retorna cópia.
 * - Se não é expansível → devolve token como está.
 * - ft_build_chuncks: expande variáveis detectadas.
 * - ft_merge_expansion: junta partes não-expandidas + expandidas.
 * - ft_expand_globs: se contiver globs, tenta expandir.
 * - ft_build_expansion_result: remove aspas externas e monta final.
 * - Guarda em last_build para futuras chamadas.
 */
t_expansion_build	*ft_build_expansion(
						t_token *token,
						t_linkedlist_array *ht_env)
{
	t_expansion_build	*expansion_build;
	char				*glob_input;

	if (token->last_build)
		return (ft_expansion_build_dup(token->last_build));
	if (!token->expandable_object)
		return (ft_build_expansion_result(token, NULL));
	ft_build_chuncks(token, ht_env);
	ft_merge_expansion(token);
	glob_input = ft_expand_globs(token);
	expansion_build = ft_build_expansion_result(token, glob_input);
	if (!expansion_build)
		return (NULL);
	token->last_build = ft_expansion_build_dup(expansion_build);
	if (!token->last_build)
	{
		free(glob_input);
		expansion_build->destroy(&expansion_build);
		return (NULL);
	}
	free(glob_input);
	return (expansion_build);
}

/**
 * # ft_build_chuncks
 *
 * Expande todas as variáveis encontradas no token.
 *
 * Lógica:
 * - Conta quantas keys expansíveis existem.
 * - Aloca expanded_chuncks.
 * - Para cada key → chama expand_var().
 */
static void	ft_build_chuncks(t_token *token, t_linkedlist_array *ht_env)
{
	char				**keys;
	int					len_keys;
	t_expandable_object	*object;

	if (!token->expandable_object->expandable_keys || !token->expand_var)
		return ;
	object = token->expandable_object;
	keys = object->expandable_keys;
	len_keys = 0;
	while (keys[len_keys])
		len_keys++;
	object->expanded_chuncks = ft_calloc(len_keys + 1, sizeof(char *));
	len_keys = -1;
	while (keys[++len_keys])
		object->expanded_chuncks[len_keys] = token->expand_var(
				keys[len_keys], ht_env);
}

/**
 * # ft_create_expanded_value
 *
 * Calcula o tamanho final após substituir variáveis.
 *
 * Lógica:
 * - Começa com tamanho original.
 * - Subtrai trechos ocupados pelas variáveis.
 * - Soma tamanhos das strings expandidas.
 * - Aloca expanded_value com tamanho final.
 */
int	ft_create_expanded_value(t_token *token)
{
	int					idx;
	int					value_len;
	int					**coords;
	char				**chuncks;
	t_expandable_object	*object;

	object = token->expandable_object;
	value_len = ft_strlen(token->value);
	coords = object->expandable_coord_keys;
	idx = -1;
	while (coords[++idx])
		value_len -= coords[idx][1] - coords[idx][0] + 1;
	chuncks = object->expanded_chuncks;
	idx = -1;
	while (chuncks[++idx])
		value_len += ft_strlen(chuncks[idx]);
	object->expanded_value = ft_calloc(value_len + 1, sizeof(char));
	return (value_len);
}

/**
 * # ft_expand_globs
 *
 * Aplica expansão glob se houver padrões (* ? []).
 *
 * Lógica:
 * - Usa expanded_value se existir; senão usa original_value.
 * - Se houver globs:
 *   - Executa expand_glob() (callback externo).
 *   - Converte matriz de strings em uma única string
 *     separada por espaços via ft_normilize_char_matrix().
 * - Retorna copia do input usado.
 */
static char	*ft_expand_globs(t_token *token)
{
	t_expandable_object	*object;
	char				*glob_input;

	object = token->expandable_object;
	if (object->expanded_value)
		glob_input = ft_strdup(object->expanded_value);
	else
		glob_input = ft_strdup(object->original_value);
	if (object->has_globs && token->expand_glob)
		object->expanded_glob_value = ft_normilize_char_matrix(
				token->expand_glob(glob_input));
	return (glob_input);
}
