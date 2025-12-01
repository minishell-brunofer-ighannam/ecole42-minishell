/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntactic_analysis_internal.h                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 13:15:02 by valero            #+#    #+#             */
/*   Updated: 2025/12/01 16:27:43 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNTACTIC_ANALYSIS_INTERNAL_H
# define SYNTACTIC_ANALYSIS_INTERNAL_H

# include "syntactic_analysis.h"

void	ft_analyse_logic_node(t_binary_tree_node	*node);
void	ft_analyse_pipe_node(t_binary_tree_node	*node);
void	ft_analyse_redirect_node(t_binary_tree_node	*node);

#endif
