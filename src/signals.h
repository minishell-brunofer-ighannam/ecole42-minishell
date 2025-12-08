/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:15:38 by brunofer          #+#    #+#             */
/*   Updated: 2025/12/08 17:24:21 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>
# include <sys/ioctl.h>

# ifndef _POSIX_C_SOURCE
#  define _POSIX_C_SOURCE 200809L
# endif

// void	ft_handle_signals(void);
int		ft_get_sig(void);
void	ft_set_sig(int value);
void ft_init_sig_parent(void);
void ft_handle_sig_parent(int sig);
void ft_init_sig_child(void);
void ft_init_sig_pipe(void);
void ft_handle_sig_pipe(int sig);
void ft_init_sig_ignore(void);
void ft_handle_sig_ignore(int sig);
// int		signs(void);

#endif
