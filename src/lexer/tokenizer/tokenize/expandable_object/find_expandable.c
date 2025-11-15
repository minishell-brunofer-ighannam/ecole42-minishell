/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_expandable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 01:12:37 by valero            #+#    #+#             */
/*   Updated: 2025/11/14 18:26:01 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expandable_object.h"
#include "expandable_object_internal.h"

static void				update_token_section(
							const char *str, int *i,
							bool *doublequote, bool *singlequote);
static void				push_non_quote_section(
							t_expandable_section *exp_sections, const char *str,
							int *i, bool single_double_quote[2]);
static void				push_doublequote_section(
							t_expandable_section *exp_sections,
							const char *str, int *i, bool doublequote);
static void				jump_singlequote_section(
							const char *str, int *i, bool singlequote);

t_expandable_section	*ft_find_expandable(const char *str)
{
	int						i;
	t_expandable_section	*exp_sections;
	bool					single_double_quote[2];

	ft_bzero(single_double_quote, sizeof(single_double_quote));
	exp_sections = ft_create_expandable_sections();
	if (!exp_sections)
		return (NULL);
	i = -1;
	while (str[++i])
	{
		update_token_section(str, &i,
			&single_double_quote[1], &single_double_quote[0]);
		push_non_quote_section(exp_sections, str, &i, single_double_quote);
		push_doublequote_section(exp_sections, str, &i, single_double_quote[1]);
		jump_singlequote_section(str, &i, single_double_quote[0]);
		if (!str[i])
			break ;
	}
	exp_sections->array = (char **)exp_sections->list->to_array(
			exp_sections->list, (void *(*)(void *))ft_strdup, free);
	exp_sections->coord_array = (int **)exp_sections->coord_list->to_array(
			exp_sections->coord_list, (void *(*)(void *))ft_coord_dup, free);
	return (exp_sections);
}

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

static void	push_non_quote_section(
				t_expandable_section *exp_sections, const char *str,
				int *i, bool single_double_quote[2])
{
	int	section_idx;
	int	*coord;

	section_idx = *i;
	while (str[section_idx]
		&& !single_double_quote[1] && !single_double_quote[0]
		&& !ft_is_special_char(str, section_idx, "\"'"))
		section_idx++;
	if (!single_double_quote[1] && !single_double_quote[0])
	{
		exp_sections->list->push(exp_sections->list,
			ft_substr(str, *i, section_idx - *i));
		coord = ft_new_coord(*i, section_idx - 1);
		exp_sections->coord_list->push(exp_sections->coord_list, coord);
		*i = section_idx - 1;
	}
}

static void	push_doublequote_section(
				t_expandable_section *exp_sections,
				const char *str, int *i, bool doublequote)
{
	int	section_idx;
	int	*coord;

	section_idx = *i;
	if (doublequote && ft_is_special_char(str, section_idx, "\""))
		section_idx++;
	while (str[section_idx]
		&& doublequote && !ft_is_special_char(str, section_idx, "\""))
		section_idx++;
	if (doublequote && ft_is_special_char(str, section_idx, "\""))
	{
		exp_sections->list->push(exp_sections->list,
			ft_substr(str, *i, section_idx - *i + 1));
		coord = ft_new_coord(*i, section_idx);
		exp_sections->coord_list->push(exp_sections->coord_list, coord);
		*i = section_idx - 1;
	}
}

static void	jump_singlequote_section(
				const char *str, int *i, bool singlequote)
{
	int	section_idx;

	section_idx = *i;
	if (singlequote
		&& ft_is_special_char(str, section_idx, "'"))
		section_idx++;
	while (str[section_idx] && singlequote
		&& !ft_is_special_char(str, section_idx, "'"))
		section_idx++;
	if (singlequote
		&& ft_is_special_char(str, section_idx, "'"))
		*i = section_idx - 1;
}
