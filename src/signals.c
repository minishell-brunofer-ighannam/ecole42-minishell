/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:16:57 by brunofer          #+#    #+#             */
/*   Updated: 2025/12/09 12:47:29 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

static volatile	sig_atomic_t g_sig;

int	ft_get_sig(void)
{
	return (g_sig);
}

void	ft_set_sig(int value)
{
	g_sig = (volatile sig_atomic_t)value;
}

void	ft_init_sig_parent(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = ft_handle_sig_parent;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_handle_sig_parent(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	//rl_done = 1;
	ft_set_sig(SIGINT);
}

void	ft_init_sig_ignore(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = ft_handle_sig_ignore;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_handle_sig_ignore(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	//rl_redisplay();
	//rl_done = 1;
	ft_set_sig(SIGINT);
}

void	ft_init_sig_heredoc(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = ft_handle_sig_heredoc;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_handle_sig_heredoc(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	//ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	rl_done = 1;
	ft_set_sig(SIGINT);
}

void	ft_init_sig_child(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = SIG_DFL;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

/**
 * # Sets up custom signal handlers for the program.
 *
 * ---
 *
 * This function initializes and configures the signal handling behavior
 * for specific signals. It assigns the `sig_handler` function as the handler
 * for both SIGINT and SIGTERM, ensuring that when these signals are received,
 * they are properly captured and stored for later processing.
 *
 * The signal mask is cleared to allow all signals during handler execution,
 * and no special flags are set.
 */
// void	ft_handle_signals(void)
// {
// 	struct sigaction	sa;

// 	sa.sa_handler = sig_handler;
// 	sigemptyset(&sa.sa_mask);
// 	sa.sa_flags = 0;
// 	sigaction(SIGINT, &sa, NULL);
// 	sigaction(SIGTERM, &sa, NULL);
// 	sigaction(SIGQUIT, &sa, NULL);
// }

// int	signs(void)
// {

// 	printf("sig: %d \n", g_sig);
// 	rl_done = 1;
// 	if (g_sig == SIGINT || g_sig == SIGTERM)
// 		return (0);
// 	return (1);
// }
