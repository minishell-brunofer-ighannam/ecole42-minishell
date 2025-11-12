/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 21:19:06 by valero            #+#    #+#             */
/*   Updated: 2025/11/11 23:11:09 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_UTILS_H
# define LEXER_UTILS_H

# include <stdbool.h>

bool	ft_is_valid_backslash(const char *str, int idx);
int		is_reserved_token(char *str, int idx);
bool	ft_is_special_char(const char *str, int idx, char *chars);
void	print_structure_not_closed_error(char *src, int error_idx);

#endif
