/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_i.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:16:57 by brunofer          #+#    #+#             */
/*   Updated: 2025/12/09 18:08:29 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

static volatile sig_atomic_t	g_sig;

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
