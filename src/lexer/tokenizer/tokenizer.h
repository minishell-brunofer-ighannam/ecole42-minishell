/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 13:26:23 by valero            #+#    #+#             */
/*   Updated: 2025/11/19 14:55:10 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "tokenize/tokenize.h"
# include <stdbool.h>

typedef struct s_tokenized_prompt	t_tokenized_prompt;
struct s_tokenized_prompt
{
	t_token		**tokens;
	const char	*original_prompt;
	int			size;
	void		*(*destroy)(t_tokenized_prompt **self_ref);
};
/* `
ola"tudo bem"'?*'bom" dia"
[
	{
		quo_type: (nil),
		char *chunck: "ola",
	},
	{
		quo_type: ",
		char *chunck: "tudo bem",
	},
	{
		quo_type: ',
		char *chunck: "?*",
	},
	{
		quo_type: (nil),
		char *chunck: "bom",
	},
	{
		quo_type: ",
		char *chunck: " dia",
	},
]
 */
t_tokenized_prompt	*ft_tokenizer(
						const char *prompt,
						t_expand_var_clbk expand_var,
						t_expand_glob_clbk expand_glob);

#endif
