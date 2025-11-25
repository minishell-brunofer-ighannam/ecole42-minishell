/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_keys_to_expand.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 12:30:52 by valero            #+#    #+#             */
/*   Updated: 2025/11/24 23:13:37 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../tests.h"
#include "../../../src/core/lexer/tokenize/expandable_object/expandable_object_internal.h"

static void	test1(void);

int	main(void)
{
	test1();
}

static void	print_result(void *arg)
{
	int		i;
	char	**splitted;

	splitted = (char **)arg;
	i = -1;
	while (splitted[++i])
		printf("[%s] ", splitted[i]);
}

static void	test1(void)
{
	t_test					test;
	char					**splitted;
	int						**coords;
	t_expandable_section	*expandable_sections;
	t_expandable_section	*keys_to_expand;
	int						i;
	int						right_tokens;

	test.teste_number = 1;
	test.test_input = "hello\"my dear $USER\"'its good'\"to see you at $PLACE, in\"$TOWN$SATE$COUNTRY";
	expandable_sections = ft_find_expandable(test.test_input);
	keys_to_expand = ft_find_keys_to_expand(expandable_sections);
	splitted = keys_to_expand->array;
	coords = keys_to_expand->coord_array;
	char	*expected_array[] = {"$USER", "$PLACE", "$TOWN", "$SATE", "$COUNTRY", NULL};
	int	expected_coords[][2] = {{14, 18}, {45, 50}, {56, 60}, {61, 65}, {66, 73}};
	right_tokens = 0;
	i = 0;
	while (expected_array[i])
	{
		if (!ft_strncmp(expected_array[i], splitted[i], ft_strlen(expected_array[i]) + 1))
			right_tokens++;
		i++;
	}
	i = 0;
	while (expected_array[i])
	{
		if (expected_coords[i][0] == coords[i][0] && expected_coords[i][1] == coords[i][1])
			right_tokens++;
		i++;
	}
	test.test_ok = (i * 2) == right_tokens;
	print_test_and_result(test, print_result, splitted);
	keys_to_expand->destroy(&keys_to_expand);
}
