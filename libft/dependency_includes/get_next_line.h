/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 10:39:54 by brunofer          #+#    #+#             */
/*   Updated: 2025/09/02 18:28:41 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*gnl_substr(char const *s, unsigned int start, size_t len);
int		gnl_strlen(const char *str);
char	*gnl_strjoin(char *dst, char *src);
char	*gnl_strdup(const char *s);
void	*release_memory(void **ptr1, void **ptr2);
char	*get_next_line(int fd);

void	get_endl(char **buffer, int fd, int *last_read);
int		read_bytes_check(int read_bytes, int *last_read,
			char *buffer, char *temp);
void	clear_endl(char **static_buffer, char **buffer);
int		gnl_strrchar(char *str, char c);

#endif
