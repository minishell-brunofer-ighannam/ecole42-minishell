/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 14:28:00 by ighannam          #+#    #+#             */
/*   Updated: 2025/11/09 15:57:21 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASHTABLE_H
# define HASHTABLE_H

# define ENV_HASH_SIZE 256

#include "minishell.h"

typedef struct s_env
{
	char			*key;
	char			*value;
	int				set;
	struct s_env	*next;
}					t_env;

int					ft_hash(char *key);
void				ft_set(t_env **env, char *key, char *value, int set);
t_env				**ft_init_ht(char **envp);
char				*ft_find_env_value(char *key, t_env **env);
char				**ft_split_env(char *s);

#endif