/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 09:53:16 by ighannam          #+#    #+#             */
/*   Updated: 2025/11/21 19:34:45 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_linkedlist_array *ht_env;
	t_node *node;
	t_node *node2;

	// inicializa o ambiente com variáveis padrão
	ht_env = ft_init_ht_env(envp);

	// constroi array de tokens
	t_tokenized_prompt *tokenized_prompt = ft_tokenizer("ls", ft_expand_var, ft_expand_glob);

	// construção da árvore
	node = ft_calloc(1, sizeof(t_node));
	node->ht_env = ht_env;
	node->envp = envp;
	node->token = tokenized_prompt->tokens;
	node->type = NODE_CMD;

	printf("\n===== cmd ls =====\n");
	//ft_execute_tree(node);

	ft_set(ht_env, "LS=ls");
	// controi array de tokens 2
	t_tokenized_prompt *tokenized_prompt2 = ft_tokenizer("ls -l", ft_expand_var, ft_expand_glob);

	// construção da árvore
	node2 = ft_calloc(1, sizeof(t_node));
	node2->ht_env = ht_env;
	node2->envp = envp;
	node2->token = tokenized_prompt2->tokens;
	node2->type = NODE_CMD;

	printf("\n===== cmd ls -l =====\n");
	//ft_execute_tree(node2);




	printf("\n===== ls | wc -l =====\n");
	// Node wc -l
	t_tokenized_prompt *token_wc = ft_tokenizer("wc -l", ft_expand_var, ft_expand_glob);
	t_node *node_wc;
	node_wc = ft_calloc(1, sizeof(t_node));
	node_wc->ht_env = ht_env;
	node_wc->token = token_wc->tokens;
	node_wc->type = NODE_CMD;

	// Node ls
	t_tokenized_prompt *token_ls = ft_tokenizer("ls", ft_expand_var, ft_expand_glob);
	t_node *node_ls;
	node_ls = ft_calloc(1, sizeof(t_node));
	node_ls->ht_env = ht_env;
	node_ls->token = token_ls->tokens;
	node_ls->type = NODE_CMD;

	// Node |
	t_tokenized_prompt *token_pipe = ft_tokenizer("|", ft_expand_var, ft_expand_glob);
	t_node *node_pipe;
	node_pipe = ft_calloc(1, sizeof(t_node));
	node_pipe->ht_env = ht_env;
	node_pipe->token = token_pipe->tokens;
	node_pipe->type = NODE_PIPE;

	// Montando a árvore
	node_pipe->left = node_ls;
	node_pipe->right = node_wc;


	ft_execute_tree(node_pipe);


	printf("\n===== ls | wc -l | wc -l > f1 =====\n");
	// Node > f1
	t_tokenized_prompt *token_redir = ft_tokenizer("> f1", ft_expand_var, ft_expand_glob);
	t_node *node_redir;
	node_redir = ft_calloc(1, sizeof(t_node));
	node_redir->ht_env = ht_env;
	node_redir->token = token_redir->tokens;
	node_redir->type = NODE_REDIRECT_OUT;

	// Node wc -l (o da direita, que recebe a saída do pipe final)
	t_tokenized_prompt *token_wc2 = ft_tokenizer("wc -l", ft_expand_var, ft_expand_glob);
	t_node *node_wc2;
	node_wc2 = ft_calloc(1, sizeof(t_node));
	node_wc2->ht_env = ht_env;
	node_wc2->token = token_wc2->tokens;
	node_wc2->type = NODE_CMD;

	// Associando o redirect ao comando wc -l final
	node_redir->left = node_wc2;


	// Node wc -l (o intermediário)
	t_tokenized_prompt *token_wc1 = ft_tokenizer("wc -l", ft_expand_var, ft_expand_glob);
	t_node *node_wc1;
	node_wc1 = ft_calloc(1, sizeof(t_node));
	node_wc1->ht_env = ht_env;
	node_wc1->token = token_wc1->tokens;
	node_wc1->type = NODE_CMD;


	// Node ls
	t_tokenized_prompt *token_ls1 = ft_tokenizer("ls", ft_expand_var, ft_expand_glob);
	t_node *node_ls1;
	node_ls1 = ft_calloc(1, sizeof(t_node));
	node_ls1->ht_env = ht_env;
	node_ls1->token = token_ls1->tokens;
	node_ls1->type = NODE_CMD;


	// Node pipe 1 (ls | wc -l)
	t_tokenized_prompt *token_pipe1 = ft_tokenizer("|", ft_expand_var, ft_expand_glob);
	t_node *node_pipe1;
	node_pipe1 = ft_calloc(1, sizeof(t_node));
	node_pipe1->ht_env = ht_env;
	node_pipe1->token = token_pipe1->tokens;
	node_pipe1->type = NODE_PIPE;

	node_pipe1->left = node_ls1;
	node_pipe1->right = node_wc1;


	// Node pipe 2 ((ls | wc -l) | (wc -l > f1))
	t_tokenized_prompt *token_pipe2 = ft_tokenizer("|", ft_expand_var, ft_expand_glob);
	t_node *node_pipe2;
	node_pipe2 = ft_calloc(1, sizeof(t_node));
	node_pipe2->ht_env = ht_env;
	node_pipe2->token = token_pipe2->tokens;
	node_pipe2->type = NODE_PIPE;

	node_pipe2->left = node_pipe1;
	node_pipe2->right = node_redir;

	ft_execute_tree(node_pipe2);



	ht_env->destroy(&ht_env, ft_free_item_ht_env);

	return(0);
}
