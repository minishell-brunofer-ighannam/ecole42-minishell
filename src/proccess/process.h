/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 13:42:13 by valero            #+#    #+#             */
/*   Updated: 2025/11/09 17:08:21 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_H
# define PROCESS_H

# include "libft.h"
# include <stdbool.h>
# include <sys/types.h>
# include <unistd.h>

/**
 * # t_child_process
 *
 * ---
 *
 * Represents a child process with its pipes, PID, and cleanup method.
 *
 * ## Members
 * - `int **pipes`: Array of pipe descriptors `[read, write]`.
 * - `int pid`: Process ID returned by fork().
 * - `void *(*destroy)(...)`: Function to free memory and close pipes.
 *
 * ## Notes
 * - Pipes are allocated dynamically according to `pipes_amount`.
 * - Use `destroy` to safely free resources.
 */
typedef struct s_child_process					t_child_process;
struct s_child_process
{
	int		**pipes;
	int		pid;
	void	*(*destroy)(t_child_process **self_ref, bool close_pipes);
};

/**
 * # t_child_process_callback_args
 *
 * ---
 *
 * Holds generic arguments for pipe management and child task callbacks.
 *
 * ## Members
 * - `void *manage_pipes_arg`: Argument passed to `manage_pipes` callback.
 * - `void *(*free_manage_pipes_arg)(void *)`: Function to free `manage_pipes_arg`.
 * - `void *child_task_arg`: Argument passed to `child_task` callback.
 * - `void *(*free_child_task_arg)(void *)`: Function to free `child_task_arg`.
 *
 * ## Notes
 * - Allows flexible data passing without fixed types.
 */
typedef struct s_child_process_callback_args	t_child_process_callback_args;
struct s_child_process_callback_args
{
	void	*manage_pipes_arg;
	void	*(*free_manage_pipes_arg)(void *manage_pipes_arg);

	void	*child_task_arg;
	void	*(*free_child_task_arg)(void *child_task_arg);
};


/**
 * # t_child_process_callbacks
 *
 * ---
 *
 * Stores the callback functions for pipe management and child task execution.
 *
 * ## Members
 * - `void *(*manage_pipes)(...)`: Optional function to prepare or manage pipes.
 * - `void *(*child_task)(...)`: Function executed by the child process.
 * - `t_child_process_callback_args args`: Arguments for both callbacks.
 *
 * ## Notes
 * - `child_task` is mandatory; `manage_pipes` is optional.
 */
typedef struct s_child_process_callbacks		t_child_process_callbacks;
struct s_child_process_callbacks
{
	void							*(*manage_pipes)(
			int **fd_pipes,
			t_child_process_callback_args args
			);
	void							*(*child_task)(
			t_child_process *process,
			t_child_process_callback_args args
			);
	t_child_process_callback_args	args;
};

#endif
