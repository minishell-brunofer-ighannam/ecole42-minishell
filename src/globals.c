/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 13:13:21 by valero            #+#    #+#             */
/*   Updated: 2025/11/27 14:14:58 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>

static volatile sig_atomic_t g_sig;

int ft_get_sig(void)
{
    return (g_sig);
}

void ft_set_sig(int value)
{
    g_sig = (volatile sig_atomic_t)value;
}
