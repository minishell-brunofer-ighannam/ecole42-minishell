/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_expandable_object.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 12:30:52 by valero            #+#    #+#             */
/*   Updated: 2025/11/24 23:13:37 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../tests.h"
#include "../../../src/core/lexer/tokenize/expandable_object/expandable_object_internal.h"
#include "../../../src/core/lexer/tokenize/expandable_object/expandable_object.h"
#include "../../../src/core/lexer/tokenize/tokenize.h"

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
	char					**expandable_keys;
	int						**expandable_coords_array;
	t_expandable_object		*object;
	int						i;
	int						right_tokens;

	test.teste_number = 1;
	test.test_input = "hello\"my dear $USER\"'its good'\"to see you at $PLACE, in\"$TOWN$SATE$COUNTRY";
	t_token *token = ft_calloc(1, sizeof(t_token));
	token->value = test.test_input;
	object = ft_create_expandable_object(token);
	expandable_keys = object->expandable_keys;
	expandable_coords_array = object->expandable_coord_keys;
	char	*expected_array[] = {"$USER", "$PLACE", "$TOWN", "$SATE", "$COUNTRY", NULL};
	int	expected_coords[][2] = {{14, 18}, {45, 50}, {56, 60}, {61, 65}, {66, 73}};
	right_tokens = 0;
	i = 0;
	while (expected_array[i])
	{
		if (!ft_strncmp(expected_array[i], expandable_keys[i], ft_strlen(expected_array[i]) + 1))
			right_tokens++;
		i++;
	}
	i = 0;
	while (expected_array[i])
	{
		if (expected_coords[i][0] == expandable_coords_array[i][0] && expected_coords[i][1] == expandable_coords_array[i][1])
			right_tokens++;
		i++;
	}
	test.test_ok = (i * 2) == right_tokens;
	print_test_and_result(test, print_result, expandable_keys);
	object->destroy(&object);
	free(token);
}
