/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_heredoc_test.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 14:56:01 by ighannam          #+#    #+#             */
/*   Updated: 2025/11/20 19:04:48 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	
	t_linkedlist_array *ht_env;
	ht_env = ft_init_ht_env(envp);
	
	// Node << eof
	t_tokenized_prompt *token_hd = ft_tokenizer("<< eof", ft_expand_var, ft_expand_glob);
	t_node *node_hd;
	node_hd = ft_calloc(1, sizeof(t_node));
	node_hd->ht_env = ht_env;
	node_hd->token = token_hd->tokens;
	node_hd->type = NODE_HERE_DOC_IN;

	// Node cat
	t_tokenized_prompt *token_cat = ft_tokenizer("cat", ft_expand_var, ft_expand_glob);
	t_node *node_cat;
	node_cat = ft_calloc(1, sizeof(t_node));
	node_cat->ht_env = ht_env;
	node_cat->token = token_cat->tokens;
	node_cat->type = NODE_CMD;

	// Montando a árvore
	node_hd->left = node_cat;

	ft_execute_tree(node_hd);
	return (0);
}