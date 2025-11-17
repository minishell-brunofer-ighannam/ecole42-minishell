/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 00:23:57 by valero            #+#    #+#             */
/*   Updated: 2025/11/17 02:39:57 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tests.h"
#include "../../src/lexer/tokenizer/tokenize/tokenize.h"
#include "../../src/lexer/tokenizer/tokenize/tokenize_internal.h"
#include "../../src/lexer/tokenizer/tokenizer_internal.h"
#include "../../src/lexer/tokenizer/tokenizer.h"
#include "../../src/env/env.h"
#include "../../src/builtins/builtins.h"


static void	test1(t_linkedlist_array	*env);
// static void	test2(t_linkedlist_array	*env);
// static void	test3(t_linkedlist_array	*env);

int	main(int argc, char **argv, char **envp)
{
	t_linkedlist_array	*env;

	(void)argc;
	(void)argv;
	env = ft_init_ht_env(envp);
	test1(env);
	// test2(env);
	// test3(env);
	env->destroy(&env, ft_free_item_ht_env);
}

typedef struct s_print	t_print;
struct s_print
{
	t_tokenized_prompt	*tokenized_prompt;
	t_linkedlist_array *env;
};

static void	print_result(void *arg)
{
	t_print	*result;

	result = (t_print *)arg;
	t_token				**token;
	t_expansion_build	*expansion;
	int	idx = -1;
	while (++idx < result->tokenized_prompt->size)
	{
		token = &result->tokenized_prompt->tokens[idx];
		expansion = (*token)->build_expansion(*token, result->env);
		printf("[%s] ", expansion->token_expanded);
		expansion->destroy(&expansion);
	}
	printf("\n");
}

static void	test1(t_linkedlist_array	*env)
{
	t_test					test;

	ft_export(env, "PLACE=42");
	ft_export(env, "TOWN=SaoPaulo");
	ft_export(env, "STATE=SP");
	ft_export(env, "COUNTRY=BR");
	test.teste_number = 1;
	test.test_input = "echo hello\"my dear $USER\"'its good $NO_EXPAND'\"to see you at $PLACE, in\"$TOWN$STATE$COUNTRY|grep -E \"[regex]\">outfile.txt";
	char	*expected_array[] = {"echo", "hello\"my dear valero\"'its good $NO_EXPAND'\"to see you at 42, in\"SaoPauloSPBR", "|", "grep", "-E", "\"[regex]\"", ">", "outfile.txt", NULL};
	t_tokenized_prompt *tokenized_prompt = ft_tokenizer(test.test_input, ft_expand_var, ft_expand_glob);
	t_token				**token;
	t_expansion_build	*expansion;
	int					idx = -1;
	int					right_tokens = 0;
	while (++idx < tokenized_prompt->size)
	{
		token = &tokenized_prompt->tokens[idx];
		expansion = (*token)->build_expansion(*token, env);
		if (!ft_strncmp(expansion->token_expanded, expected_array[idx], ft_strlen(expected_array[idx]) + 1))
			right_tokens++;
		expansion->destroy(&expansion);
	}
	test.test_ok = right_tokens == tokenized_prompt->size;
	t_print	print_struct;
	print_struct.tokenized_prompt = tokenized_prompt;
	print_struct.env = env;
	print_test_and_result(test, print_result, &print_struct);
	tokenized_prompt->destroy(&tokenized_prompt);
}
