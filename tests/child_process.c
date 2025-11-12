/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 21:20:04 by valero            #+#    #+#             */
/*   Updated: 2025/11/12 12:27:28 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tests.h"

static void	test_child_process_creation(void);
static void	test_child_process_pipe_communication(void);
static void	test_child_process_execve_ls(void);

int	main(void)
{
	test_child_process_creation();
	test_child_process_pipe_communication();
	test_child_process_execve_ls();
}

static void	*child_task_func1(
	t_child_process *p,
	t_child_process_callback_args a)
{
	p->destroy(&p, true);
	(void)a;
	return (NULL);
}

static void	test_child_process_creation(void)
{
	t_test						test;
	t_child_process				*process;
	t_child_process_callbacks	callbacks;
	int							tests_ok;

	test.teste_number = 1;
	tests_ok = 0;
	test.test_input = "create a simple child process";
	// Callback simples que não faz nada
	callbacks.child_task = child_task_func1;
	callbacks.manage_pipes = NULL;
	// Deixa os args nulos
	ft_bzero(&callbacks.args, sizeof(callbacks.args));
	process = ft_child_process(1, callbacks);
	// Verifica se estrutura foi criada
	tests_ok += (process != NULL);
	// Verifica se há pipes
	tests_ok += (process && process->pipes && process->pipes[0]);
	// Verifica se PID > 0 (pai)
	tests_ok += (process && process->pid > 0);
	// Limpa memória
	process->destroy(&process, true);
	tests_ok += (process == NULL);

	test.test_ok = (tests_ok == 4);
	print_test(test);
}

static void	*child_task_func2(
	t_child_process *p,
	t_child_process_callback_args a)
{
	(void)a;
	char msg[] = "hello from child";
	write(p->pipes[0][1], msg, sizeof(msg));
	p->destroy(&p, true);
	return (NULL);
}

static void	test_child_process_pipe_communication(void)
{
	t_test						test;
	t_child_process				*process;
	t_child_process_callbacks	callbacks;
	char						buffer[64];
	int							tests_ok;

	test.teste_number = 2;
	tests_ok = 0;
	test.test_input = "pipe communication (child writes, parent reads)";
	// Callback: o filho escreve no pipe
	callbacks.child_task = child_task_func2;
	callbacks.manage_pipes = NULL;
	// Deixa os args nulos
	ft_bzero(&callbacks.args, sizeof(callbacks.args));
	process = ft_child_process(1, callbacks);
	// Pai lê a mensagem
	read(process->pipes[0][0], buffer, sizeof(buffer));

	tests_ok += strstr(buffer, "hello from child") != NULL;
	// Limpa memória
	process->destroy(&process, true);
	tests_ok += (process == NULL);

	test.test_ok = (tests_ok == 2);
	print_test(test);
}

struct command
{
	char	*command_path;
	char	**command_argv;
};

void	*free_command(void *cmd_ptr)
{
	int				i;
	struct command	*command;

	command = (struct command *)cmd_ptr;
	if (!command)
		return (NULL);
	if (command->command_argv)
	{
		i = -1;
		while (command->command_argv[++i])
			free(command->command_argv[i]);
		free(command->command_argv);
	}
	if (command->command_path)
		free(command->command_path);
	free(command);
	return (NULL);
}

void	*child_task_func(
			t_child_process *process,
			t_child_process_callback_args args)
{
	struct command	*task_arg;
	char			*msg;

	task_arg = (struct command *)args.child_task_arg;
	if (!task_arg)
	{
		process->destroy(&process, true);
		exit(1);
	}
	// Redireciona stdout e stderr
	dup2(process->pipes[1][1], STDOUT_FILENO);
	dup2(process->pipes[0][1], STDERR_FILENO);
	// Fecha descritores não usados (opcional)
	process->destroy(&process, true);
	// executa comando
	execve(task_arg->command_path, task_arg->command_argv, NULL);
	// Se execve falhar
	msg = "execve failed\n";
	write(process->pipes[0][1], msg, sizeof(msg));
	args.free_child_task_arg(args.child_task_arg);
	process->destroy(&process, true);
	exit(1);
}

static void	test_child_process_execve_ls(void)
{
	t_test						test;
	t_child_process				*process;
	t_child_process_callbacks	callbacks;
	struct command				*command;
	int							tests_ok = 0;
	char						*line;

	test.teste_number = 5;
	test.test_input = "child process executes ls -la via execve";
	// Cria struct command para o comando ls -la
	command = malloc(sizeof(struct command));
	command->command_path = strdup("/bin/ls");
	command->command_argv = ft_split("ls -la", ' ');
	// Preenche callbacks
	callbacks.manage_pipes = NULL;
	callbacks.child_task = child_task_func;
	callbacks.args.child_task_arg = command;
	callbacks.args.free_child_task_arg = free_command;
	// Cria processo filho com 2 pipes
	process = ft_child_process(2, callbacks);
	// libera a memoria alocada
	free(command->command_path);
	ft_destroy_char_matrix(&command->command_argv);
	free(command);
	// Lê saída do comando pelo pipe[1]
	fflush(stdout);
	line = get_next_line(process->pipes[1][0]);
	while (line)
	{
		if (strstr(line, "Makefile"))
		{
			tests_ok = 1;
			free(line);
			get_next_line(-1);
			break ;
		}
		free(line);
		line = get_next_line(process->pipes[1][0]);
	}
	// Destroi processo (filho já destruiu, mas garante cleanup)
	process->destroy(&process, true);

	test.test_ok = tests_ok == 1;
	print_test(test);
}
