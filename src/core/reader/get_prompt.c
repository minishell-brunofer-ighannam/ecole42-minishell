/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 17:03:41 by brunofer          #+#    #+#             */
/*   Updated: 2025/12/09 22:57:14 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader_internal.h"

static char	*ft_bold(char *str);
static char	*ft_bold_green(char *str);
static char	*ft_bold_magenta(char *str);
static char	*ft_concat_prompt_parts(
				char *isa_nick, char *bruno_nick, char *minishell);

char	*ft_get_prompt(void)
{
	char	*isa_nick;
	char	*bruno_nick;
	char	*minishell;
	char	*prompt;

	isa_nick = ft_bold_green("isaghannam");
	bruno_nick = ft_bold_green("brunovalero");
	minishell = ft_bold_magenta("minishell");
	prompt = ft_concat_prompt_parts(isa_nick, bruno_nick, minishell);
	free(isa_nick);
	free(bruno_nick);
	free(minishell);
	return (prompt);
}

static char	*ft_bold_green(char *str)
{
	char	*prompt;
	char	*temp;

	prompt = ft_strjoin(TEXT_BOLD, TEXT_LIGHT_GREEN);
	temp = ft_strjoin(prompt, str);
	free(prompt);
	prompt = ft_strjoin(temp, TEXT_RESET);
	free(temp);
	return (prompt);
}

static char	*ft_bold_magenta(char *str)
{
	char	*prompt;
	char	*temp;

	prompt = ft_strjoin(TEXT_BOLD, TEXT_LIGHT_MAGENTA);
	temp = ft_strjoin(prompt, str);
	free(prompt);
	prompt = ft_strjoin(temp, TEXT_RESET);
	free(temp);
	return (prompt);
}

static char	*ft_bold(char *str)
{
	char	*prompt;
	char	*temp;

	temp = ft_strjoin(TEXT_BOLD, str);
	prompt = ft_strjoin(temp, TEXT_RESET);
	free(temp);
	return (prompt);
}

static char	*ft_concat_prompt_parts(
				char *isa_nick, char *bruno_nick, char *minishell)
{
	char	*prompt;
	char	*temp;
	char	*and;
	char	*semi_colom;
	char	*end;

	and = ft_bold("&");
	semi_colom = ft_bold(":");
	end = ft_bold("$> ");
	prompt = ft_strjoin(isa_nick, and);
	temp = ft_strjoin(prompt, bruno_nick);
	free(prompt);
	prompt = ft_strjoin(temp, semi_colom);
	free(temp);
	temp = ft_strjoin(prompt, minishell);
	free(prompt);
	prompt = ft_strjoin(temp, end);
	free(temp);
	free(and);
	free(semi_colom);
	free(end);
	return (prompt);
}
