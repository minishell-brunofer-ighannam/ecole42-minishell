/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_expandable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 01:12:37 by valero            #+#    #+#             */
/*   Updated: 2025/11/13 02:10:08 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize_internal.h"
#include "tokenize.h"

static void	update_token_section(
				char *str, int i,
				bool *doublequote, bool *singlequote);
static void	push_non_quote_section(
				t_linkedlist *list, char *str,
				int *i, bool single_double_quote[2]);
static void	push_doublequote_section(
				t_linkedlist *list, char *str,
				int *i, bool doublequote);
static void	push_singlequote_section(
				t_linkedlist *list, char *str,
				int *i, bool singlequote);

char	**find_expandable(char *str)
{
	int				i;
	t_linkedlist	*list;
	bool			single_double_quote[2];
	int				section_idx;
	char			**expandable_sections;

	single_double_quote[0] = false;
	single_double_quote[1] = false;
	list = ft_new_linkedlist();
	i = -1;
	while (str[++i])
	{
		update_token_section(str, i,
			&single_double_quote[1], &single_double_quote[0]);
		push_non_quote_section(list, str, &i, single_double_quote);
		push_doublequote_section(list, str, &i, single_double_quote[1]);
		push_singlequote_section(list, str, &i, single_double_quote[0]);
	}
	expandable_sections = (char **)list->to_array(list, free);
	list->destroy(&list, free);
	return (expandable_sections);
}

static void	update_token_section(
				char *str, int i,
				bool *doublequote, bool *singlequote)
{
	if (!*doublequote && !*singlequote && ft_is_special_char(str, i, "'"))
		*singlequote = true;
	if (*singlequote && ft_is_special_char(str, i, "'"))
		*singlequote = false;
	if (!*doublequote && !*singlequote && ft_is_special_char(str, i, "\""))
		*doublequote = true;
	if (*doublequote && ft_is_special_char(str, i, "\""))
		*doublequote = false;
}

static void	push_non_quote_section(
				t_linkedlist *list, char *str,
				int *i, bool single_double_quote[2])
{
	int	section_idx;

	section_idx = *i;
	if (!single_double_quote[1] && !single_double_quote[0]
		&& !ft_is_special_char(str, section_idx, "\"'"))
		section_idx++;
	list->push(list, ft_substr(str, *i, section_idx - *i + 1));
	*i = section_idx;
}

static void	push_doublequote_section(
				t_linkedlist *list, char *str,
				int *i, bool doublequote)
{
	int	section_idx;

	section_idx = *i;
	if (doublequote && ft_is_special_char(str, section_idx + 1, "\""))
		section_idx++;
	if (ft_is_special_char(str, section_idx + 1, "\""))
	{
		list->push(list, ft_substr(str, *i, section_idx - *i + 2));
		*i = section_idx + 1;
	}
}

static void	push_singlequote_section(
				t_linkedlist *list, char *str,
				int *i, bool singlequote)
{
	int	section_idx;

	section_idx = *i;
	if (singlequote
		&& ft_is_special_char(str, section_idx + 1, "'"))
		section_idx++;
	if (ft_is_special_char(str, section_idx + 1, "'"))
		*i = section_idx + 1;
}
