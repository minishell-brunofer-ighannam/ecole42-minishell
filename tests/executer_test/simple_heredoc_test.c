/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_heredoc_test.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 14:56:01 by ighannam          #+#    #+#             */
/*   Updated: 2025/11/24 23:21:33 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;

	t_linkedlist_array *ht_env;
	ht_env = ft_init_ht_env(envp);

	//
	// NODE: ls
	//
	t_lexer *token_ls = ft_lexer("ls", ft_expand_var, ft_expand_glob);
	t_node *node_ls = ft_calloc(1, sizeof(t_node));
	node_ls->ht_env = ht_env;
	node_ls->token = token_ls->tokens;
	node_ls->type = NODE_CMD;

	//
	// NODE: wc -l   (será filho do heredoc)
	//
	t_lexer *token_wc = ft_lexer("wc -l", ft_expand_var, ft_expand_glob);
	t_node *node_wc = ft_calloc(1, sizeof(t_node));
	node_wc->ht_env = ht_env;
	node_wc->token = token_wc->tokens;
	node_wc->type = NODE_CMD;

	//
	// NODE: << eof   (HEREDOC)
	//
	t_lexer *token_hd = ft_lexer("<< eof", ft_expand_var, ft_expand_glob);
	t_node *node_hd = ft_calloc(1, sizeof(t_node));
	node_hd->ht_env = ht_env;
	node_hd->token = token_hd->tokens;
	node_hd->type = NODE_HERE_DOC_IN;

	// comando que recebe o heredoc
	node_hd->left = node_wc;


	//
	// NODE: pipe   =  ls  |  (node_hd)
	//
	t_lexer *token_pipe = ft_lexer("|", ft_expand_var, ft_expand_glob);
	t_node *node_pipe = ft_calloc(1, sizeof(t_node));
	node_pipe->ht_env = ht_env;
	node_pipe->token = token_pipe->tokens;
	node_pipe->type = NODE_PIPE;

	node_pipe->left = node_ls;
	node_pipe->right = node_hd;

	//
	// node_pipe é a raiz da árvore
	//


	ft_execute_tree(node_pipe);
	return (0);
}
