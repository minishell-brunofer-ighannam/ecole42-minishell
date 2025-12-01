/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 13:26:23 by valero            #+#    #+#             */
/*   Updated: 2025/11/24 22:47:30 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "tokenize/tokenize.h"
# include <stdbool.h>

/**
*  # t_lexer
*
* Estrutura final gerada pela tokenização. Agrupa todos os tokens
* produzidos pelo splitter e pelo lexer.
*
* Campos principais:
* - tokens: vetor de ponteiros para t_token.
* - original_prompt: cópia da linha original.
* - size: quantidade total de tokens.
* - destroy: callback para destruir toda a estrutura.
*
* Papel:
* Centraliza o resultado da tokenização e fornece um ponto único de
* destruição e gerenciamento do ciclo de vida dos tokens.
*/
typedef struct s_lexer	t_lexer;
struct s_lexer
{
	t_token		**tokens;
	const char	*original_prompt;
	int			size;
	void		*(*destroy)(t_lexer **self_ref);
};

bool	ft_is_redirect_token(t_token *token);
bool	ft_is_logic_token(t_token *token);
bool	ft_is_pipe_token(t_token *token);
bool	ft_is_reserved_token(t_token *token);
t_lexer	*ft_lexer(
			const char *prompt,
			t_expand_var_clbk expand_var,
			t_expand_glob_clbk expand_glob);

#endif
