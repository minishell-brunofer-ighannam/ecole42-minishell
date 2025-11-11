/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 16:27:17 by brunofer          #+#    #+#             */
/*   Updated: 2025/11/11 16:37:55 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static int	get_end(
				const char *str,
				int idx,
				bool (*is_special_char)(const char *str, int idx, char *chars),
				char *chars);
static int	verify_char(t_char_checker checker, int (*verify)(const char *line));
static int	ft_get_smaller(int len, int *arr);

int	ft_reader(void)
{
	char	*line;

	rl_catch_signals = 0;
	line = readline(PROMPT);
	while (line)
	{
		if (!line)
		{
			free(line);
			break ;
		}
		printf("line: %s\n", line);
		add_history(line);
		free(line);
		line = readline(PROMPT);
	}

	return (1);
}

int	verify_prompt(const char *line)
{
	int	error_index;

	error_index = -1;
	error_index = verify_parenthesis(line);
	if (error_index > -1)
		return (error_index);
	error_index = verify_doublequotes(line);
	if (error_index > -1)
		return (error_index);
	error_index = verify_backquotes(line);
	if (error_index > -1)
		return (error_index);
	return (error_index);
}

bool	ft_is_special_char(const char *str, int idx, char *chars)
{
	bool	is_chars;

	is_chars = !!ft_strchr(chars, str[idx]);
	if (!idx && (is_chars))
		return (true);
	if (!ft_is_valid_backslash(str, idx - 1) && (is_chars))
		return (true);
	return (false);
}

int	verify_doublequotes(const char *line)
{
	int	i;
	int	open_quote_index;
	int	other_openning_idx;

	other_openning_idx = -1;
	open_quote_index = -1;
	i = -1;
	while (line[++i])
	{
		if (open_quote_index > -1)
		{
			if (ft_is_special_char(line, i, "`"))
			{
				other_openning_idx = verify_char(ft_char_checker(line, i, "`", ft_is_special_char), verify_backquotes);
				if (other_openning_idx > -1)
					other_openning_idx = (i + other_openning_idx);
				else
					i = get_end(line, i, ft_is_special_char, "\"");
			}
		}
		if (ft_is_special_char(line, i, "\""))
		{
			if (open_quote_index == -1)
				open_quote_index = i;
			else
				open_quote_index = -1;
		}
	}
	if (open_quote_index == -1)
		return (other_openning_idx);
	return (open_quote_index);
}

int	verify_backquotes(const char *line)
{
	int		i;
	int		open_backquotes_index;
	int		other_openning_idx[2];

	other_openning_idx[0] = -1;
	other_openning_idx[1] = -1;
	open_backquotes_index = -1;
	i = -1;
	while (line[++i])
	{
		if (open_backquotes_index > -1)
		{
			if (ft_is_special_char(line, i, "\""))
			{
				other_openning_idx[0] = verify_char(ft_char_checker(line, i, "\"", ft_is_special_char), verify_doublequotes);
				if (other_openning_idx[0] > -1)
					other_openning_idx[0] = (i + other_openning_idx[0]);
				else
					i = get_end(line, i, ft_is_special_char, "\"");
			}
			else if (ft_is_special_char(line, i, "()"))
			{
				other_openning_idx[1] = verify_char(ft_char_checker(line, i, ")", ft_is_special_char), verify_parenthesis);
				if (other_openning_idx[1] > -1)
					other_openning_idx[1] = (i + other_openning_idx[1]);
				else
					i = get_end(line, i, ft_is_special_char, "()");
			}
		}
		if (ft_is_special_char(line, i, "`"))
		{
			if (open_backquotes_index == -1)
				open_backquotes_index = i;
			else
				open_backquotes_index = -1;
		}
	}
	if (open_backquotes_index == -1)
		return (ft_get_smaller(2, other_openning_idx));
	return (open_backquotes_index);
}

static int	verify_char(t_char_checker checker, int (*verify)(const char *line))
{
	char	*sub;
	int		openning_idx;

	sub = ft_substr(checker.str, checker.idx,
			get_end(checker.str, checker.idx,
				checker.is_special_char, checker.chars) + 1 - checker.idx);
	openning_idx = verify(sub);
	free(sub);
	if (openning_idx > -1)
		return (openning_idx);
	return (-1);
}

int	verify_parenthesis(const char *line)
{
	int		i;
	int		open_parenthesis_index;
	int		other_openning_idx[3];

	other_openning_idx[0] = -1;
	other_openning_idx[1] = -1;
	other_openning_idx[2] = -1;
	open_parenthesis_index = -1;
	i = -1;
	while (line[++i])
	{
		if (open_parenthesis_index > -1)
		{
			if (ft_is_special_char(line, i, "\""))
			{
				other_openning_idx[0] = verify_char(ft_char_checker(line, i, "\"", ft_is_special_char), verify_doublequotes);
				if (other_openning_idx[0] > -1)
					other_openning_idx[0] = i + other_openning_idx[0];
				else
					i = get_end(line, i, ft_is_special_char, "\"");
			}
			else if (ft_is_special_char(line, i, "("))
			{
				other_openning_idx[1] = verify_char(ft_char_checker(line, i, ")", ft_is_special_char), verify_parenthesis);
				if (other_openning_idx[1] > -1)
					other_openning_idx[1] = i + other_openning_idx[1];
				else
					i = get_end(line, i, ft_is_special_char, ")");
			}
			else if (ft_is_special_char(line, i, "`"))
			{
				other_openning_idx[2] = verify_char(ft_char_checker(line, i, "`", ft_is_special_char), verify_backquotes);
				if (other_openning_idx[2] > -1)
					other_openning_idx[2] = i + other_openning_idx[2];
				else
					i = get_end(line, i, ft_is_special_char, "\"");
			}
		}
		if (ft_is_special_char(line, i, "()"))
		{
			if (line[i] == '(')
				open_parenthesis_index = i;
			if (!open_parenthesis_index && line[i] == ')')
				return (i);
			if (open_parenthesis_index && line[i] == ')')
				open_parenthesis_index = -1;
		}
	}
	if (open_parenthesis_index == -1)
		return (ft_get_smaller(3, other_openning_idx));
	return (open_parenthesis_index);
}

static int	get_end(
				const char *str,
				int idx,
				bool (*is_special_char)(const char *str, int idx, char *chars),
				char *chars)
{
	int	i;

	i = idx;
	while (str[++i])
	{
		if (is_special_char(str, i, chars))
		{
			if (str[i] == chars[0])
				return (i);
		}
	}
	return (i);
}

t_char_checker	ft_char_checker(const char *str, int idx, char *chars,
					bool (*is_special_char)(
						const char *str, int idx, char *chars))
{
	t_char_checker	checker;

	checker.str = str;
	checker.idx = idx;
	checker.chars = chars;
	checker.is_special_char = is_special_char;
	return (checker);
}

static int	ft_get_smaller(int len, int *arr)
{
	int	smaller;

	smaller = INT_MAX;
	while (--len >= 0)
		if (arr[len] < smaller)
			smaller = arr[len];
	return (smaller);
}
