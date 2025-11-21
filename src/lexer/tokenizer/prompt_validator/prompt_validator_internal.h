/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_validator_internal.h                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 21:04:48 by valero            #+#    #+#             */
/*   Updated: 2025/11/21 14:55:05 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_VALIDATOR_INTERNAL_H
# define PROMPT_VALIDATOR_INTERNAL_H

# include "libft.h"
# include "../../lexer_utils/lexer_utils.h"

/**
 * # t_char_checker
 *
 * Pequena estrutura auxiliar usada para isolar um contexto:
 * - `str`: string original.
 * - `idx`: índice de início da análise.
 * - `chars`: caracteres especiais que delimitam a estrutura.
 * - `is_special_char`: função usada para identificar esses caracteres.
 *
 * Serve como pacote de dados para `verify_char`.
 */
typedef struct s_char_checker
{
	const char	*str;
	int			idx;
	char		*chars;
	bool		(*is_special_char)(const char *str, int idx, char *chars);
}	t_char_checker;

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

void			jump_to_closing(
					const char *line, int *idx,
					int *inner_openning_idx, int (*validate)(const char *line));
void			fill_int_array(int *array, int len, int value);

int				validate_doublequotes(const char *line);
int				validate_backquotes(const char *line);
int				validate_dollar_parens(const char *line);
int				validate_parens(const char *line);
int				validate_singlequotes(const char *line);

#endif
