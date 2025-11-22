/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_expandable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 01:12:37 by valero            #+#    #+#             */
/*   Updated: 2025/11/22 15:14:36 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expandable_object.h"
#include "expandable_object_internal.h"

static void	ft_push_section(
				t_expandable_section *exp_sections,
				t_token_section *section_content,
				t_linkedlist_node *coord_node);

/**
 * # ft_find_expandable
 *
 * Primeira etapa da análise: encontrar *todas* as seções possíveis
 * que possam conter expansões.
 *
 * Lógica:
 * - Fragmenta o token respeitando aspas com `ft_separate_quote_chuncks`.
 * - Pula trechos dentro de aspas simples.
 * - Push das seções e coordenadas em `exp_sections`.
 * - Converte listas para arrays.
 *
 * Base bruta para todo o restante da análise.
 */
t_expandable_section	*ft_find_expandable(const char *str)
{
	t_expandable_section		*exp_sections;
	t_token_separated_sections	*sep_sections;
	t_linkedlist_node			*section_node;
	t_linkedlist_node			*coord_node;
	t_token_section				*section_content;

	exp_sections = ft_create_expandable_sections();
	sep_sections = ft_separate_quote_chuncks(str);
	section_node = sep_sections->list->first;
	coord_node = sep_sections->coord_list->first;
	while (section_node)
	{
		section_content = (t_token_section *)section_node->content;
		if (section_content->quote_type != '\'')
			ft_push_section(exp_sections, section_content, coord_node);
		section_node = section_node->next;
		coord_node = coord_node->next;
	}
	sep_sections->destroy(&sep_sections);
	exp_sections->array = (char **)exp_sections->list->to_array(
			exp_sections->list, (void *(*)(void *))ft_strdup, free);
	exp_sections->coord_array = (int **)exp_sections->coord_list->to_array(
			exp_sections->coord_list, (void *(*)(void *))ft_coord_dup, free);
	return (exp_sections);
}

/**
 * # ft_push_section
 *
 * Insere uma seção candidata à expansão dentro do `t_expandable_section`.
 *
 * Lógica:
 * - Duplica texto da seção.
 * - Duplica coordenada correspondente.
 */
static void	ft_push_section(
				t_expandable_section *exp_sections,
				t_token_section *section_content,
				t_linkedlist_node *coord_node)
{
	exp_sections->list->push(
		exp_sections->list,
		ft_strdup(section_content->section));
	exp_sections->coord_list->push(
		exp_sections->coord_list,
		ft_coord_dup((int *)coord_node->content));
}
