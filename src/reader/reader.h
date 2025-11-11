/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 12:58:09 by valero            #+#    #+#             */
/*   Updated: 2025/11/11 14:25:28 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READER_H
# define READER_H

typedef struct s_char_checker	t_char_checker;
struct s_char_checker
{
	const char	*str;
	int			idx;
	char		*chars;
	bool		(*is_special_char)(const char *str, int idx, char *chars);
};

t_char_checker	ft_char_checker(const char *str, int idx, char *chars,
					bool (*is_special_char)(
						const char *str, int idx, char *chars));
int				verify_doublequotes(const char *line);
int				verify_backquotes(const char *line);
int				verify_parenthesis(const char *line);
int				verify_prompt(const char *line);

#endif
