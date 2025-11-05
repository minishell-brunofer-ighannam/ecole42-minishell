# Minishell

## Pontos gerais a serem desenvolvidos:
- Tree --> *BRUNO*
	- Fazer lexer/tokenizer ([`src/lexer/README.md`](https://github.com/minishell-brunofer-ighannam/ecole42-minishell/tree/main/src/lexer)) e parser:
	- Obs.: "e""c""h""o" é a mesma coisa que echo. Qualquer palavra especial pode ter aspas duplas ou simples no meio dela
	- Obs.: não precisa tratar () sem ser em && e ||. Ex.: não precisa tratar echo $(echo x)
	- Em algum ponto na montagem da árvore já verifica se há erros de sintaxe
	- Proposta: usar gramática (Context Free Grammar)
	- Olhar Recursive Descent para montar a árvore
	- Atenção com aspas simples e duplas
- Execution --> *ISADORA*
	- Definição de modelagem da struct
	- Montar hash table para env
	- Montar função que trata cada tipo de nó
	- Montar função que junta todas as outras execuções
	- Expansões ficam nessa parte --> montar função e expande ($ e *)
	- obs: quando tem && ou ||, se o lado esquerdo já define o resultado não executa o direito e já encerra
- Tratamento de sinais --> *BRUNO*
- set (ex.: echo teste=1) --> é diferente de export - não sei se precisamos tratar
- true e false - não sei se precisamos tratar

## sobre globs (wildcards no shell)
- pode conter mais de um asterisco num glob, exempo \*ou\*in\*\*

## Sobre CTRL + D
quando for co here-doc ele interrompe a leitura e da o seguinte warning **`bash: warning: here-document at line 4 delimited by end-of-file (wanted 'cat')`**


## Struct e ENUM para classificação de tipos de nó para cada nó da AST (Abstract Syntax Tree)

```c
typedef enum e_node_type {
    NODE_CMD,       // comando simples
    NODE_PIPE,      // |
    NODE_AND,       // &&
    NODE_OR,        // ||
    NODE_SUBSHELL,  // ( )
    NODE_REDIR      // redirecionamentos
} t_node_type;

typedef struct s_node
{
	t_node_type		type;
	char			**argv;
	struct s_node	*left;
	struct s_node	*right;
	int				built_in; //se for 1 indica que é uma função built in
}

```

## Adicionar Novos Arquivos no Makefile

exemplo `execution.c`:

-	Primeiro inserir o caminho do arquivo no Makefile (está na `linha 24`):

	```bash
	# ============== SRC FILES =================

	SRC_FILES = src/signals.c # colocar o execution.c aqui
	```
-	Depois inportar o header dele no `minishell.h`:
	```c
		/* ************************************************************************** */
		/*                                                                            */
		/*                                                        :::      ::::::::   */
		/*   minishell.h                                        :+:      :+:    :+:   */
		/*                                                    +:+ +:+         +:+     */
		/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
		/*                                                +#+#+#+#+#+   +#+           */
		/*   Created: 2025/11/04 12:57:32 by brunofer          #+#    #+#             */
		/*   Updated: 2025/11/04 18:59:51 by brunofer         ###   ########.fr       */
		/*                                                                            */
		/* ************************************************************************** */

		#ifndef MINISHELL_H
		# define MINISHELL_H

		# include <stdio.h>
		# include <readline/readline.h>
		# include <readline/history.h>
		# include <stdlib.h>
		# include "libft.h"
		# include "../src/signals.h"
		// coloque o includes aqui:
		// # includes "../src/execution.h"

		# define PROMPT "minishell$> "

		#endif

	```
