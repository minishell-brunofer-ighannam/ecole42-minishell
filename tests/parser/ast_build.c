/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 18:44:01 by valero            #+#    #+#             */
/*   Updated: 2025/11/27 00:33:21 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tests.h"
#include "../../src/core/parser/parser_internal.h"
#include "../../src/core/lexer/lexer.h"
#include "../../src/core/executer/env/env.h"
#include "../../src/core/executer/builtins/builtins.h"

static void	test1(t_linkedlist_array	*env);

int	main(int argc, char **argv, char **envp)
{
	t_linkedlist_array	*env;

	(void)argc;
	(void)argv;
	env = ft_init_ht_env(envp);
	test1(env);
	env->destroy(&env, ft_free_item_ht_env);
}

void	test1(t_linkedlist_array	*env)
{
	t_test	test;

	ft_export(env, "USER=lexer");
	ft_export(env, "PLACE=42");
	ft_export(env, "TOWN=SaoPaulo");
	ft_export(env, "STATE=SP");
	ft_export(env, "COUNTRY=BR");
	test.teste_number = 1;
	test.test_input = "echo hello|grep -E \"[regex]\">outfile.txt&&(echo subshell)";
	t_lexer *lexer = ft_lexer(test.test_input, ft_expand_var, ft_expand_glob);
	t_ast	*ast = ft_ast_build(lexer, NULL);
	ast->print(ast);
}
