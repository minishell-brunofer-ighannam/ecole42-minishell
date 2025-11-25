/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 16:25:02 by ighannam          #+#    #+#             */
/*   Updated: 2025/11/24 22:44:08 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "libft.h"
# include <stdbool.h>

# define TEXT_LIGHT_BLACK   "\033[90m" // light gray
# define TEXT_LIGHT_RED     "\033[91m"
# define TEXT_LIGHT_GREEN   "\033[92m"
# define TEXT_LIGHT_YELLOW  "\033[93m"
# define TEXT_LIGHT_BLUE    "\033[94m"
# define TEXT_LIGHT_MAGENTA "\033[95m"
# define TEXT_LIGHT_CYAN    "\033[96m"
# define TEXT_LIGHT_WHITE   "\033[97m"

# define TEXT_RESET        "\033[0m"
# define TEXT_BOLD         "\033[1m"
# define TEXT_UNDERLINE    "\033[4m"

void	ft_ordene_array_str(char **list);
void	ft_swap_array_str(int i, int j, char **list);
void	ft_clean_array_str(char **list);

void	ft_print_bold_read(char *str, int fd);
bool	ft_is_valid_backslash(const char *str, int idx);
int		is_reserved_token(char *str, int idx);
bool	ft_is_special_char(const char *str, int idx, char *chars);

#endif
