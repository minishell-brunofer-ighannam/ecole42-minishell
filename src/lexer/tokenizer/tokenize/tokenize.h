/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 13:58:37 by brunofer          #+#    #+#             */
/*   Updated: 2025/11/14 20:49:05 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZE_H
# define TOKENIZE_H

# include <stdbool.h>
# include "./expandable_object/expandable_object.h"

typedef enum e_token_type			t_token_type;
enum e_token_type
{
	TOKEN_UNKNOWN = 'u' << 16 | 'n' << 8 | 'k',

	TOKEN_CMD = 'c' << 16 | 'm' << 8 | 'd',
	TOKEN_ARG = 'a' << 16 | 'r' << 8 | 'g',

	TOKEN_PIPE = '|',
	TOKEN_OR = '|' << 8 | '|',
	TOKEN_AND = '&' << 8 | '&',

	TOKEN_SEMICOLON = ';',
	TOKEN_BACKGROUND = '&',

	TOKEN_PAREN_OPEN = '(',
	TOKEN_PAREN_CLOSE = ')',

	TOKEN_REDIRECT_IN = '<',
	TOKEN_REDIRECT_OUT = '>',
	TOKEN_HERE_DOC_IN = '<' << 8 | '<',
	TOKEN_APPEND_OUT = '>' << 8 | '>',
	TOKEN_REDIRECT_IN_OUT = '<' << 8 | '>',
	TOKEN_REDIRECT_FORCE_OUT = '>' << 8 | '|',
	TOKEN_REDIRECT_ERR_OUT = '2' << 8 | '>',
	TOKEN_REDIRECT_OUT_ERR = '&' << 8 | '>',
	TOKEN_REDIRECT_OUT_MERGE = '>' << 8 | '&',

	TOKEN_END = '\0'
};

typedef struct s_token				t_token;
struct s_token
{
	const char			*value;
	char				*last_build;
	t_token_type		type;
	int					position;
	int					coord_in_src[2];
	bool				sintaxe_error;
	bool				feature_out_of_scope;
	char				*(*expand_var)(const char *token);
	char				**(*expand_glob)(const char *token);
	char				*(*build_expansion)(t_token *self);
	t_expandable_object	*expandable_object;
};

typedef struct s_expander_callbacks	t_expander_callbacks;
struct s_expander_callbacks
{
	char	*(*expand_var)(const char *token);
	char	**(*expand_glob)(const char *token);
};

#endif
