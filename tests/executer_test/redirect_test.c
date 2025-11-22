/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 16:58:38 by ighannam          #+#    #+#             */
/*   Updated: 2025/11/22 17:28:06 by ighannam         ###   ########.fr       */
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

	//
	// NODE: wc -l   (comando que recebe o redirect)
	//
	t_tokenized_prompt *token_wc = ft_tokenizer("wc -l", ft_expand_var, ft_expand_glob);
	t_node *node_wc = ft_calloc(1, sizeof(t_node));
	node_wc->ht_env = ht_env;
	node_wc->token = token_wc->tokens;
	node_wc->type = NODE_CMD;

	//
	// NODE: < f1   (redirect de entrada)
	//
	t_tokenized_prompt *token_redir = ft_tokenizer("< f1", ft_expand_var, ft_expand_glob);
	t_node *node_redir = ft_calloc(1, sizeof(t_node));
	node_redir->ht_env = ht_env;
	node_redir->token = token_redir->tokens;
	node_redir->type = NODE_REDIRECT_IN;

	// comando associado ao redirect
	node_redir->left = node_wc;

	//
	// node_redir é a raiz da árvore
	//

	printf("\n===== < f1 wc -l =====\n");
	
	ft_execute_tree(node_redir);
	
	return (0);
}