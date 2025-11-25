# Submódulo: Expandable Object

![expandable object diagram](exp_object_diagram.png)

Este módulo identifica trechos expansíveis dentro de um token
(`$VAR`, `${VAR}`, `$1`, `$?`, `$(cmd)` etc.), coleta suas coordenadas
originais, avalia se há *globs* e produz um objeto estruturado
(`t_expandable_object`) com tudo que será usado na fase posterior
de expansão.

O fluxo é simples e direto:

1. **Separar trechos da string**, preservando conteúdo entre aspas simples.
2. **Filtrar apenas partes expansíveis**.
3. **Extrair cada chave de expansão**, com coordenadas.
4. **Detectar globs** (`*` fora de aspas).
5. **Produzir o objeto final** (`t_expandable_object`), centralizando:
   - valor original
   - chaves expansíveis
   - coordenadas dessas chaves
   - flags de controle (como `has_globs`)

---

# Estruturas Principais

## t_expandable_section
Agrupa trechos da string considerados expansíveis.

- `list`: lista encadeada de strings encontradas.
- `coord_list`: lista de coordenadas correspondentes.
- `array` / `coord_array`: versões convertidas das listas.
- `copy_array`: duplica o array.
- `copy_coord_array`: duplica coordenadas.
- `destroy`: libera a estrutura.

Usada como **base de coleta** durante o parsing.

---

## t_expandable_object
Objeto final que representa *tudo que pode ser expandido* dentro de um token.

- `original_value`: valor bruto do token.
- `expanded_value`: valor após substituição de variáveis.
- `expanded_glob_value`: valor após expansão de globs (se houver).
- `has_globs`: indica se há `*` relevante.
- `expandable_keys`: lista final das chaves encontradas (`$VAR`, `$?`, etc.).
- `expandable_coord_keys`: coordenadas dessas chaves.
- `expanded_chuncks`: chunks já expandidos.
- `destroy`: libera a estrutura.

É o **produto final** que o módulo entrega ao pipeline de expansão.

---

# Funções Principais

## ft_create_expandable_object
Cria e inicializa o `t_expandable_object`.

Lógica:
- Aloca estrutura.
- Gera dados de expansão via `ft_create_expansion_data`.
- Copia valor original do token.
- Prepara campos para expansão posterior.

---

## ft_create_expansion_data
Pipeline central de análise.

Lógica:
- Localiza seções expansíveis via `ft_find_expandable`.
- Determina se existem globs via `ft_has_globs`.
- Filtra apenas as seções que contêm chaves reais (`ft_find_keys_to_expand`).
- Copia dados relevantes para o objeto.

---

## ft_find_expandable
Identifica trechos elegíveis para expansão.

Lógica:
- Separa partes ignorando texto entre aspas simples.
- Empilha em `list` e `coord_list` apenas se a seção permitir expansão.
- Converte listas em arrays para acesso rápido.

---

## ft_find_keys_to_expand
Filtra dentro das seções expansíveis apenas as *chaves reais*.

Lógica:
- Percorre cada trecho de `expandable_sections`.
- Usa `ft_extract_keys` para identificar `$VAR`, `${VAR}`, `$?`, `$1` etc.
- Constrói arrays finais contendo somente chaves e coordenadas dessas chaves.

---

## ft_extract_keys
Extrai chaves simples ou compostas:

- `$X` quando X é um caractere especial ou dígito.
- `$VAR`, `${VAR}`, `$VAR123`, etc.
- Coleta coordenadas relativas à string original.

Para casos complexos, delega para `ft_track_keys`.

---

## ft_track_keys
Percorre caracteres após `$` até montar a chave completa.

Aceita:
- letras
- dígitos (exceto primeiro char)
- underscore

Retorna substring + coordenadas.

---

## ft_has_globs
Detecta se algum trecho expansível contém `*` fora de aspas duplas.

Usado para decidir se deve ocorrer expansão de globbing posteriormente.

---

## ft_copy_matrix / ft_copy_coord_matrix
Geram cópias completas e seguras dos arrays,
evitando shallow-copies que quebrariam na destruição.

---

## ft_create_expandable_sections
Cria container para coleta de trechos expansíveis.

Inicializa:
- listas
- callbacks
- arrays nulos

---

## ft_destroy_expandable_object / ft_destroy_expandable_sections
Destruição segura das estruturas principais,
liberando arrays, listas, coordenadas e strings.

---
