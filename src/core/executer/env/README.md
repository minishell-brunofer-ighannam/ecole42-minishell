# Environment Module (`env`) -- Documentation

This module implements the **environment handling system** for the
Minishell project.\
It manages environment variables using a hash table, variable expansion,
and glob expansion.

------------------------------------------------------------------------

## 📌 Overview

The module provides:

-   Hash table initialization from `envp`
-   Splitting `KEY=VALUE` strings
-   Managing environment entries (`t_env_value`)
-   Expanding variables (`$VAR`, `$?`, `$$`, `$0`)
-   Glob expansion (`*`, handling duplicates, matching, sorting)
-   Directory listing helpers

------------------------------------------------------------------------

## 📂 Data Structures

### `t_env_value`

``` c
typedef struct s_env_value
{
    char *value;
    int set;
} t_env_value;
```

Represents the value stored inside the hash table for each environment
key.

------------------------------------------------------------------------

## 🚀 Main Functions

### `t_linkedlist_array *ft_init_ht_env(char **envp);`

Initializes the environment hash table using the provided `envp`.

### `void ft_free_item_ht_env(void *node_ht);`

Frees a hash table node created by the env module.

### `char *ft_expand_var(const char *s, t_linkedlist_array *ht_env);`

Expands shell variables such as:

-   `$VAR`
-   `$?`
-   `$$`
-   `$0`
-   invalid variables (`$1`, `$!`) → empty string

### `char **ft_expand_glob(const char *s);`

Expands patterns like:

-   `*.c`
-   `test*`
-   `****a***b***` → simplified internally

Returns `NULL` if nothing matches.

------------------------------------------------------------------------

## 📝 Example: Initializing the Environment

``` c
t_linkedlist_array *env = ft_init_ht_env(envp);
```

------------------------------------------------------------------------

## 🔍 Example: Expanding a Variable

``` c
char *expanded = ft_expand_var("$HOME", env);
```

------------------------------------------------------------------------

## 🌟 Example: Glob Expansion

``` c
char **files = ft_expand_glob("*.c");
```

------------------------------------------------------------------------

## 🗑 Freeing an Environment Entry

``` c
ft_free_item_ht_env(entry);
```
