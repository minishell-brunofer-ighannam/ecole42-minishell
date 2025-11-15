/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 12:30:52 by valero            #+#    #+#             */
/*   Updated: 2025/11/14 20:58:47 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../tests.h"
#include "../../../src/lexer/tokenizer/tokenize/tokenize.h"
#include "../../../src/lexer/tokenizer/tokenize/tokenize_internal.h"

static void	test1(void);

int	main(void)
{
	test1();
}

static void	print_result(void *arg)
{
	char	*result;

	result = (char *)arg;
	printf("[%s] ", result);
}

static char	*expand_var(const char *key)
{
	char	*result[] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", NULL};
	return (ft_strdup(result[ft_strlen(key) - 1]));
}

static void	test1(void)
{
	t_test					test;

	test.teste_number = 1;
	test.test_input = "hello\"my dear $USER\"'its good'\"to see you at $PLACE, in\"$TOWN$SATE$COUNTRY";
	int coord[2] = {0, 0};
	t_expander_callbacks callbacks;
	callbacks.expand_glob = NULL;
	callbacks.expand_var = expand_var;
	t_token *token = ft_create_token(test.test_input, 0, coord, callbacks);
	char	*result = token->build_expansion(token);
	char	*expected = "hello\"my dear five\"'its good'\"to see you at six, in\"fivefiveeight";
	test.test_ok = !ft_strncmp(expected, result, ft_strlen(expected) + 1);
	print_test_and_result(test, print_result, result);
	// token->destroy(&token);
}
