/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 13:44:16 by valero            #+#    #+#             */
/*   Updated: 2025/11/09 16:50:24 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"

static void				*ft_destroy_child_process(
							t_child_process **self_ref,
							bool close_pipes);
static t_child_process	*ft_create_child_process_structure(
							int pipes_amount,
							t_child_process *process);

/**
 * # ft_child_process
 *
 * ---
 *
 * Creates a child process with pipes and executes the provided task.
 *
 * ## Logic
 * - Checks if `child_task` callback is provided.
 * - Creates `t_child_process` structure with requested pipes.
 * - Calls `manage_pipes` callback if provided.
 * - Calls `fork()` to spawn the child process.
 *   - Child executes `child_task` and exits.
 *   - Parent keeps the process structure.
 *
 * ## Parameters
 * - `pipes_amount`: Number of pipes to create.
 * - `callbacks`: Struct containing `child_task`, `manage_pipes`, and arguments.
 *
 * ## Returns
 * - Pointer to the created `t_child_process`.
 * - NULL if creation or fork fails.
 *
 * ## Notes
 * - Use `destroy` to free resources if needed.
 */
t_child_process	*ft_child_process(
					int pipes_amount,
					t_child_process_callbacks callbacks)
{
	t_child_process	*process;

	if (!callbacks.child_task)
		return (NULL);
	process = ft_create_child_process_structure(pipes_amount, NULL);
	if (!process)
		return (NULL);
	if (callbacks.manage_pipes)
		callbacks.manage_pipes(process->pipes, callbacks.args);
	process->pid = fork();
	if (process->pid < 0)
		return (process->destroy(&process, true));
	if (!process->pid)
	{
		callbacks.child_task(process, callbacks.args);
		exit(0);
	}
	return (process);
}

/**
 * # ft_create_child_process_structure
 *
 * ---
 *
 * Allocates and initializes a `t_child_process` structure with pipes.
 *
 * ## Logic
 * - Allocates memory for `t_child_process`.
 * - Allocates array of `pipes_amount` pipes.
 * - Calls `pipe()` for each pipe.
 * - Cleans up if any allocation or pipe creation fails.
 *
 * ## Parameters
 * - `pipes_amount`: Number of pipes to create.
 * - `process`: Optional preallocated structure (usually NULL).
 *
 * ## Returns
 * - Pointer to initialized `t_child_process`.
 * - NULL if allocation or pipe creation fails.
 */
static t_child_process	*ft_create_child_process_structure(
							int pipes_amount,
							t_child_process *process)
{
	int	idx;

	if (!pipes_amount)
		return (NULL);
	process = ft_calloc(1, sizeof(t_child_process));
	if (!process)
		return (NULL);
	process->destroy = ft_destroy_child_process;
	process->pipes = ft_calloc(pipes_amount + 1, sizeof(int *));
	if (!process->pipes)
		return (ft_destroy_child_process(&process, false));
	idx = -1;
	while (++idx < pipes_amount)
	{
		process->pipes[idx] = ft_calloc(2, sizeof(int));
		if (!process->pipes[idx])
			return (ft_destroy_child_process(&process, false));
		if (pipe(process->pipes[idx]) < 0)
		{
			free(process->pipes[idx]);
			process->pipes[idx] = NULL;
			return (ft_destroy_child_process(&process, true));
		}
	}
	return (process);
}

/**
 * # ft_destroy_child_process
 *
 * ---
 *
 * Frees memory of `t_child_process` and closes pipes if requested.
 *
 * ## Logic
 * - Iterates all pipes and closes them if `close_pipes` is true.
 * - Frees memory of each pipe and the pipes array.
 * - Frees the `t_child_process` structure.
 * - Sets external pointer to NULL to avoid dangling references.
 *
 * ## Parameters
 * - `self_ref`: Pointer to the process structure pointer.
 * - `close_pipes`: Flag to close pipes before freeing memory.
 *
 * ## Returns
 * - NULL always.
 *
 * ## Notes
 * - Safe to call on partially initialized structures.
 */
static void	*ft_destroy_child_process(
				t_child_process **self_ref,
				bool close_pipes)
{
	t_child_process	*self;
	int				idx;

	if (!self_ref || !*self_ref)
		return (NULL);
	self = *self_ref;
	if (self->pipes)
	{
		idx = -1;
		while (self->pipes[++idx])
		{
			if (close_pipes)
			{
				close(self->pipes[idx][0]);
				close(self->pipes[idx][1]);
			}
			free(self->pipes[idx]);
		}
		free(self->pipes);
	}
	free(self);
	*self_ref = NULL;
	return (NULL);
}
