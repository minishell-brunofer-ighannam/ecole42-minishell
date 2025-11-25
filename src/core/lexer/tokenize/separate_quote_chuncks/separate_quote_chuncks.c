/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separate_quote_chuncks.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 20:10:11 by valero            #+#    #+#             */
/*   Updated: 2025/11/23 17:17:06 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "separate_quote_chuncks_internal.h"

static void				update_token_section(
							const char *str, int *i,
							bool *doublequote, bool *singlequote);
static void				push_non_quote_section(
							t_token_separated_sections *exp_sections,
							const char *str,
							int *i, bool single_double_quote[2]);
static void				push_doublequote_section(
							t_token_separated_sections *exp_sections,
							const char *str, int *i, bool doublequote);
static void				push_singlequote_section(
							t_token_separated_sections *exp_sections,
							const char *str, int *i, bool singlequote);

/**
 * # ft_separate_quote_chuncks
 *
 * Função principal do módulo. Percorre a string original e
 * divide em seções: sem aspas, entre aspas duplas e entre
 * aspas simples. Mantém coordenadas de cada trecho.
 *
 * Lógica:
 * - Controla estados de aspas (simples/duplas).
 * - Detecta início/fim de cada tipo de seção.
 * - Empilha seções e coordenadas em listas.
 * - Converte listas em arrays para uso posterior.
 */
t_token_separated_sections	*ft_separate_quote_chuncks(const char *str)
{
	int							i;
	t_token_separated_sections	*exp_sections;
	bool						single_double_quote[2];

	ft_bzero(single_double_quote, sizeof(single_double_quote));
	exp_sections = ft_create_token_separated_sections();
	if (!exp_sections)
		return (NULL);
	i = -1;
	while (str[++i])
	{
		update_token_section(str, &i,
			&single_double_quote[1], &single_double_quote[0]);
		push_non_quote_section(exp_sections, str, &i, single_double_quote);
		push_doublequote_section(exp_sections, str, &i, single_double_quote[1]);
		push_singlequote_section(exp_sections, str, &i, single_double_quote[0]);
		if (!str[i])
			break ;
	}
	exp_sections->array = (t_token_section **)exp_sections->list->to_array(
			exp_sections->list, (void *(*)(void *))ft_token_session_dup,
			ft_token_session_destroy_callback);
	exp_sections->coord_array = (int **)exp_sections->coord_list->to_array(
			exp_sections->coord_list, (void *(*)(void *))ft_coord_dup, free);
	return (exp_sections);
}

/**
 * # update_token_section
 *
 * Atualiza o estado atual de aspas durante a varredura.
 *
 * Lógica:
 * - Liga/desliga flags de aspas simples e duplas.
 * - Garante alternância correta entre `'` e `"`,
 *   respeitando o shell (uma aspa só fecha a mesma aspa).
 */
static void	update_token_section(
				const char *str, int *i,
				bool *doublequote, bool *singlequote)
{
	if (!*doublequote && !*singlequote && ft_is_special_char(str, *i, "'"))
		*singlequote = true;
	else if (*singlequote && ft_is_special_char(str, *i, "'"))
	{
		*singlequote = false;
		(*i)++;
		if (!*doublequote && !*singlequote && ft_is_special_char(str, *i, "\""))
			*doublequote = true;
	}
	else if (!*doublequote && !*singlequote
		&& ft_is_special_char(str, *i, "\""))
		*doublequote = true;
	else if (*doublequote && ft_is_special_char(str, *i, "\""))
	{
		*doublequote = false;
		(*i)++;
		if (!*doublequote && !*singlequote && ft_is_special_char(str, *i, "'"))
			*singlequote = true;
	}
}

/**
 * # push_non_quote_section
 *
 * Coleta trecho contínuo sem aspas.
 *
 * Lógica:
 * - Avança até encontrar `'` ou `"`.
 * - Empilha substring correspondente e suas coordenadas.
 * - Usado somente quando nenhuma aspa está ativa.
 */
static void	push_non_quote_section(
				t_token_separated_sections *exp_sections, const char *str,
				int *i, bool single_double_quote[2])
{
	int		section_idx;
	int		*coord;
	char	*section;

	section_idx = *i;
	while (str[section_idx]
		&& !single_double_quote[1] && !single_double_quote[0]
		&& !ft_is_special_char(str, section_idx, "\"'"))
		section_idx++;
	if (!single_double_quote[1] && !single_double_quote[0])
	{
		section = ft_substr(str, *i, section_idx - *i);
		exp_sections->list->push(exp_sections->list,
			ft_create_token_session(section, 0)
		);
		free(section);
		coord = ft_new_coord(*i, section_idx - 1);
		exp_sections->coord_list->push(exp_sections->coord_list, coord);
		*i = section_idx - 1;
	}
}

/**
 * # push_doublequote_section
 *
 * Coleta trecho completo entre aspas duplas `"..."`,
 * incluindo as aspas na substring.
 *
 * Lógica:
 * - Verifica se o estado está em doublequote.
 * - Avança até a próxima `"`.
 * - Empilha substring inteira + coordenadas.
 */
static void	push_doublequote_section(
				t_token_separated_sections *exp_sections,
				const char *str, int *i, bool doublequote)
{
	int		section_idx;
	int		*coord;
	char	*section;

	section_idx = *i;
	if (doublequote && ft_is_special_char(str, section_idx, "\""))
		section_idx++;
	while (str[section_idx]
		&& doublequote && !ft_is_special_char(str, section_idx, "\""))
		section_idx++;
	if (doublequote && ft_is_special_char(str, section_idx, "\""))
	{
		section = ft_substr(str, *i, section_idx - *i + 1);
		exp_sections->list->push(exp_sections->list,
			ft_create_token_session(section, '"'));
		free(section);
		coord = ft_new_coord(*i, section_idx);
		exp_sections->coord_list->push(exp_sections->coord_list, coord);
		*i = section_idx - 1;
	}
}

/**
 * # push_singlequote_section
 *
 * Coleta trecho `'...'` completo, preservando as aspas.
 *
 * Lógica:
 * - Varre até a próxima `'`.
 * - Empilha substring e coordenadas.
 * - Essencial porque conteúdo entre aspas simples
 *   nunca deve sofrer expansão.
 */
static void	push_singlequote_section(
				t_token_separated_sections *exp_sections,
				const char *str, int *i, bool singlequote)
{
	int		section_idx;
	int		*coord;
	char	*section;

	section_idx = *i;
	if (singlequote
		&& ft_is_special_char(str, section_idx, "'"))
		section_idx++;
	while (str[section_idx] && singlequote
		&& !ft_is_special_char(str, section_idx, "'"))
		section_idx++;
	if (singlequote && ft_is_special_char(str, section_idx, "'"))
	{
		section = ft_substr(str, *i, section_idx - *i + 1);
		exp_sections->list->push(exp_sections->list,
			ft_create_token_session(section, '\''));
		free(section);
		coord = ft_new_coord(*i, section_idx);
		exp_sections->coord_list->push(exp_sections->coord_list, coord);
		*i = section_idx - 1;
	}
}
