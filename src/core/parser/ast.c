/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 23:03:17 by valero            #+#    #+#             */
/*   Updated: 2025/11/27 00:32:47 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_internal.h"

static void	*ft_destroy_ast_node(
				t_ast_node **self_ref,
				void (*free_exec)(void *exec));
static void	*ft_destroy_ast(t_ast **self_ref, void (*free_content)(void *arg));

t_ast	*ft_create_ast(t_lexer *lexer)
{
	t_ast	*ast;

	ast = ft_calloc(1, sizeof(t_ast));
	if (!ast)
		return (NULL);
	ast->tree = ft_create_binary_tree();
	if (!ast->tree)
	{
		free(ast);
		lexer->destroy(&lexer);
		return (NULL);
	}
	ast->lexer = lexer;
	ast->print = ft_print_ast;
	ast->destroy = ft_destroy_ast;
	return (ast);
}

t_ast_node	*ft_create_ast_node(
				t_token **tokens,
				t_ast_node_type type,
				void *exec)
{
	t_ast_node	*node;
	int			tokens_size;

	node = ft_calloc(1, sizeof(t_ast_node));
	if (!node)
		return (NULL);
	tokens_size = 0;
	while (tokens[tokens_size])
		tokens_size++;
	node->tokens = ft_calloc(tokens_size + 1, sizeof(t_token *));
	while (--tokens_size >= 0)
		node->tokens[tokens_size] = tokens[tokens_size];
	node->type = type;
	node->exec = exec;
	node->destroy = ft_destroy_ast_node;
	return (node);
}

static void	*ft_destroy_ast_node(
				t_ast_node **self_ref,
				void (*free_exec)(void *exec))
{
	t_ast_node	*self;

	if (!self_ref || !*self_ref)
		return (NULL);
	self = *self_ref;
	if (self->tokens)
		free(self->tokens);
	free_exec(self->exec);
	free(self);
	*self_ref = NULL;
	return (NULL);
}

static void	*ft_destroy_ast(t_ast **self_ref, void (*free_content)(void *arg))
{
	t_ast	*self;

	if (!self_ref || *self_ref)
		return (NULL);
	self = *self_ref;
	self->tree->destroy(&self->tree, free_content);
	self->lexer->destroy(&self->lexer);
	free(self);
	*self_ref = NULL;
	return (NULL);
}
