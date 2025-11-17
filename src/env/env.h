/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 10:52:08 by ighannam          #+#    #+#             */
/*   Updated: 2025/11/17 02:35:54 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "../data_structures/data_structures.h"
# include "../utils/utils.h"
# include <fcntl.h>
# include <dirent.h>

typedef struct s_env_value
{
	char			*value;
	int				set;
}					t_env_value;

t_linkedlist_array	*ft_init_ht_env(char **envp);
void				ft_split_key_value(char *s, char **key_value);
t_ht				*ft_content_node_ht(char *s);
void				ft_free_item_ht_env(void *node_ht);
char				*ft_expand_var(const char *s, t_linkedlist_array *ht_env);
char				**ft_expand_glob(const char *s);
int					ft_matched_glob(char *after_removal, char *to_match);

#endif
