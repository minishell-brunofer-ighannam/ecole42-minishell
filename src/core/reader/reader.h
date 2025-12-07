/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 17:02:39 by brunofer          #+#    #+#             */
/*   Updated: 2025/12/07 17:41:15 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READER_H
# define READER_H

# include <readline/readline.h>
# include <readline/history.h>

void	ft_reader(
			void (*executer)(const char *line, void *exec),
			void *(*create_exec)(char **envp), char **envp);

#endif
