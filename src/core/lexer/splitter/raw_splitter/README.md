# Raw Splitter – Tokenizador Robusto com Tratamento Avançado de Aspas

![raw splitter diagram](raw_diagram.png)

Este módulo implementa um **tokenizador bruto** especializado para cenários onde `ft_split` não é suficiente.
Ele identifica **tokens** preservando exatamente a posição original de cada trecho, mesmo quando existem:

- aspas simples `'`
- aspas duplas `"`
- backticks `` ` ``
- sequências consecutivas de aspas
- estados intermediários de abertura/fechamento
- espaços que fazem parte do conteúdo
- escapes válidos

Ideal para:

- interpretes e mini-shells
- pré-processamento de comandos
- análise sintática leve
- ferramentas que dependem de coordenadas exatas do texto original

---

# ⚙️ Funcionamento Geral

O módulo opera em **duas etapas** complementares.

---

## 1. 🧭 Mapeamento das Coordenadas

A função **`ft_raw_splitter_get_words_position()`** percorre o texto e registra:

- início de um token
- fim de um token
- entrada e saída de aspas
- estados intermediários e transições com backticks
- casos especiais como múltiplos fechamentos de backticks

Tudo isso baseado em uma **máquina de estados** (`FSM`), representada pela estrutura `t_quote_info`:

```c
typedef struct s_quote_info
{
    t_quote_state state;
    int           open_quote_type;
} t_quote_info;
```

Estados possíveis:

```c
NO_QUOTE_OPEN
QUOTE_OPEN
INSIDE_QUOTE
CLOSED_QUOTE
```

Ao final, a função gera um vetor linear:

```
[start0, end0, start1, end1, start2, end2, ...]
```

Cada par representa um token detectado.

---

## 2. ✂️ Construção dos Tokens

Com as coordenadas definidas, a função **`ft_run_split()`**:

1. Cria uma instância de `t_splited_prompt`
2. Aloca o array de strings
3. Extrai cada substring usando os índices
4. Registra as coordenadas de cada token
5. Define `len` corretamente

Resultado típico:

```c
splited_prompt->chuncks = ["hello", "my name is", "test"];
splited_prompt->coords  = { {0,4}, {8,19}, {23,26} };
splited_prompt->len     = 3;
```

---

# 🧱 Estruturas Principais

### `t_splited_prompt`

```c
typedef struct s_splited_prompt
{
    char **chuncks; // tokens extraídos
    int  **coords;  // pares [start, end]
    int   len;      // quantidade de tokens
    void *(*destroy)(t_splited_prompt **self_ref);
} t_splited_prompt;
```

É o objeto final entregue pelo módulo.

---

### `t_quote_info` e `t_quote_state`

Gerenciam a lógica de aspas:

- detectar entradas e saídas
- lidar com aspas consecutivas
- diferenciar aspas simples, duplas e backticks
- permitir parsing de tokens com espaços internos

---

### `t_int_array`

```c
typedef struct s_int_array
{
    int len;
    int *array;
} t_int_array;
```

Armazena o vetor contínuo de coordenadas enquanto o texto é analisado.

---

# 🔍 Funções Críticas

### `ft_raw_splitter()`

Entrada principal.
Aloca o array de coordenadas, preenche com a análise e devolve o objeto final.

---

### `ft_raw_splitter_get_words_position()`

Coração do módulo.
Percorre o texto e determina com precisão onde cada token começa e termina.

---

### `ft_raw_splitter_update_quote_state()`

Atualiza o estado atual da máquina de aspas.
Lida com:

- aberturas
- fechamentos
- múltiplos backticks
- aspas consecutivas

---

### `ft_split_with_coords()`

Extrai as substrings reais usando os índices.

---

# 🧪 Exemplo Simplificado

Entrada:

```
echo "um teste" `cmd here` 'outro'
```

Coordenadas detectadas:

```
[0,3] [5,13] [15,23] [25,31]
```

Tokens extraídos:

```
["echo", "um teste", "cmd here", "outro"]
```

As aspas não são removidas por padrão — tudo fica exatamente como no original.

---

# 🧹 Destruição Segura

A estrutura final possui um método `destroy` para facilitar limpeza:

```
splited_prompt->destroy(&splited_prompt);
```

---

# 📌 Conclusão

Este módulo entrega:

- tokenização robusta
- preservação total da estrutura original
- tratamento avançado de aspas e estados
- coordenação completa entre análise e extração

É uma base sólida para **interpretes**, **parsers customizados** e qualquer ferramenta que precise manipular texto sem perder fidelidade.

---

Pronto para ser integrado ao seu mini-shell ou analisador.
