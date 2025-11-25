# Submódulo de Separação de Aspas (Quote Splitter)

![separate quote chuncks diagram](sep_quote_chuncks_diagram.png)

Este módulo varre uma string e a divide em **trechos normais**, **trechos entre aspas simples** e **trechos entre aspas duplas**, preservando coordenadas e tipos de aspas. Ele funciona como um **pré-processador para parsing**, exatamente como um shell faz antes de expandir variáveis e metacaracteres.

---

# 📦 Estruturas Principais

## `t_token_section`
Representa **um único pedaço** da string original.

Campos:
- `section`: substring extraída.
- `quote_type`: `'`, `"` ou `0` (sem aspas).
- `start` / `end`: coordenadas originais.
- `destroy`: função para liberar.

É a unidade básica do módulo.

---

## `t_token_separated_sections`
É o **container completo** que guarda todas as seções.

Contém:
- `list`: lista de `t_token_section`.
- `coord_list`: lista de coordenadas.
- `array`: versão em array das seções.
- `coord_array`: coordenadas em array.
- Funções de cópia, destruição e reconstrução.
- Suporte a reconstrução da string sem aspas.

Pensa como um “pacote de análise das aspas”.

---

# ⚙️ Fluxo do `ft_separate_quote_chunks()`

1. Inicializa a estrutura principal.
2. Percorre a string com índice `i`.
3. Mantém estado de aspas:
   - `singlequote` ligado/desligado.
   - `doublequote` ligado/desligado.
4. Em cada passo:
   - `update_token_section()` ajusta o estado.
   - `push_non_quote_section()` captura texto sem aspas.
   - `push_doublequote_section()` captura `"..."`.
   - `push_singlequote_section()` captura `'...'`.
5. Converte listas em arrays.
6. Devolve a estrutura pronta para o parser.

É um scanner manual, nada de mágica.

---

# 🔧 Funções Auxiliares (Resumo Rápido)

### `update_token_section()`
Determina entrada/saída de aspas e ajusta o estado.

### `push_non_quote_section()`
Coleta trecho contínuo sem aspas.

### `push_doublequote_section()`
Coleta `"..."` incluindo as aspas.

### `push_singlequote_section()`
Coleta `'...'` incluindo as aspas.

### `ft_to_noquotes_string()`
Reconstrói a string removendo apenas as aspas externas.

---

# ✔️ Em resumo final
Este módulo **divide a string em blocos classificados por tipo de aspas**, marca coordenadas originais e prepara tudo para expansão posterior. É a base do parser de shell que depende de entender “onde” cada caractere está e “sob qual aspas” ele vive.
