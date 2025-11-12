/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_validator_internal.h                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 21:04:48 by valero            #+#    #+#             */
/*   Updated: 2025/11/11 22:33:37 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_VALIDATOR_INTERNAL_H
# define PROMPT_VALIDATOR_INTERNAL_H

# include "libft.h"
# include "../../lexer_utils/lexer_utils.h"

typedef struct s_char_checker	t_char_checker;
struct s_char_checker
{
	const char	*str;
	int			idx;
	char		*chars;
	bool		(*is_special_char)(const char *str, int idx, char *chars);
};

int				ft_get_smaller(int len, int *arr);
int				get_end(const char *str, int idx,
					bool (*is_special_char)(
						const char *str, int idx, char *chars),
					char *chars);
int				verify_char(
					t_char_checker checker,
					int (*verify)(const char *line));
t_char_checker	ft_char_checker(const char *str, int idx, char *chars,
					bool (*is_special_char)(
						const char *str, int idx, char *chars));

int				validate_doublequotes(const char *line);
int				validate_backquotes(const char *line);
int				validate_dollar_parens(const char *line);
int				validate_parens(const char *line);

#endif
