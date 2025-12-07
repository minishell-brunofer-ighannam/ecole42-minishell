/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 00:23:57 by valero            #+#    #+#             */
/*   Updated: 2025/11/24 23:07:30 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tests.h"
#include "../../src/core/lexer/tokenize/tokenize.h"
#include "../../src/core/lexer/tokenize/tokenize_internal.h"
#include "../../src/core/lexer/lexer_internal.h"
#include "../../src/core/lexer/lexer.h"
#include "../../src/core/executer/env/env.h"
#include "../../src/core/executer/builtins/builtins.h"

static void	test1(t_linkedlist_array	*env);
static void	test2(t_linkedlist_array	*env);

int	main(int argc, char **argv, char **envp)
{
	t_linkedlist_array	*env;

	(void)argc;
	(void)argv;
	env = ft_init_ht_env(envp);
	test1(env);
	test2(env);
	env->destroy(&env, ft_free_item_ht_env);
}

typedef struct s_print	t_print;
struct s_print
{
	t_lexer	*lexer;
	t_linkedlist_array *env;
};

static void	print_result(void *arg)
{
	t_print	*result;

	result = (t_print *)arg;
	t_token				**token;
	t_expansion_build	*expansion;
	int	idx = -1;
	while (++idx < result->lexer->size)
	{
		token = &result->lexer->tokens[idx];
		expansion = (*token)->build_expansion(*token, result->env);
		printf("[%s] ", expansion->token_expanded);
		expansion->destroy(&expansion);
	}
	printf("\n");
}

static void	test1(t_linkedlist_array	*env)
{
	t_test					test;

	ft_export(env, "USER=lexer");
	ft_export(env, "PLACE=42");
	ft_export(env, "TOWN=SaoPaulo");
	ft_export(env, "STATE=SP");
	ft_export(env, "COUNTRY=BR");
	test.teste_number = 1;
	test.test_input = "echo hello\"my dear $USER\"'its good $NO_EXPAND'\"to see you at $PLACE, in\"$TOWN$STATE$COUNTRY|grep -E \"[regex]\">outfile.txt";
	char	*expected_array[] = {"echo", "hellomy dear lexerits good $NO_EXPANDto see you at 42, inSaoPauloSPBR", "|", "grep", "-E", "[regex]", ">", "outfile.txt", NULL};
	t_lexer *lexer = ft_lexer(test.test_input, ft_expand_var, ft_expand_glob);
	t_token				**token;
	t_expansion_build	*expansion;
	int					idx = -1;
	int					right_tokens = 0;
	while (++idx < lexer->size)
	{
		token = &lexer->tokens[idx];
		expansion = (*token)->build_expansion(*token, env);
		if (!ft_strncmp(expansion->token_expanded, expected_array[idx], ft_strlen(expected_array[idx]) + 1))
			right_tokens++;
		expansion->destroy(&expansion);
	}
	test.test_ok = right_tokens == lexer->size;
	t_print	print_struct;
	print_struct.lexer = lexer;
	print_struct.env = env;
	print_test_and_result(test, print_result, &print_struct);
	lexer->destroy(&lexer);
}

static void	test2(t_linkedlist_array	*env)
{
	t_test					test;

	ft_export(env, "USER=lexer");
	ft_export(env, "PLACE=42");
	ft_export(env, "TOWN=SaoPaulo");
	ft_export(env, "STATE=SP");
	ft_export(env, "COUNTRY=BR");
	test.teste_number = 2;
	test.test_input = "cat <\"./test_files/file name with spaces\"";
	char	*expected_array[] = {"cat", "<", "./test_files/file name with spaces", NULL};
	t_lexer *lexer = ft_lexer(test.test_input, ft_expand_var, ft_expand_glob);
	t_token				**token;
	t_expansion_build	*expansion;
	int					idx = -1;
	int					right_tokens = 0;
	while (++idx < lexer->size)
	{
		token = &lexer->tokens[idx];
		expansion = (*token)->build_expansion(*token, env);
		if (!ft_strncmp(expansion->token_expanded, expected_array[idx], ft_strlen(expected_array[idx]) + 1))
			right_tokens++;
		expansion->destroy(&expansion);
	}
	test.test_ok = right_tokens == lexer->size;
	t_print	print_struct;
	print_struct.lexer = lexer;
	print_struct.env = env;
	print_test_and_result(test, print_result, &print_struct);
	lexer->destroy(&lexer);
}
