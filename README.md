# Minishell


| Info | Details |
|------|----------|
| **Project Start** | November 4, 2025 |
| **Authors** | [Bruno Fernandes Valero](https://github.com/bruno-valero) & [Isadora Ghannam](https://github.com/isaghannam) |
| **School / Program** | [42 São Paulo](https://www.42sp.org.br/) – Minishell Project |
| **Language** | C |
| **Description** | A custom shell implementation designed to replicate core Bash functionalities, with process management, pipes, environment handling, and command parsing. |
| **Status** | 🚧 In progress |
| **Modules** | [Lexer](https://github.com/minishell-brunofer-ighannam/ecole42-minishell/tree/main/src/core/lexer), [Parser](https://github.com/minishell-brunofer-ighannam/ecole42-minishell/tree/main/src/core/parser), [Executer](https://github.com/minishell-brunofer-ighannam/ecole42-minishell/tree/main/src/core/executer), [Data Structures](https://github.com/minishell-brunofer-ighannam/ecole42-minishell/tree/main/src/data_structures), [Utils](https://github.com/minishell-brunofer-ighannam/ecole42-minishell/tree/main/src/utils) and [Automated Tests](https://github.com/minishell-brunofer-ighannam/ecole42-minishell/tree/main/tests) |
| **Documentation** | Every module has its own documentation, **click in the modules above** for full details |

---


# Planejamento do Projeto MiniShell

Trabalho em paralelo --- Tokenização (Bruno) + Environment/Expansões
(Isadora)

Este documento descreve exatamente **como o projeto está sendo
desenvolvido**, destacando a execução **em paralelo** e o fluxo completo
de trabalho até as próximas fases.

------------------------------------------------------------------------

## 📌 Visão Geral do Projeto

O MiniShell está sendo desenvolvido em etapas bem delimitadas.
Cada etapa segue sempre o mesmo ciclo:

    Implementar → Testar → Pausar → Revisar → Documentar → Revisão Cruzada → Próxima Fase

Esse ciclo se repete em **todas** as fases do projeto.

## 📌 Fluxo Geral do Projeto

	[ Tokenização (Bruno) ]    ← paralelo →    [ Env + Expansões (Isadora) ]
				 ↓
	[ Parser + AST (Bruno) ]    ← paralelo →    [ Execução da Árvore (Isadora) ]
				 ↓
	[ Built-ins (Ambos, em paralelo) ]
				 ↓
	[ Leitura do Prompt com Termios (Ambos) ]
				 ↓
	[ Integração Final ]

------------------------------------------------------------------------

## 📍 FASE ATUAL --- Execução em Paralelo

### **1. Tokenização (Bruno)**

Responsável por:

-   Divisão do prompt:
    -   Espaços
    -   Aspas simples
    -   Aspas duplas
-   Separação de símbolos grudados:
    -   `|`, `<`, `>`, `>>`, `<<`
-   Divisão avançada:
    -   Tokens com partes misturadas (trechos sem aspas, trechos entre
        aspas)
-   Identificação de trechos elegíveis para expansão
-   Criação do pipeline de callbacks:
    -   Expansão de variáveis (callback)
    -   Expansão de glob (callback)
-   Testes unitários da tokenização


> #### ***Pendências:***
> -   Criar o **array final de tokens**
> -   Classificar os tokens
> -   Garante validações globais (ex.: erros de sintaxe simples)
> -   Preparar os tokens para o parser

### **2. Environment / Expansões (Isadora)**

Responsável por:

-   Implementação da tabela de variáveis de ambiente
    -   `set`
    -   `unset`
    -   `extend`
-   Expansão de variáveis
-   Expansão de glob:
    -   *Pendências:*
        -   Suporte a caminhos completos (ex: `/home/user/*`)
        -   Diferenciar glob dentro/fora de aspas
-   Fornecer a função de expansão como callback para a tokenização
-   Testes unitários das expansões

> #### ***Pendências:***
> -   Suporte a caminhos completos (ex: `/home/user/*`)
> -   Diferenciar glob dentro/fora de aspas

**Bruno e Isadora trabalham em paralelo** nessa fase:
- Bruno fornece tokens "pré-processados"
- Isadora fornece a função de expansão
- Ambos usam **mocks** para testar quando o módulo do outro ainda não
está pronto
- Comunicação constante para manter a mesma abstração e semântica

------------------------------------------------------------------------

## 📍 Fase Seguinte --- Parsing + Construção da Árvore (AST) + Execução

Trabalho **em paralelo novamente**, mas com funções diferentes:

### **Bruno**

-   Faz o **parser**
-   Monta a **AST**
-   Valida estrutura
-   Define nós da árvore e tipos de operações

### **Isadora**

-   Implementa a **execução da árvore**, usando mocks até a AST final
    existir:
    -   Pipeline
    -   Redireções
    -   Execução de comandos

------------------------------------------------------------------------

## 📍 Etapa Posterior --- Built-ins (PARALELO)

Ambos trabalham juntos, cada um pega alguns built-ins:

-   `cd`
-   `echo`
-   `cat`
-   Outros necessários

Desenvolvidos **em paralelo**, seguindo o mesmo ciclo:

    Implementar → Testar → Revisar → Documentar → Revisão Cruzada

------------------------------------------------------------------------

## 📍 Última Grande Fase --- Leitura do Prompt (Termios, Termcap)

Trabalho **conjunto**, em paralelo:

-   Abandonar `readline`
-   Implementar a leitura manual:
    -   Raw mode
    -   Histórico
    -   Movimentação do cursor
    -   Redesenho da linha
    -   Backspace, delete, etc.
-   Testes unitários onde possível

Essa etapa só começa quando tudo antes estiver **estável e bem
documentado**.

------------------------------------------------------------------------

## 📌 Metodologia de Trabalho (sempre igual)

Para cada grande módulo:

1.  Implementação
2.  Testes unitários
3.  Pausa intencional
4.  Revisão do próprio código
5.  Documentação
6.  Um revisa o do outro
7.  Mais testes
8.  Só então → próxima fase

------------------------------------------------------------------------

## ✔️ Estado Atual

-   Tokenização micro: **quase finalizada**
-   Expansão de variáveis: **pronta**
-   Expansão de glob: **falta melhorar**
-   Pipeline de callback: **integrado e funcionando**
-   Próximas tarefas:
    -   Refinar glob
    -   Finalizar tokenização macro
    -   Revisar e documentar tudo
    -   Entrar juntos na fase da AST

------------------------------------------------------------------------



---

## Pontos gerais a serem desenvolvidos:
- Tree --> *BRUNO*
	- Fazer lexer/lexer ([`src/lexer/README.md`](https://github.com/minishell-brunofer-ighannam/ecole42-minishell/tree/main/src/lexer)) e parser:
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
- env - só printa o env em qqr ordem
- export - printa env em ordem alfabética e com detalhes antes e na formatação
- impressão de env e export - olhar como fica quando você declara uma variável como NULL ou não coloca nenhum valor para ela (comentários Bia)

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
