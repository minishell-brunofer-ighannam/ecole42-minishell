/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 16:25:02 by ighannam          #+#    #+#             */
/*   Updated: 2025/11/14 18:56:46 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "../includes/minishell.h"

void	ft_ordene_array_str(char **list);
void	ft_swap_array_str(int i, int j, char **list);
void	ft_clean_array_str(char **list);

#endif