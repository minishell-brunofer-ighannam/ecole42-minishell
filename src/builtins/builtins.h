/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 10:20:31 by ighannam          #+#    #+#             */
/*   Updated: 2025/11/11 13:07:23 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
#define BUILTINS_H

#include "../includes/minishell.h"

typedef struct s_env	t_env;

void	ft_env(t_linkedlist_array *ht_env);
void	ft_unset(t_env **env, char *key);
void	ft_export(t_linkedlist_array *ht_env, char *key_value);

#endif