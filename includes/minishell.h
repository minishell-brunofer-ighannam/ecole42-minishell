/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 12:57:32 by brunofer          #+#    #+#             */
/*   Updated: 2025/12/01 15:57:24 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <termios.h>
# include <unistd.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/types.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include "libft.h"
# include "../src/signals.h"
# include "../src/core/lexer/lexer.h"
# include "../src/data_structures/data_structures.h"
# include "../src/core/executer/process/process.h"
# include "../src/core/executer/builtins/builtins.h"
# include "../src/core/executer/env/env.h"
# include "../src/core/executer/executer.h"
# include "../src/utils/utils.h"
# include "../src/core/executer/mapper/mapper.h"

# define PROMPT_GREEN	"\001\033[32m\002"
# define PROMPT_MAGENTA	"\001\033[35m\002"
# define PROMPT_RESET	"\001\033[0m\002"
# define PROMPT_ISA		PROMPT_GREEN"isaghannam"PROMPT_RESET
# define PROMPT_BRUNO	PROMPT_GREEN"brunovalero"PROMPT_RESET
# define PROMPT_SHELL	PROMPT_MAGENTA"minishell"PROMPT_RESET
# define PROMPT PROMPT_ISA"&"PROMPT_BRUNO":"PROMPT_SHELL"$> "

int		get_sig(void);
void	set_sig(int value);

#endif
