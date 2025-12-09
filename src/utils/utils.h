/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 16:25:02 by ighannam          #+#    #+#             */
/*   Updated: 2025/12/09 15:10:44 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "libft.h"
# include <stdbool.h>

# define TEXT_LIGHT_BLACK "\001\033[90m\002"
# define TEXT_LIGHT_RED "\001\033[91m\002"
# define TEXT_LIGHT_GREEN "\001\033[92m\002"
# define TEXT_LIGHT_YELLOW "\001\033[93m\002"
# define TEXT_LIGHT_BLUE "\001\033[94m\002"
# define TEXT_LIGHT_MAGENTA "\001\033[95m\002"
# define TEXT_LIGHT_CYAN "\001\033[96m\002"
# define TEXT_LIGHT_WHITE "\001\033[97m\002"

# define TEXT_RESET "\001\033[0m\002"
# define TEXT_BOLD "\001\033[1m\002"
# define TEXT_UNDERLINE "\001\033[4m\002"

void	ft_ordene_array_str(char **list);
void	ft_ordene_array_str_alpha(char **list);
void	ft_swap_array_str(int i, int j, char **list);
void	ft_clean_array_str(char **list);

void	ft_print_bold_read(char *str, int fd);
bool	ft_is_valid_backslash(const char *str, int idx);
int		is_reserved_token(char *str, int idx);
bool	ft_is_special_char(const char *str, int idx, char *chars);

#endif
