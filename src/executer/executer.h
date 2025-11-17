/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 14:40:44 by ighannam          #+#    #+#             */
/*   Updated: 2025/11/17 15:13:01 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H

# include "../data_structures/data_structures.h"
# include "../env/env.h"
# include "../lexer/lexer.h"
# include <stdio.h>

typedef struct s_node
{
	t_token_type		type;
	t_token				**token;
	char				**argv;
	struct s_node		*left;
	struct s_node		*right;
	t_linkedlist_array	*ht_env;
}						t_node;

char					*ft_find_path(t_linkedlist_array *ht_env, char *cmd);

#endif
