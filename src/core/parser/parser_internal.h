/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_internal.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 00:14:45 by valero            #+#    #+#             */
/*   Updated: 2025/11/25 23:49:23 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_INTERNAL_H
# define PARSER_INTERNAL_H

# include "parser.h"

typedef struct s_lexer_subset	t_lexer_subset;
struct s_lexer_subset
{
	t_token			**tokens;
	int				size;
	t_lexer_subset	*(*subset)(t_lexer_subset *prev_subset, int start, int end);
	void			*(*destroy)(t_lexer_subset **self_ref);
};

t_lexer_subset	*ft_create_lexer_subset(
					t_lexer *lexer, int start, int end);
int				ft_get_precedence(t_token *node);
t_ast			*ft_create_ast(t_lexer *lexer);

#endif
