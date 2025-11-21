/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   only_redirects_test.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 16:58:38 by ighannam          #+#    #+#             */
/*   Updated: 2025/11/19 17:54:04 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_linkedlist_array *ht_env;
	

	// inicializa o ambiente com variáveis padrão
	ht_env = ft_init_ht_env(envp);

	// Node > f3
	t_tokenized_prompt *tokenized_prompt = ft_tokenizer("> f3", ft_expand_var, ft_expand_glob);
	t_node *node;
	node = ft_calloc(1, sizeof(t_node));
	node->ht_env = ht_env;
	node->token = tokenized_prompt->tokens;
	node->type = NODE_REDIRECT_OUT;

	// Node > f2
	t_tokenized_prompt *tokenized_prompt2 = ft_tokenizer("> f2", ft_expand_var, ft_expand_glob);
	t_node *node2;
	node2 = ft_calloc(1, sizeof(t_node));
	node2->ht_env = ht_env;
	node2->token = tokenized_prompt2->tokens;
	node2->type = NODE_REDIRECT_OUT;

	// Node > f1
	t_tokenized_prompt *tokenized_prompt3 = ft_tokenizer("> f1", ft_expand_var, ft_expand_glob);
	t_node *node3;
	node3 = ft_calloc(1, sizeof(t_node));
	node3->ht_env = ht_env;
	node3->token = tokenized_prompt3->tokens;
	node3->type = NODE_REDIRECT_OUT;

	// Node ls
	t_tokenized_prompt *tokenized_prompt4 = ft_tokenizer("ls", ft_expand_var, ft_expand_glob);
	t_node *node4;
	node4 = ft_calloc(1, sizeof(t_node));
	node4->ht_env = ht_env;
	node4->token = tokenized_prompt4->tokens;
	node4->type = NODE_CMD;

	// Montando a árvore
	node->left = node2;
	node2->left = node3;
	node3->left = node4;

	printf("\n===== ls > f1 > f2 > f3 =====\n");
	ft_execute_tree(node);
	
	return (0);
}