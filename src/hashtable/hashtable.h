/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 14:28:00 by ighannam          #+#    #+#             */
/*   Updated: 2025/11/06 11:45:52 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASHTABLE_H
# define HASHTABLE_H

# define ENV_HASH_SIZE 256

# include "../src/lexer/lexer.h"
# include "../src/signals.h"
# include "libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>

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
void				ft_env(t_env **env);
char				*ft_find_env_value(char *key, t_env **env);
void				ft_unset(t_env **env, char *key);
char				**ft_split_env(char *s);
void				ft_export(t_env **env, char *key, char *value);
void				ft_ordene_keys(t_env **env, char **all_keys);
void				ft_swap_keys(int i, int j, char **all_keys);
char				*ft_find_path(t_env **env, char *cmd);

#endif