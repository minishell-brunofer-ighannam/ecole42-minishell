/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 12:57:32 by brunofer          #+#    #+#             */
/*   Updated: 2025/12/09 12:51:14 by brunofer         ###   ########.fr       */
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
# include "../src/core/reader/reader.h"

#endif
