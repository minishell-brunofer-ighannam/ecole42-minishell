/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:16:57 by brunofer          #+#    #+#             */
/*   Updated: 2025/11/09 16:56:24 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

/**
 * # Signal handler function.
 *
 * ---
 *
 * This function is called automatically when a signal is received
 * by the process. It captures the received signal number and stores
 * it in the global variable `g_sig` so that other parts of the program
 * can check which signal was triggered and respond accordingly.
 *
 * @param sig The signal number received by the process.
 */
void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("^C", 1);
		ft_putstr_fd("\n", 1);
		ft_putstr_fd(PROMPT, 1);
	}
	if (sig == SIGTERM)
		printf("SIGTERM: %d\n", sig);
	if (sig == SIGQUIT)
		printf("SIGQUIT: %d\n", sig);
	set_sig(sig);
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
void	handle_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = sig_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGTERM, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

// int	signs(void)
// {

// 	printf("sig: %d \n", g_sig);
// 	rl_done = 1;
// 	if (g_sig == SIGINT || g_sig == SIGTERM)
// 		return (0);
// 	return (1);
// }
