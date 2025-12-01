/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_build_internal.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 20:37:28 by valero            #+#    #+#             */
/*   Updated: 2025/11/30 21:46:33 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_BUILD_INTERNAL_H
# define AST_BUILD_INTERNAL_H

# include "ast_build.h"

typedef struct s_lexer_subset		t_lexer_subset;
struct s_lexer_subset
{
	t_token			**tokens;
	int				size;
	t_lexer_subset	*(*subset)(t_lexer_subset *prev_subset, int start, int end);
	void			*(*destroy)(t_lexer_subset **self_ref);
};

typedef struct s_buid_ast_params	t_buid_ast_context;
struct s_buid_ast_params
{
	t_ast				*ast;
	t_binary_tree_node	*tree_node;
	bool				on_left;
	t_lexer_subset		*prev_subset;
};

// Build part functions
void				ft_manage_multiples_redirect(
						t_buid_ast_context *ctx,
						int *lower_precedence);
void				ft_build_ast_node(t_buid_ast_context *ctx, void *exec);
void				ft_push_redirect_node(int sep_idx, t_ast_node_type type,
						t_buid_ast_context *ctx, void *exec);
void				ft_push_node_composition(int sep_idx, t_ast_node_type type,
						t_buid_ast_context *ctx, void *exec);
void				ft_push_cmd_node(t_buid_ast_context *ctx, void *exec);

// Lexer manipulation
t_lexer_subset	*ft_create_lexer_subset(t_lexer *lexer, int start, int end);

// Build utils functions
t_binary_tree_node	*ft_get_next_node(t_ast *ast,
						t_binary_tree_node *tree_node, bool on_left);
t_buid_ast_context	ft_create_buid_ast_context(t_ast *ast,
						t_binary_tree_node *tree_node, bool on_left,
						t_lexer_subset *prev_subset);
int					ft_find_lower_precedence(t_token **tokens);

#endif
