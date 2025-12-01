/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_build.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 20:37:28 by valero            #+#    #+#             */
/*   Updated: 2025/11/30 21:44:14 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_BUILD_H
# define AST_BUILD_H

# include "../ast/ast.h"

t_ast	*ft_ast_build(t_lexer *lexer, void *exec);

#endif
