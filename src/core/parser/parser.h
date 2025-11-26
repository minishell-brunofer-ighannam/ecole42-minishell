/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 00:14:45 by valero            #+#    #+#             */
/*   Updated: 2025/11/25 23:43:53 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../../data_structures/data_structures.h"
# include "../lexer/lexer.h"

typedef enum e_ast_node_type	t_ast_node_type;
enum e_ast_node_type
{
	AST_NODE_UNKNOWN = 'u' << 16 | 'n' << 8 | 'k',

	AST_NODE_CMD = 'c' << 16 | 'm' << 8 | 'd',
	AST_NODE_ARG = 'a' << 16 | 'r' << 8 | 'g',

	AST_NODE_PIPE = '|',
	AST_NODE_OR = '|' << 8 | '|',
	AST_NODE_AND = '&' << 8 | '&',

	AST_NODE_SEMICOLON = ';',
	AST_NODE_BACKGROUND = '&',

	AST_NODE_SUBSHELL = '(',

	AST_NODE_REDIRECT_IN = '<',
	AST_NODE_REDIRECT_OUT = '>',
	AST_NODE_HERE_DOC_IN = '<' << 8 | '<',
	AST_NODE_APPEND_OUT = '>' << 8 | '>',
};

typedef struct s_ast_node		t_ast_node;
struct s_ast_node
{
	t_ast_node_type	type;
	t_token			**tokens;
	void			*exec;
	void			*(*destroy)(t_ast_node **self_ref,
			void (*free_exec)(void *exec));
};

typedef struct s_ast			t_ast;
struct s_ast
{
	t_lexer			*lexer;
	t_binary_tree	*tree;
	void			*(*destroy)(t_ast **self_ref,
			void (*free_content)(void *arg));
};

#endif
