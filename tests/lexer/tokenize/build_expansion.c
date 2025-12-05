/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 12:30:52 by valero            #+#    #+#             */
/*   Updated: 2025/12/04 20:31:20 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../tests.h"
#include "../../../src/core/lexer/tokenize/tokenize.h"
#include "../../../src/core/lexer/tokenize/tokenize_internal.h"
#include "../../../src/core/lexer/lexer_internal.h"
#include "../../../src/core/executer/env/env.h"
#include "../../../src/core/executer/builtins/builtins.h"


static void	test1(t_linkedlist_array	*env);
static void	test2(t_linkedlist_array	*env);
static void	test3(t_linkedlist_array	*env);
static void	test4(t_linkedlist_array	*env);
static void	test5(t_linkedlist_array	*env);
static void	test6(t_linkedlist_array	*env);
static void	test7(t_linkedlist_array	*env);

int	main(int argc, char **argv, char **envp)
{
	t_linkedlist_array	*env;

	(void)argc;
	(void)argv;
	env = ft_init_ht_env(envp);
	test1(env);
	test2(env);
	test3(env);
	test4(env);
	test5(env);
	test6(env);
	test7(env);
	env->destroy(&env, ft_free_item_ht_env);
}

static void	print_result(void *arg)
{
	char	*result;

	result = (char *)arg;
	printf("%s", result);
}

// $HOME, $USER
// static char	*expand_var(const char *key)
// {
// 	int	len;
// 	char	*result[] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", NULL};

// 	len = ft_strlen(key);
// 	if (!len)
// 		return (ft_strdup("zero"));
// 	return (ft_strdup(result[(ft_strlen(key) - 1) % 10]));
// }

static void	test1(t_linkedlist_array	*env)
{
	t_test					test;

	ft_export(env, "USER=lexer");
	ft_export(env, "PLACE=42");
	ft_export(env, "TOWN=SaoPaulo");
	ft_export(env, "STATE=SP");
	ft_export(env, "COUNTRY=BR");
	test.teste_number = 1;
	test.test_input = "hello\"my dear $USER\"'its good'\"to see you at $PLACE, in\"$TOWN$STATE$COUNTRY";
	char	*expected = "hellomy dear lexerits goodto see you at 42, inSaoPauloSPBR";
	int *coord = ft_new_coord(0, 0);
	t_expander_callbacks callbacks;
	callbacks.expand_glob = NULL;
	callbacks.expand_var = ft_expand_var;
	callbacks.expand_glob = ft_expand_glob;
	t_token *token = ft_create_token(test.test_input, 0, coord, callbacks);
	free(coord);
	t_expansion_build	*result = token->build_expansion(token, env);
	test.test_ok = !ft_strncmp(expected, result->token_expanded, ft_strlen(expected) + 1);
	print_test_and_result(test, print_result, result->token_expanded);
	token->destroy(&token);
	result->destroy(&result);
}
// echo hello"my dear $USER"'its $VAR_TO_KEEP_UP good'"to see you at $MONICA_BAR, in"$LENGTH$GREATER$THAN_OTHERS

static void	test2(t_linkedlist_array	*env)
{
	t_test					test;

	ft_set(env, "VAR_TO_KEEP_UP=teste");
	ft_set(env, "MONICA_BAR=bunker");
	ft_set(env, "LENGTH=len");
	ft_set(env, "GREATER=greater");
	ft_set(env, "THAN_OTHERS=others");
	test.teste_number = 2;
	test.test_input = "hello\"my dear $USER\"'its $VAR_TO_KEEP_UP good'\"to see you at $MONICA_BAR, in\"$LENGTH$GREATER$THAN_OTHERS";
	char	*expected = "hellomy dear lexerits $VAR_TO_KEEP_UP goodto see you at bunker, inlengreaterothers";
	int *coord = ft_new_coord(0, 0);
	t_expander_callbacks callbacks;
	callbacks.expand_glob = NULL;
	callbacks.expand_var = ft_expand_var;
	callbacks.expand_glob = ft_expand_glob;
	t_token *token = ft_create_token(test.test_input, 0, coord, callbacks);
	free(coord);
	t_expansion_build	*result = token->build_expansion(token, env);
	test.test_ok = !ft_strncmp(expected, result->token_expanded, ft_strlen(expected) + 1);
	print_test_and_result(test, print_result, result->token_expanded);
	if (result->glob_error)
		return ;
	token->destroy(&token);
	result->destroy(&result);
}

static void	test3(t_linkedlist_array	*env)
{
	t_test					test;

	ft_set(env, "VAR_TO_KEEP_UP=teste");
	ft_set(env, "MONICA_BAR=bunker");
	ft_set(env, "LENGTH=len");
	ft_set(env, "GREATER=greater");
	ft_set(env, "THAN_OTHERS=others");
	test.teste_number = 3;
	test.test_input = "$HOME/*";
	char	*expected = "/nfs/homes/brunofer/backup /nfs/homes/brunofer/Born2beroot-breno /nfs/homes/brunofer/Desktop /nfs/homes/brunofer/Documents /nfs/homes/brunofer/Downloads /nfs/homes/brunofer/francinette /nfs/homes/brunofer/game_jam /nfs/homes/brunofer/goinfre /nfs/homes/brunofer/mini-moulinette /nfs/homes/brunofer/Music /nfs/homes/brunofer/Pictures /nfs/homes/brunofer/projects /nfs/homes/brunofer/Public /nfs/homes/brunofer/ronaldo_so_long /nfs/homes/brunofer/rush /nfs/homes/brunofer/rush01 /nfs/homes/brunofer/sgoinfre /nfs/homes/brunofer/Templates /nfs/homes/brunofer/teste /nfs/homes/brunofer/testefinalrush /nfs/homes/brunofer/Videos /nfs/homes/brunofer/VirtualBox VMs";
	int *coord = ft_new_coord(0, 0);
	t_expander_callbacks callbacks;
	callbacks.expand_glob = NULL;
	callbacks.expand_var = ft_expand_var;
	callbacks.expand_glob = ft_expand_glob;
	t_token *token = ft_create_token(test.test_input, 0, coord, callbacks);
	free(coord);
	t_expansion_build	*result = token->build_expansion(token, env);
	if (result->token_expanded)
		test.test_ok = !ft_strncmp(expected, result->token_expanded, ft_strlen(expected) + 1);
	else
		test.test_ok = false;
	print_test_and_result(test, print_result, result->token_expanded);
	token->destroy(&token);
	result->destroy(&result);
}

static void	test4(t_linkedlist_array	*env)
{
	t_test					test;

	ft_set(env, "VAR_TO_KEEP_UP=teste");
	ft_set(env, "MONICA_BAR=bunker");
	ft_set(env, "LENGTH=len");
	ft_set(env, "GREATER=greater");
	ft_set(env, "THAN_OTHERS=others");
	test.teste_number = 4;
	test.test_input = "*";
	char	*expected = "Makefile README.md build_expansion child_process create_expandable_object env_ht_op expand_glob_test expand_var_test find_expandable find_keys_to_expand find_path includes libft linkedlist linkedlist_array minishell.excalidraw minishell.excalidraw:Zone.Identifier prompt_validator raw_splitter refined_splitter src tests lexer";
	int *coord = ft_new_coord(0, 0);
	t_expander_callbacks callbacks;
	callbacks.expand_glob = NULL;
	callbacks.expand_var = ft_expand_var;
	callbacks.expand_glob = ft_expand_glob;
	t_token *token = ft_create_token(test.test_input, 0, coord, callbacks);
	free(coord);
	t_expansion_build	*result = token->build_expansion(token, env);
	if (result->token_expanded)
		test.test_ok = !ft_strncmp(expected, result->token_expanded, ft_strlen(expected) + 1);
	else
		test.test_ok = false;
	print_test_and_result(test, print_result, result->token_expanded);
	token->destroy(&token);
	result->destroy(&result);
}

static void	test5(t_linkedlist_array	*env)
{
	t_test					test;

	ft_set(env, "VAR_TO_KEEP_UP=teste");
	ft_set(env, "MONICA_BAR=bunker");
	ft_set(env, "LENGTH=len");
	ft_set(env, "GREATER=greater");
	ft_set(env, "THAN_OTHERS=others");
	test.teste_number = 5;
	test.test_input = "ola$12oi";
	char	*expected = "ola2oi";
	int *coord = ft_new_coord(0, 0);
	t_expander_callbacks callbacks;
	callbacks.expand_glob = NULL;
	callbacks.expand_var = ft_expand_var;
	callbacks.expand_glob = ft_expand_glob;
	t_token *token = ft_create_token(test.test_input, 0, coord, callbacks);
	free(coord);
	t_expansion_build	*result = token->build_expansion(token, env);
	if (result->token_expanded)
		test.test_ok = !ft_strncmp(expected, result->token_expanded, ft_strlen(expected) + 1);
	else
		test.test_ok = false;
	print_test_and_result(test, print_result, result->token_expanded);
	token->destroy(&token);
	result->destroy(&result);
}

static void	test6(t_linkedlist_array	*env)
{
	t_test					test;

	ft_set(env, "VAR_TO_KEEP_UP=teste");
	ft_set(env, "MONICA_BAR=bunker");
	ft_set(env, "LENGTH=len");
	ft_set(env, "GREATER=greater");
	ft_set(env, "THAN_OTHERS=others");
	test.teste_number = 6;
	test.test_input = "> >> < ? [ ] | ; [ ] || && ( ) & # $  <<";
	char	*expected = "> >> < ? [ ] | ; [ ] || && ( ) & # $  <<";
	int *coord = ft_new_coord(0, 0);
	t_expander_callbacks callbacks;
	callbacks.expand_glob = NULL;
	callbacks.expand_var = ft_expand_var;
	callbacks.expand_glob = ft_expand_glob;
	t_token *token = ft_create_token(test.test_input, 0, coord, callbacks);
	free(coord);
	t_expansion_build	*result = token->build_expansion(token, env);
	if (result->token_expanded)
		test.test_ok = !ft_strncmp(expected, result->token_expanded, ft_strlen(expected) + 1);
	else
		test.test_ok = false;
	print_test_and_result(test, print_result, result->token_expanded);
	token->destroy(&token);
	result->destroy(&result);
}

static void	test7(t_linkedlist_array	*env)
{
	t_test					test;

	ft_set(env, "VAR_TO_KEEP_UP=teste");
	ft_set(env, "MONICA_BAR=bunker");
	ft_set(env, "LENGTH=len");
	ft_set(env, "GREATER=greater");
	ft_set(env, "THAN_OTHERS=others");
	test.teste_number = 6;
	test.test_input = "$";
	char	*expected = "$";
	int *coord = ft_new_coord(0, 0);
	t_expander_callbacks callbacks;
	callbacks.expand_glob = NULL;
	callbacks.expand_var = ft_expand_var;
	callbacks.expand_glob = ft_expand_glob;
	t_token *token = ft_create_token(test.test_input, 0, coord, callbacks);
	free(coord);
	t_expansion_build	*result = token->build_expansion(token, env);
	if (result->token_expanded)
		test.test_ok = !ft_strncmp(expected, result->token_expanded, ft_strlen(expected) + 1);
	else
		test.test_ok = false;
	print_test_and_result(test, print_result, result->token_expanded);
	token->destroy(&token);
	result->destroy(&result);
}
