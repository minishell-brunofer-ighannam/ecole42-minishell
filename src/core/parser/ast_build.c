/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 22:58:48 by valero            #+#    #+#             */
/*   Updated: 2025/11/25 23:53:42 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_internal.h"

t_ast	*ft_ast_build(t_lexer *lexer)
{
	t_lexer_subset	*subset;
	t_ast			*ast;

	ast = ft_create_ast(lexer);
	subset = ft_create_lexer_subset(lexer, 0, lexer->size - 1);
}
