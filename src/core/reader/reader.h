/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 17:02:39 by brunofer          #+#    #+#             */
/*   Updated: 2025/12/08 15:35:42 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READER_H
# define READER_H

# include <readline/history.h>
# include <readline/readline.h>

int	ft_reader(int (*executer)(const char *line, void *exec),
		void *(*create_exec)(char **envp),
		void (*destroy_exec)(void *exec), char **envp);

#endif
