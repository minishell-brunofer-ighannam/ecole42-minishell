/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_print_error.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 18:18:11 by ighannam          #+#    #+#             */
/*   Updated: 2025/12/13 18:21:09 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

void	ft_print_error_redirect(char *error, t_redirect *content)
{
	char	*temp;
	char	*msg;

	temp = ft_strjoin("minishell: ", content->file);
	msg = ft_strjoin(temp, ": ");
	free(temp);
	temp = ft_strjoin(msg, error);
	ft_putendl_fd(temp, STDERR_FILENO);
	free(temp);
	free(msg);
}
