/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 10:40:10 by brunofer          #+#    #+#             */
/*   Updated: 2025/08/05 09:27:49 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*static_buffer[1024];
	int			last_read;

	last_read = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = ft_strdup("");
	get_endl(&buffer, fd, &last_read);
	if (last_read < 0)
		return (release_memory((void **) &static_buffer[fd], (void **) NULL));
	clear_endl(&static_buffer[fd], &buffer);
	if (!ft_strlen(buffer))
		return (
			release_memory((void **) &static_buffer[fd], (void **) &buffer)
		);
	if (last_read && !ft_strlen(static_buffer[fd]))
		release_memory((void **) &static_buffer[fd], (void **) NULL);
	return (buffer);
}

void	get_endl(char **buffer, int fd, int *last_read)
{
	char	*temp;
	char	*joined;
	int		endl_found;
	int		read_bytes;

	endl_found = 0;
	while (!endl_found)
	{
		read_bytes = 0;
		temp = ft_strdup(*buffer);
		release_memory((void **) buffer, (void **) NULL);
		*buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
		read_bytes = read(fd, *buffer, BUFFER_SIZE);
		if (!read_bytes_check(read_bytes, last_read, *buffer, temp))
			return ;
		(*buffer)[read_bytes] = '\0';
		if (ft_strrchar(*buffer, '\n') || !read_bytes)
			endl_found = 1;
		if (read_bytes > 0 || temp)
			joined = ft_strjoin(temp, *buffer);
		else
			joined = ft_strdup("");
		release_memory((void **) buffer, (void **) &temp);
		*buffer = joined;
	}
}

int	read_bytes_check(int read_bytes, int *last_read,
				char *buffer, char *temp)
{
	if (read_bytes == 0)
		*last_read = 1;
	else if (read_bytes < 0)
	{
		release_memory((void **) &buffer, (void **) &temp);
		*last_read = -1;
		return (0);
	}
	return (1);
}

void	clear_endl(char **static_buffer, char **buffer)
{
	char	*full_str;
	int		i;

	if (!*static_buffer)
		*static_buffer = ft_strdup("");
	full_str = ft_strjoin(*static_buffer, *buffer);
	i = -1;
	while (full_str[++i])
		if (full_str[i] == '\n')
			break ;
	release_memory((void **) buffer, (void **) static_buffer);
	if (!ft_strlen(full_str))
	{
		*buffer = full_str;
		return ;
	}
	if (ft_strlen(full_str) > (i + 1))
		*static_buffer = ft_substr(full_str, i + 1, ft_strlen(full_str));
	else
		*static_buffer = ft_strdup("");
	*buffer = ft_substr(full_str, 0, i + 1);
	release_memory((void **) &full_str, (void **) NULL);
}

int	ft_strrchar(char *str, char c)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == c)
			return (1);
	return (0);
}
