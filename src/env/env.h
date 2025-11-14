/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 10:52:08 by ighannam          #+#    #+#             */
/*   Updated: 2025/11/13 16:40:17 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "../includes/minishell.h"

typedef struct s_env_value
{
	char			*value;
	int				set;
}					t_env_value;

t_linkedlist_array	*ft_init_ht_env(char **envp);
void				ft_split_key_value(char *s, char **key_value);
t_ht				*ft_content_node_ht(char *s);
void				ft_free_item_ht_env(void *node_ht);
char				*ft_expand_var(char *s, t_linkedlist_array *ht_env);

#endif