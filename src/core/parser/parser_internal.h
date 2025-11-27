/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_internal.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 00:14:45 by valero            #+#    #+#             */
/*   Updated: 2025/11/27 15:14:53 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_INTERNAL_H
# define PARSER_INTERNAL_H

# include "parser.h"

typedef struct s_lexer_subset		t_lexer_subset;
struct s_lexer_subset
{
	t_token			**tokens;
	int				size;
	t_lexer_subset	*(*subset)(t_lexer_subset *prev_subset, int start, int end);
	void			*(*destroy)(t_lexer_subset **self_ref);
};

typedef struct s_buid_ast_params	t_buid_ast_params;
struct s_buid_ast_params
{
	t_ast				*ast;
	t_binary_tree_node	*tree_node;
	bool				on_left;
	t_lexer_subset		*prev_subset;
};

bool			ft_is_redirect_node(t_token *token);
t_lexer_subset	*ft_create_lexer_subset(
					t_lexer *lexer, int start, int end);
int				ft_get_precedence(t_token *node);
int				ft_find_lower_precedence(t_token **tokens);
t_ast			*ft_create_ast(t_lexer *lexer);
t_ast_node		*ft_create_ast_node(
					t_token **tokens,
					t_ast_node_type type,
					void *exec);
void			ft_print_ast(t_ast *self);
t_ast			*ft_ast_build(t_lexer *lexer, void *exec);

#endif
