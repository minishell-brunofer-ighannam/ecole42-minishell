/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 09:53:16 by ighannam          #+#    #+#             */
/*   Updated: 2025/11/26 17:28:18 by ighannam         ###   ########.fr       */
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

	// //LINHA DE COMANDO
	// printf("\ncat < input.txt | grep foo || ls > log.txt && head -n 5 >> results.txt | wc -l << EOF\n");


	// // Node cat
	// t_lexer *token_cat = ft_lexer("cat", ft_expand_var, ft_expand_glob);
	// t_node *node_cat = ft_calloc(1, sizeof(t_node));
	// node_cat->ht_env = ht_env;
	// node_cat->token = token_cat->tokens;
	// node_cat->type = NODE_CMD;

	// // Node < input.txt
	// t_lexer *token_in = ft_lexer("< input.txt", ft_expand_var, ft_expand_glob);
	// t_node *node_in = ft_calloc(1, sizeof(t_node));
	// node_in->ht_env = ht_env;
	// node_in->token = token_in->tokens;
	// node_in->type = NODE_REDIRECT_IN;

	// // Redirect: cat < input.txt
	// node_in->left = node_cat;

	// // Node grep foo
	// t_lexer *token_grep = ft_lexer("grep foo", ft_expand_var, ft_expand_glob);
	// t_node *node_grep = ft_calloc(1, sizeof(t_node));
	// node_grep->ht_env = ht_env;
	// node_grep->token = token_grep->tokens;
	// node_grep->type = NODE_CMD;

	// // Node |
	// t_lexer *token_pipe_A = ft_lexer("|", ft_expand_var, ft_expand_glob);
	// t_node *node_pipe_A = ft_calloc(1, sizeof(t_node));
	// node_pipe_A->ht_env = ht_env;
	// node_pipe_A->token = token_pipe_A->tokens;
	// node_pipe_A->type = NODE_PIPE;

	// // Montando: cat < input.txt | grep foo
	// node_pipe_A->left = node_in;
	// node_pipe_A->right = node_grep;

	// // Node ls
	// t_lexer *token_ls = ft_lexer("ls", ft_expand_var, ft_expand_glob);
	// t_node *node_ls = ft_calloc(1, sizeof(t_node));
	// node_ls->ht_env = ht_env;
	// node_ls->token = token_ls->tokens;
	// node_ls->type = NODE_CMD;


	// // Node > log.txt
	// t_lexer *token_out = ft_lexer("> log.txt", ft_expand_var, ft_expand_glob);
	// t_node *node_out = ft_calloc(1, sizeof(t_node));
	// node_out->ht_env = ht_env;
	// node_out->token = token_out->tokens;
	// node_out->type = NODE_REDIRECT_OUT;

	// // ls > log.txt
	// node_out->left = node_ls;

	// // Node ||
	// t_lexer *token_or = ft_lexer("||", ft_expand_var, ft_expand_glob);
	// t_node *node_or = ft_calloc(1, sizeof(t_node));
	// node_or->ht_env = ht_env;
	// node_or->token = token_or->tokens;
	// node_or->type = NODE_OR;

	// // Montagem:  (cat < ... | grep foo)  ||  (ls > log.txt)
	// node_or->left = node_pipe_A;
	// node_or->right = node_out;

	// // Node head -n 5
	// t_lexer *token_head = ft_lexer("head -n 5", ft_expand_var, ft_expand_glob);
	// t_node *node_head = ft_calloc(1, sizeof(t_node));
	// node_head->ht_env = ht_env;
	// node_head->token = token_head->tokens;
	// node_head->type = NODE_CMD;

	// // Node >> results.txt
	// t_lexer *token_append = ft_lexer(">> results.txt", ft_expand_var, ft_expand_glob);
	// t_node *node_append = ft_calloc(1, sizeof(t_node));
	// node_append->ht_env = ht_env;
	// node_append->token = token_append->tokens;
	// node_append->type = NODE_APPEND_OUT;

	// // head -n 5 >> results.txt
	// node_append->left = node_head;

	// // Node wc -l
	// t_lexer *token_wc = ft_lexer("wc -l", ft_expand_var, ft_expand_glob);
	// t_node *node_wc = ft_calloc(1, sizeof(t_node));
	// node_wc->ht_env = ht_env;
	// node_wc->token = token_wc->tokens;
	// node_wc->type = NODE_CMD;

	// // Node << EOF
	// t_lexer *token_heredoc = ft_lexer("< EOF", ft_expand_var, ft_expand_glob);
	// t_node *node_heredoc = ft_calloc(1, sizeof(t_node));
	// node_heredoc->ht_env = ht_env;
	// node_heredoc->token = token_heredoc->tokens;
	// node_heredoc->type = NODE_REDIRECT_IN;

	// // wc -l << EOF
	// node_heredoc->left = node_wc;

	// // Node |
	// t_lexer *token_pipe_C = ft_lexer("|", ft_expand_var, ft_expand_glob);
	// t_node *node_pipe_C = ft_calloc(1, sizeof(t_node));
	// node_pipe_C->ht_env = ht_env;
	// node_pipe_C->token = token_pipe_C->tokens;
	// node_pipe_C->type = NODE_PIPE;

	// // Montando: head >> results.txt | wc -l << EOF
	// node_pipe_C->left = node_append;
	// node_pipe_C->right = node_heredoc;

	// // Node &&
	// t_lexer *token_and = ft_lexer("&&", ft_expand_var, ft_expand_glob);
	// t_node *node_and = ft_calloc(1, sizeof(t_node));
	// node_and->ht_env = ht_env;
	// node_and->token = token_and->tokens;
	// node_and->type = NODE_AND;

	// // Montagem final
	// node_and->left = node_or;      // (A || B)
	// node_and->right = node_pipe_C; // C


	// ft_execute_tree(node_and);

	//
	// NODE: ls
	//
	t_lexer *token_ls = ft_lexer("ls", ft_expand_var, ft_expand_glob);
	t_node *node_ls = ft_calloc(1, sizeof(t_node));
	node_ls->ht_env = ht_env;
	node_ls->token = token_ls->tokens;
	node_ls->type = NODE_CMD;

	//
	// NODE: wc -l
	//
	t_lexer *token_wc = ft_lexer("minishell", ft_expand_var, ft_expand_glob);
	t_node *node_wc = ft_calloc(1, sizeof(t_node));
	node_wc->ht_env = ht_env;
	node_wc->token = token_wc->tokens;
	node_wc->type = NODE_CMD;

	//
	// NODE: < f1
	//
	t_lexer *token_redirect = ft_lexer("< f1", ft_expand_var, ft_expand_glob);
	t_node *node_redirect = ft_calloc(1, sizeof(t_node));
	node_redirect->ht_env = ht_env;
	node_redirect->token = token_redirect->tokens;
	node_redirect->type = NODE_REDIRECT_IN;

	//
	// O redirect fica como nó ESQUERDO do comando wc -l
	//

	//
	// NODE: pipe   =   ls  |  wc -l < f1
	//
	t_lexer *token_pipe = ft_lexer("|", ft_expand_var, ft_expand_glob);
	t_node *node_pipe = ft_calloc(1, sizeof(t_node));
	node_pipe->ht_env = ht_env;
	node_pipe->token = token_pipe->tokens;
	node_pipe->type = NODE_PIPE;

	node_pipe->left = node_ls;
	node_pipe->right = node_redirect;
	node_redirect->left = node_wc;

	//
	// node_pipe é a raiz final
	//



	ft_execute_tree(node_wc);


	t_ht *item;
	t_env_value *value;
	t_linkedlist_node *curr_node;

	curr_node = ft_find_ht(ht_env, "?");
	item = curr_node->content;
	value = item->value;

	//printf("%s\n", value->value);



	ht_env->destroy(&ht_env, ft_free_item_ht_env);

	return(0);
}
