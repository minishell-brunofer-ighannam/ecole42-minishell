/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 10:39:54 by brunofer          #+#    #+#             */
/*   Updated: 2025/09/02 16:37:01 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strlen(const char *str);
char	*ft_strjoin(char *dst, char *src);
char	*ft_strdup(const char *s);
void	*release_memory(void **ptr1, void **ptr2);
char	*get_next_line(int fd);

void	get_endl(char **buffer, int fd, int *last_read);
int		read_bytes_check(int read_bytes, int *last_read,
			char *buffer, char *temp);
void	clear_endl(char **static_buffer, char **buffer);
int		ft_strrchar(char *str, char c);

#endif
