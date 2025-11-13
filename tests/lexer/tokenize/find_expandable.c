/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_expandable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 12:30:52 by valero            #+#    #+#             */
/*   Updated: 2025/11/13 18:07:23 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../tests.h"
#include "../../../src/lexer/tokenizer/tokenize/tokenize_internal.h"

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

static void	free_coords(int **coords)
{
	int	i;

	i = -1;
	while (coords[++i])
		free(coords[i]);
	free(coords);
}

static void	test1(void)
{
	t_test					test;
	char					**splitted;
	int						**coords;
	t_expandable_section	*expandable_sections;
	int						i;
	int						right_tokens;

	test.teste_number = 1;
	test.test_input = "hello\"my dear $USER\"'its good'\"to see you at $PLACE, in\"$TOWN$SATE$COUNTRY";
	expandable_sections = ft_find_expandable(test.test_input);
	splitted = expandable_sections->array;
	coords = expandable_sections->coord_array;
	char	*expected_array[] = {"hello", "\"my dear $USER\"", "\"to see you at $PLACE, in\"", "$TOWN$SATE$COUNTRY", NULL};
	int	expected_coords[][2] = {{0, 4}, {5, 19}, {30, 55}, {56, 73}};
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
	ft_destroy_char_matrix(&expandable_sections->array);
	free_coords(expandable_sections->coord_array);
	expandable_sections->list->destroy(&expandable_sections->list, free);
	expandable_sections->coord_list->destroy(&expandable_sections->coord_list, free);
	free(expandable_sections);
}

/*


[
{
char	*expandable	->	hello;
int		*coord		->	[0, 4];
},
{
char	*expandable	->	my dear $USER;
int		*coord		->	[5, 17];
},
{
char	*expandable	->	to see you at $PLACE, in;
int		*coord		->	[28, end];
},
]

 */
