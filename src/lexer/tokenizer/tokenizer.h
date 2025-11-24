/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 13:26:23 by valero            #+#    #+#             */
/*   Updated: 2025/11/24 20:28:52 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "tokenize/tokenize.h"
# include <stdbool.h>

/**
*  # t_tokenized_prompt
*
* Estrutura final gerada pela tokenização. Agrupa todos os tokens
* produzidos pelo splitter e pelo tokenizer.
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
typedef struct s_tokenized_prompt	t_tokenized_prompt;
struct s_tokenized_prompt
{
	t_token		**tokens;
	const char	*original_prompt;
	int			size;
	void		*(*destroy)(t_tokenized_prompt **self_ref);
};

t_tokenized_prompt	*ft_tokenizer(
						const char *prompt,
						t_expand_var_clbk expand_var,
						t_expand_glob_clbk expand_glob);

#endif
