/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 12:57:32 by brunofer          #+#    #+#             */
/*   Updated: 2025/11/09 16:33:41 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct s_env t_env;

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
# include "libft.h"
# include "../src/signals.h"
# include "../src/lexer/lexer.h"
# include "../src/linkedlist_array/linkedlist_array.h"
# include "../src/proccess/process.h"
#include "../src/hashtable/hashtable.h"

/* ****************************   BUILTINS   ****************************** */
/*env*/
void	ft_env(t_env **env);
/*unset*/
void	ft_unset(t_env **env, char *key);
/*export*/
void	ft_export(t_env **env, char *key, char *value);


# define PROMPT_GREEN	"\033[32m"
# define PROMPT_MAGENTA	"\033[35m"
# define PROMPT_RESET	"\033[0m"
# define PROMPT_ISA		PROMPT_GREEN"isaghannam"PROMPT_RESET
# define PROMPT_BRUNO	PROMPT_GREEN"brunovalero"PROMPT_RESET
# define PROMPT_SHELL	PROMPT_MAGENTA"minishell"PROMPT_RESET
# define PROMPT PROMPT_ISA"&"PROMPT_BRUNO":"PROMPT_SHELL"$> "

int		get_sig(void);
void	set_sig(int value);

#endif
