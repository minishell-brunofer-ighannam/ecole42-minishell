/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 12:30:52 by valero            #+#    #+#             */
/*   Updated: 2025/11/15 17:20:45 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../tests.h"
#include "../../../src/lexer/tokenizer/tokenize/tokenize.h"
#include "../../../src/lexer/tokenizer/tokenize/tokenize_internal.h"

static void	test1(void);
static void	test2(void);

int	main(void)
{
	test1();
	test2();
}

static void	print_result(void *arg)
{
	char	*result;

	result = (char *)arg;
	printf("[%s] ", result);
}

static char	*expand_var(const char *key)
{
	int	len;
	char	*result[] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", NULL};

	len = ft_strlen(key);
	if (!len)
		return (ft_strdup("zero"));
	return (ft_strdup(result[(ft_strlen(key) - 1) % 10]));
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
	t_token *token = ft_create_token(ft_strdup(test.test_input), 0, coord, callbacks);
	t_expansion_build	*result = token->build_expansion(token);
	char	*expected = "hello\"my dear five\"'its good'\"to see you at six, in\"fivefiveeight";
	test.test_ok = !ft_strncmp(expected, result->token_expanded, ft_strlen(expected) + 1);
	print_test_and_result(test, print_result, result->token_expanded);
	token->destroy(&token);
	result->destroy(&result);
}

static void	test2(void)
{
	t_test					test;

	test.teste_number = 1;
	test.test_input = "hello\"my dear $USER\"'its $VAR_TO_KEEP_UP good'\"to see you at $MONICA_BAR, in\"$LENGTH$GREATER$THAN_OTHERS";
	int coord[2] = {0, 0};
	t_expander_callbacks callbacks;
	callbacks.expand_glob = NULL;
	callbacks.expand_var = expand_var;
	t_token *token = ft_create_token(ft_strdup(test.test_input), 0, coord, callbacks);
	t_expansion_build	*result = token->build_expansion(token);
	char	*expected = "hello\"my dear five\"'its $VAR_TO_KEEP_UP good'\"to see you at one, in\"seveneighttwo";
	test.test_ok = !ft_strncmp(expected, result->token_expanded, ft_strlen(expected) + 1);
	print_test_and_result(test, print_result, result->token_expanded);
	if (result->glob_error)
		return ;
	token->destroy(&token);
	result->destroy(&result);
}
