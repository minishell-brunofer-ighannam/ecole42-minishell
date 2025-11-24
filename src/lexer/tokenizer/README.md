# 🧩 Tokenizer — Visão Geral

O módulo **tokenizer** transforma a linha bruta do usuário em uma sequência estruturada de **tokens**, cada um contendo seu valor, tipo, coordenadas e callbacks de expansão.
É o elo entre o *splitter* (que apenas divide a linha) e o *expander* (que interpreta `$VAR`, globs e aspas).

O objetivo do tokenizer é:
1. **Criar tokens bem definidos** a partir dos chunks gerados pelo splitter.
2. **Classificar cada token** (pipe, redirecionamento, operador, palavra comum).
3. **Conectar cada token ao sistema de expansão**, anexando callbacks e estruturas auxiliares.
4. **Fornecer um objeto final (`t_tokenized_prompt`)**, pronto para a fase de *expansão* e, depois, *execução*.

---

# 🔧 Funcionamento Geral

O fluxo básico é:

1. O usuário digita algo como:
	```bash
	echo "$USER" | grep foo > out.txt
	```

2. O `splitter` devolve chunks já segmentados por espaços e aspas.

3. O `tokenizer` recebe esses chunks e, para cada um:
- Determina o tipo do token (`|`, `>`, `>>`, palavra comum etc.).
- Atribui callbacks para expansões.
- Salva a substring bruta.
- Armazena as coordenadas originais na linha.
- Monta um objeto `t_token`.

4. Todos os tokens são guardados em um `t_tokenized_prompt`, que contém:
- o vetor de tokens,
- a linha original,
- o tamanho total,
- um destrutor próprio.

Após isso, o *expander* pode operar no token com segurança, usando as coordenadas originais e os callbacks.

---

# 🧱 Estruturas Principais

## **t_tokenized_prompt**

Contém o resultado completo da tokenização.

- `tokens`: vetor de ponteiros para `t_token`.
- `original_prompt`: cópia exata da linha digitada.
- `size`: número total de tokens.
- `destroy`: função para limpar tudo de forma segura.

Serve como **container principal**, preservando o estado antes da expansão.

---

# 🔨 Funções Essenciais

## **ft_tokenizer(prompt, expand_var, expand_glob)**

Função de entrada.
Une o splitter e o tokenizer:

- Chama `ft_splitter()` → obtém os chunks.
- Prepara callbacks de expansão.
- Cria a estrutura final via `ft_create_tokenized_prompt()`.
- Retorna um `t_tokenized_prompt`.

É o ponto de partida da fase de tokenização.

---

## **ft_create_tokenized_prompt(prompt, &splited, callbacks)**

Constrói o objeto final:

- Aloca `t_tokenized_prompt`.
- Copia a prompt original.
- Cria o vetor de tokens com tamanho exato.
- Para cada chunk do splitter:
- chama `ft_tokenize()` para construir o token final.
- Em caso de erro, destrói tudo com segurança.
- Registra o destrutor.

É o coração da construção do tokenizer.

---

## **ft_destroy_tokenized_prompt(self_ref)**

Destrutor completo:

- Libera a string original.
- Libera cada token individual.
- Libera o vetor de tokens.
- Libera a própria estrutura.
- Zera o ponteiro externo.

Evita leak em qualquer contexto.

---

## **ft_coord_dup() / ft_new_coord()**

Funções utilitárias simples:

- `ft_coord_dup` → duplica um par `[start, end]`.
- `ft_new_coord` → cria um par `[start, end]` novo.

Essenciais para manter coordenadas independentes ao longo do fluxo.

---

# 📌 Resumo Final

O tokenizer:

- Recebe chunks brutos do splitter.
- Cria tokens completos com tipo, posição e callbacks.
- Embala tudo em um `t_tokenized_prompt`.
- Prepara a linha para as fases de expansão (variáveis, globs, aspas) e execução.

É o **núcleo da interpretação lexical** do shell.

