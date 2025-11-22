/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_keys_to_expand.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 23:05:14 by valero            #+#    #+#             */
/*   Updated: 2025/11/22 15:18:24 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expandable_object.h"
#include "expandable_object_internal.h"

static bool	ft_is_key_char(char key_char, bool is_first);
static bool	ft_is_special_key_char(char key_char);
static void	ft_extract_keys(
				char *token_section, int *coords,
				t_expandable_section *exp_keys);
static void	ft_track_keys(
				int *section_idx, char *token_section,
				int *coords, t_expandable_section *exp_keys);

/**
 * # ft_find_keys_to_expand
 *
 * Filtra *apenas* as partes realmente expansíveis.
 *
 * Lógica:
 * - Itera todas as seções encontradas.
 * - Usa `ft_extract_keys` para extrair chaves ($X, ${var}, $?).
 * - Converte listas para arrays.
 * - Destrói estrutura original, retornando só o filtrado.
 *
 * Função essencial: separa “seções com potencial” de “chaves reais”.
 */
t_expandable_section	*ft_find_keys_to_expand(
		t_expandable_section *expandable_sections)
{
	t_expandable_section	*exp_keys;
	t_linkedlist			*list;
	t_linkedlist			*coord_list;
	int						idx;

	exp_keys = ft_create_expandable_sections();
	if (!exp_keys)
		return (expandable_sections->destroy(&expandable_sections));
	idx = -1;
	while (expandable_sections->array[++idx])
		ft_extract_keys(expandable_sections->array[idx],
			expandable_sections->coord_array[idx], exp_keys);
	list = exp_keys->list;
	coord_list = exp_keys->coord_list;
	exp_keys->array = (char **)list->to_array(
			list, (void *(*)(void *content))ft_strdup, free);
	exp_keys->coord_array = (int **)coord_list->to_array(
			coord_list, (void *(*)(void *content))ft_coord_dup, free);
	expandable_sections->destroy(&expandable_sections);
	return (exp_keys);
}

/**
 * # ft_extract_keys
 *
 * Extrai chaves de expansão dentro de uma seção.
 *
 * Lógica:
 * - Percorre `token_section`.
 * - Detecta `$`.
 *   - Se o caractere seguinte for especial → chave curta (`$1`, `$?`).
 *   - Senão, chama `ft_track_keys` para chaves longas ($VAR).
 * - Cria coordenadas corretas relativas à string original.
 */
static void	ft_extract_keys(
		char *token_section, int *coords,
		t_expandable_section *exp_keys)
{
	int	section_idx;
	int	*new_coord;

	section_idx = -1;
	while (token_section[++section_idx])
	{
		if (ft_is_special_char(token_section, section_idx, "$"))
		{
			if (ft_is_special_key_char(token_section[section_idx + 1]))
			{
				exp_keys->list->push(exp_keys->list,
					ft_substr(token_section, section_idx, 2));
				new_coord = ft_new_coord(
						coords[0] + section_idx, coords[0] + section_idx + 1);
				exp_keys->coord_list->push(exp_keys->coord_list, new_coord);
				section_idx++;
			}
			else
				ft_track_keys(&section_idx, token_section, coords, exp_keys);
		}
	}
}

/**
 * # ft_track_keys
 *
 * Lida com chaves do tipo `$VAR_NAME`.
 *
 * Lógica:
 * - Avança caracter por caracter verificando `ft_is_key_char`.
 * - Armazena substring completa.
 * - Cria coordenada relativa ao token original.
 *
 * É onde ocorre a lógica mais sensível do parsing de variáveis.
 */
static void	ft_track_keys(
		int *section_idx, char *token_section,
		int *coords, t_expandable_section *exp_keys)
{
	int	key_idx;
	int	*new_coord;

	(*section_idx)++;
	key_idx = (*section_idx);
	while (token_section[key_idx] && ft_is_key_char(
			token_section[key_idx], (*section_idx) == key_idx))
		key_idx++;
	exp_keys->list->push(exp_keys->list,
		ft_substr(token_section,
			*section_idx - 1, key_idx - (*section_idx - 1)));
	new_coord = ft_new_coord(
			coords[0] + (*section_idx) - 1, coords[0] + key_idx - 1);
	exp_keys->coord_list->push(exp_keys->coord_list, new_coord);
	*section_idx = key_idx - 1;
}

/**
 * # ft_is_key_char
 *
 * Verifica se o caractere faz parte de um nome de variável.
 *
 * Regras:
 * - Primeiro char: letra ou `_`.
 * - Restante: alfanumérico ou `_`.
 */
static bool	ft_is_key_char(char key_char, bool is_first)
{
	if ((is_first && (ft_isalpha(key_char) || key_char == '_'))
		|| (!is_first && (ft_isalnum(key_char) || key_char == '_')))
		return (true);
	return (false);
}

/**
 * # ft_is_special_key_char
 *
 * Verifica chaves especiais de um caractere só:
 * $, ?, #, *, @, -, dígitos, etc.
 */
static bool	ft_is_special_key_char(char key_char)
{
	if (ft_isdigit(key_char) || ft_strchr("$!?#*@-", key_char))
		return (true);
	return (false);
}
