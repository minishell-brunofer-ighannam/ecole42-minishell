/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 14:40:44 by ighannam          #+#    #+#             */
/*   Updated: 2025/11/12 14:57:37 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
#define EXECUTER_H

#include "../includes/minishell.h"

typedef enum e_node_type
{
    NODE_CMD,
    NODE_PIPE,
    NODE_AND,
    NODE_OR,
    NODE_SUBSHELL,
    NODE_REDIR
} t_node_type;

typedef struct s_node
{
	t_node_type		type;
	char			**argv;
	struct s_node	*left;
	struct s_node	*right;
	int				built_in;
} t_node;

char	*ft_find_path(t_linkedlist_array *ht_env, char *cmd);


#endif
