/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 11:15:08 by ighannam          #+#    #+#             */
/*   Updated: 2025/12/07 20:08:45 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASHTABLE_H
# define HASHTABLE_H

# include "../linkedlist_array/linkedlist_array.h"

# define ENV_HASH_SIZE 256

typedef struct s_ht
{
	char			*key;
	void			*value;
}					t_ht;

int		ft_hash(const char *key);
void	ft_include_item_ht(
			t_linkedlist_array *ht, t_ht *new,
			void (*ft_free_item_ht)(void *arg));
void	*ft_find_ht(t_linkedlist_array *ht, const char *key);
void	ft_include_item_ht(
			t_linkedlist_array *ht, t_ht *new,
			void (*ft_free_item_ht)(void *arg));
void	ft_remove_item_ht(
			t_linkedlist_array *ht, t_ht *new,
			void (*ft_free_item_ht)(void *arg));

#endif
