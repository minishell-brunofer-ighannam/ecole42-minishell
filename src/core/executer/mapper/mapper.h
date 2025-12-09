/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapper.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 17:54:56 by ighannam          #+#    #+#             */
/*   Updated: 2025/12/09 14:38:56 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAPPER_H
# define MAPPER_H

# include "../../parser/parser.h"

typedef struct s_redirect	t_redirect;

typedef struct s_exec		t_exec;
struct						s_exec
{
	t_linkedlist_array		*ht_env;
	t_linkedlist			*redirect;
	t_linkedlist			*heredoc;
	t_linkedlist			*heredoc_files;
	char					**envp;
	char					**argv;
	int						fds[2];
	bool					destroy;
	int						flag_n;
};

t_exec						*ft_built_exec(char **envp);
int							ft_get_fd_in(t_binary_tree_node *node);
int							ft_get_fd_out(t_binary_tree_node *node);
void						ft_close_fds(t_binary_tree_node *node);
t_linkedlist_array			*ft_get_ht_env(t_binary_tree_node *node);
t_token						**ft_get_tokens(t_binary_tree_node *node);
t_ast_node_type				ft_get_type(t_binary_tree_node *node);
t_linkedlist				**ft_get_list_redirects(t_binary_tree_node *node);
char						**ft_get_argv(t_binary_tree_node *node);
char						**ft_get_envp(t_binary_tree_node *node);
void						ft_init_argv(t_binary_tree_node *node, int size);
void						ft_set_argv(t_binary_tree_node *node, int index,
								char *str);
void						ft_free_argv(t_binary_tree_node *node);
void						ft_free_exec(void *exec);
void						ft_destroy_exec(void *exec);
void						ft_push_redirect(t_binary_tree_node *node,
								t_redirect *content);
void						ft_set_redirect(t_binary_tree_node *node,
								t_linkedlist *list);
void						ft_init_redirect(t_binary_tree_node *node);
void						ft_set_flag_destroy_exec(t_binary_tree_node *node);
void						ft_free_heredoc_file_item(void *arg);
char						*ft_get_next_heredoc_file(t_binary_tree_node *node);
int							ft_get_flag_n(t_binary_tree_node *node);
void						ft_set_flag_n(t_binary_tree_node *node, int flag);
void						free_ast_node(void *arg);

#endif
