/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 14:40:44 by ighannam          #+#    #+#             */
/*   Updated: 2025/11/28 16:42:51 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H

# include "../../data_structures/data_structures.h"
# include "../../signals.h"
# include "../lexer/lexer.h"
# include "builtins/builtins.h"
# include "env/env.h"
# include "process/process.h"
# include <fcntl.h>
# include <readline/readline.h>
# include <stdio.h>
# include <sys/stat.h>
# include <sys/wait.h>

typedef enum e_node_type	t_node_type;
enum						e_node_type
{
	NODE_CMD = 'c' << 16 | 'm' << 8 | 'd',

	NODE_PIPE = '|',
	NODE_OR = '|' << 8 | '|',
	NODE_AND = '&' << 8 | '&',

	NODE_SUBSHELL = '(',

	NODE_REDIRECT_IN = '<',
	NODE_REDIRECT_OUT = '>',
	NODE_HERE_DOC_IN = '<' << 8 | '<',
	NODE_APPEND_OUT = '>' << 8 | '>',
};

typedef struct s_node
{
	t_node_type type; // Você preenche
	t_token **token;  // Você preenche
	char					**argv;
	// Eu fiz a função para popular o argv. Vc pode só setar como NULL (ft_calloc)
	struct s_node *left;  // Você preenche
	struct s_node *right; // Você preenche
	t_linkedlist_array		*ht_env;
	// A ht_env você já inicia e coloca o ponteiro em todos os nós.
	t_linkedlist			*redirect;
	// Essa linkedlist eu inicio. Vc pode só setar ela como NULL (ft_calloc)
	char					**envp;
}							t_node;

typedef struct s_redirect
{
	t_node_type				type;
	const char				*file;
}							t_redirect;

// TREE
int							ft_execute_tree(t_node *node);
int							ft_execute_node(t_node *node);

// CMD
char						*ft_find_path(t_linkedlist_array *ht_env,
								char *cmd);
int							ft_execute_cmd(t_node *node);
void						*ft_child_task_func_cmd(t_child_process *process,
								t_child_process_callback_args args);
int							ft_expand_tokens(t_node *node);
void						ft_built_args(t_node *node);

// CMD BUILTIN
int							ft_execute_builtin(t_node *node);

// REDIRECT
int							ft_is_redirect(t_node *node);
int							ft_visit_redirect(t_node *node);
int							ft_execute_redirect(t_node *node);
int							ft_execute_redirect_in(t_linkedlist_node *node);
int							ft_execute_redirect_out(t_linkedlist_node *node);
int							ft_execute_append_out(t_linkedlist_node *node);

// HEREDOC
int							ft_execute_heredocs(t_node *node);
char						*ft_generate_temp_file(void);
void						ft_dfs_find_heredoc(t_linkedlist *heredoc,
								t_node *node);
t_linkedlist				*ft_find_all_heredoc(t_node *node);

// PIPE
int							ft_execute_pipe(t_node *node);

// SUBSHELL
int							ft_execute_subshell(t_node *node);

// AND OR
int							ft_execute_and(t_node *node);
int							ft_execute_or(t_node *node);

#endif
