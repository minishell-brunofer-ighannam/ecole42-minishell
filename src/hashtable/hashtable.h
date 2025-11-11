/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 14:28:00 by ighannam          #+#    #+#             */
/*   Updated: 2025/11/11 11:05:09 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASHTABLE_H
# define HASHTABLE_H

# define ENV_HASH_SIZE 256

# include "minishell.h"

typedef struct s_env
{
	char			*key;
	char			*value;
	int				set;
	struct s_env	*next;
}					t_env;

// int	ft_hash(char *key);
// t_linkedlist_array *ft_init_ht(int size, t_ht **key_value);
// void ft_free_item_ht(void *node_ht);
// void *ft_find_ht(t_linkedlist_array *ht ,char *key);
// void ft_include_item_ht(t_linkedlist_array *ht, t_ht *new);
// void ft_remove_item_ht(t_linkedlist_array *ht, t_ht *new);

#endif