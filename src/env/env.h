/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 10:52:08 by ighannam          #+#    #+#             */
/*   Updated: 2025/11/11 12:54:48 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
#define ENV_H

#include "../includes/minishell.h"

typedef struct s_env_value
{
	char			*value;
	int				set;
}					t_env_value;

t_linkedlist_array *ft_init_ht_env(char **envp);
char	**ft_split_key_value(char *s);
t_ht	*ft_content_node_ht(char *s);

#endif