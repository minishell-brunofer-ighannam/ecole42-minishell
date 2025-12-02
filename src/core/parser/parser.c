/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 14:37:53 by valero            #+#    #+#             */
/*   Updated: 2025/12/01 18:11:59 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_internal.h"

static int	ft_get_syntact_error(t_ast *ast);
static void	ft_print_syntact_error(t_ast *ast, int error_idx);

t_ast	*ft_parser(const char *prompt, t_expander_callbacks callbacks,
			void *exec, void (*free_content)(void *arg))
{
	t_ast	*ast;
	t_lexer	*lexer;
	int		syntact_error;

	if (!prompt)
		return (NULL);
	lexer = ft_lexer(prompt, callbacks.expand_var, callbacks.expand_glob);
	if (!lexer)
		return (NULL);
	ast = ft_ast_build(lexer, exec);
	if (!ast)
	{
		if (lexer)
			lexer->destroy(&lexer);
		return (NULL);
	}
	ft_syntactic_analysis(ast);
	syntact_error = ft_get_syntact_error(ast);
	if (syntact_error > -1)
	{
		ft_print_syntact_error(ast, syntact_error);
		return (ast->destroy(&ast, free_content));
	}
	return (ast);
}

static int	ft_get_syntact_error(t_ast *ast)
{
	int	idx;

	idx = -1;
	while (ast->lexer->tokens[++idx])
		if (ast->lexer->tokens[idx]->sintaxe_error)
			return (ast->lexer->tokens[idx]->position);
	return (-1);
}

static void	ft_print_syntact_error(t_ast *ast, int error_idx)
{
	int			idx;
	t_token		*target_token;
	const char	*original_prompt;
	int			pointer_idx;

	if (!ast || !ast->lexer || !ast->lexer->original_prompt
		|| !ast->lexer->tokens)
		return ;
	target_token = ast->lexer->tokens[error_idx];
	if (!target_token)
		return ;
	original_prompt = ast->lexer->original_prompt;
	idx = -1;
	while (original_prompt[++idx] && idx < target_token->coord_in_src[1] + 20)
	{
		if (idx < target_token->coord_in_src[0]
			|| idx > target_token->coord_in_src[1])
			ft_putchar_fd((char)original_prompt[idx], 2);
		else
		{
			ft_print_bold_read((char *)target_token->value, 2);
			idx = target_token->coord_in_src[1];
		}
	}
	pointer_idx = (target_token->coord_in_src[0]
			+ target_token->coord_in_src[1]) / 2;
	idx = -1;
	ft_putchar_fd('\n', 2);
	while (original_prompt[++idx] && idx <= pointer_idx)
	{
		if (idx < pointer_idx)
			ft_putchar_fd(' ', 2);
		else
			ft_print_bold_read("^  syntax error: structure in wrong position\n", 2);
	}
}
