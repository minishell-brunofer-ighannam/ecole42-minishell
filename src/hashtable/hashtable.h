/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 14:28:00 by ighannam          #+#    #+#             */
/*   Updated: 2025/11/05 17:45:23 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASHTABLE_H
#define HASHTABLE_H

#define ENV_HASH_SIZE 256

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include "libft.h"
# include "../src/signals.h"
# include "../src/lexer/lexer.h"

typedef struct s_env
{
	char *key;
	char *value;
	struct s_env *next;
} t_env;

int ft_hash(char *key);
void ft_include_ht(t_env **env, char *key, char *value);
t_env **ft_init_ht(char **envp);
void	ft_env(t_env **env);

#endif