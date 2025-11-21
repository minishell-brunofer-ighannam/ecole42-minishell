# Validator Module — Overview

![prompt validator diagram](prompt_validator_diagram.png)

O módulo **validator** verifica se a linha digitada pelo usuário possui erros de
estrutura: aspas abertas, parênteses sem fechamento, backquotes soltos ou
sequências `$(` sem o `)` correspondente.
Ele retorna **o índice do primeiro erro encontrado** ou **-1** quando a linha é válida.

O fluxo geral é simples:

1. Cada tipo de estrutura é validado separadamente:
   - `()`
   - `"`
   - `'`
   - `` ` ``
   - `$( ... )`
2. Cada validador percorre a string e:
   - marca o índice de abertura
   - procura o fechamento correto
   - pula estruturas internas (ex.: `( " ... ` ... ` )`)
3. Ao final, o `prompt_validator` escolhe **o menor índice válido** dentre todos —
   esse é o erro real.

A ideia é detectar **erros estruturais sérios** antes de o parser ser acionado.

---

# Principais Estruturas e Funções

## `t_char_checker`
Estrutura auxiliar para operações locais dentro de subtstrings:
- `str` — string original
- `idx` — posição de início
- `chars` — conjunto de caracteres que delimitam a estrutura
- `is_special_char` — função de comparação

É usada quando precisamos gerar uma substring delimitada e validá-la
isoladamente.

---

## `prompt_validator(const char *line)`
Função principal do módulo.
Executa todos os validadores, coleta seus resultados e retorna **o menor índice**
onde há erro.
Se nenhum erro existir, retorna **-1**.

---

## `jump_to_closing(...)`
Pula diretamente até o fechamento da estrutura atual.
É crucial para evitar leituras erradas dentro de:
- aspas
- parênteses
- backquotes
- dollar-parens

Se encontrar uma estrutura interna, invoca `verify_char` ou pula via `get_end`.

---

## `verify_char(t_char_checker checker, int (*verify)())`
Extrai uma substring delimitada e aplica um validador nela.
Responsável por detectar erros **internos**, como:

```c
$("foo "bar")
```

Se um erro é encontrado na substring, retorna o índice local.

---

## `ft_get_smaller`
Recebe um vetor de índices e devolve o menor índice válido.
É a base para a decisão final do `prompt_validator`.

---

## `get_end`
Recebe um índice de abertura e procura o caractere de fechamento
correspondente.
Serve como motor para saltar grandes blocos internos com segurança.

---

# Validadores Individuais

## `validate_singlequotes`
Valida `'...'`.
Não permite estruturas internas.
Se a aspa não for fechada, retorna a posição inicial.

---

## `validate_doublequotes`
Valida `"..."`.
Aceita estruturas internas como:
- `` `...` ``
- `$(...)`

Usa `jump_inner_structures` para ignorar o conteúdo corretamente.

---

## `validate_parens`
Valida `(...)` comuns.
Diferencia de `$(...)` através da flag `is_dollar_parens`.
Permite estruturas internas.

---

## `validate_dollar_parens`
Valida estruturas de substituição:

```c
$( comando ... )
```

Controla `is_parens` para diferenciar entre parênteses normais e `$(`.
É o validador mais sensível do módulo.

---

## `validate_backquotes`
Valida `` `...` ``.
Aceita estruturas internas como aspas, parênteses e `$(`.
Usa fortemente `jump_inner_structures`.

---

# Helpers Internos

## `fill_int_array`
Inicializa vetores de índices com `-1`.

---

## `update_open_index`
Versões diferentes existem em cada validador.
Sempre fazem a mesma função essencial:
- marcar a abertura
- limpar quando encontrar o fechamento

Controlam flags internas como `is_dollar_parens` ou `is_parens`.

---

# Conclusão

O módulo validator não interpreta comandos.
Ele apenas garante que a entrada esteja **estruturalmente íntegra**,
permitindo que o parser trabalhe em paz e que o shell se comporte como deve.

O objetivo é simples:
**não deixar o usuário quebrar seu minishell com uma linha inválida.**
