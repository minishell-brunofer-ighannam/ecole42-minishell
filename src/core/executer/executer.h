/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 14:40:44 by ighannam          #+#    #+#             */
/*   Updated: 2025/12/07 18:28:39 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H

# include "../../data_structures/data_structures.h"
# include "../../signals.h"
# include "../lexer/lexer.h"
# include "../parser/parser.h"
# include "builtins/builtins.h"
# include "env/env.h"
# include "mapper/mapper.h"
# include "process/process.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <stdio.h>
# include <sys/stat.h>
# include <sys/wait.h>

typedef struct s_redirect
{
	t_ast_node_type	type;
	char			*file;
}					t_redirect;

// EXECUTER
int					ft_executer(const char *line, void *exec);

// TREE
int					ft_execute_tree(t_ast *ast);
int					ft_execute_node(t_binary_tree_node *node, t_ast *ast);
void				free_ast_node(void *arg);

// CMD
char				*ft_find_path(t_linkedlist_array *ht_env, char *cmd);
int					ft_execute_cmd(t_binary_tree_node *node, t_ast *ast);
void				*ft_child_task_func_cmd(t_child_process *process,
						t_child_process_callback_args args);
int					ft_expand_tokens(t_binary_tree_node *node);
void				ft_built_args(t_binary_tree_node *node);

// CMD BUILTIN
int					ft_execute_builtin(t_binary_tree_node *node, t_ast *ast);

// REDIRECT
int					ft_is_redirect(t_binary_tree_node *node);
int					ft_visit_redirect(t_binary_tree_node *node, t_ast *ast);
int					ft_execute_redirect(t_binary_tree_node *node);
int					ft_execute_redirect_in(t_linkedlist_node *node);
int					ft_execute_redirect_out(t_linkedlist_node *node);
int					ft_execute_append_out(t_linkedlist_node *node);
void				ft_free_item_redirect(void *content);

// HEREDOC
int					ft_execute_heredocs(t_binary_tree_node *node);
char				*ft_generate_temp_file(void);
void				ft_dfs_find_heredoc(t_linkedlist *heredoc,
						t_binary_tree_node *node);
t_linkedlist		*ft_find_all_heredoc(t_binary_tree_node *node);

// PIPE
int					ft_execute_pipe(t_binary_tree_node *node, t_ast *ast);

// SUBSHELL
int					ft_execute_subshell(t_binary_tree_node *node, t_ast *ast);

// AND OR
int					ft_execute_and(t_binary_tree_node *node, t_ast *ast);
int					ft_execute_or(t_binary_tree_node *node, t_ast *ast);

#endif
