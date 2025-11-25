/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 10:20:31 by ighannam          #+#    #+#             */
/*   Updated: 2025/11/24 23:45:20 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../../../data_structures/data_structures.h"
# include "../../../utils/utils.h"
# include "../env/env.h"
# include <stdio.h>

void	ft_env(t_linkedlist_array *ht_env);
void	ft_export(t_linkedlist_array *ht_env, const char *key_value);
void	ft_set(t_linkedlist_array *ht_env, const char *key_value);
void	ft_unset(t_linkedlist_array *ht_env, const char *key);

int		ft_is_builtin(const char *cmd);

#endif
