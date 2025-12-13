/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 10:20:31 by ighannam          #+#    #+#             */
/*   Updated: 2025/12/13 13:06:51 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../../../data_structures/data_structures.h"
# include "../../../utils/utils.h"
# include "../../parser/parser.h"
# include "../env/env.h"
# include "../mapper/mapper.h"
# include "libft.h"
# include <stdio.h>
# include <unistd.h>

void	ft_env(t_linkedlist_array *ht_env);
int		ft_export(t_linkedlist_array *ht_env, t_token **tokens);
int		ft_export_include(t_linkedlist_array *ht_env, const char *key_value);
void	ft_free_content_ht(t_ht *content);
void	ft_set(t_linkedlist_array *ht_env, const char *key_value);
void	ft_unset(t_linkedlist_array *ht_env, const char *key);
int		ft_cd(t_binary_tree_node *node);
int		ft_pwd(t_binary_tree_node *node);
void	ft_echo(t_binary_tree_node *node);
int		ft_exit(t_binary_tree_node *node, t_ast *ast);
int		ft_is_builtin(const char *cmd);

#endif
