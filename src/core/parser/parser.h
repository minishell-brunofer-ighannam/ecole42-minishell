/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 00:14:45 by valero            #+#    #+#             */
/*   Updated: 2025/12/01 16:28:41 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../lexer/lexer.h"
# include "ast/ast.h"

t_ast	*ft_parser(const char *prompt, t_expander_callbacks callbacks,
			void *exec, void (*free_content)(void *arg));

#endif
