# Hash Table Module Documentation

This module provides a hash table implementation backed by a linked-list
array structure.\
It includes functionality for hashing keys, inserting items, searching,
and removing items.

------------------------------------------------------------------------

## Features

-   **DJB2-based hashing** (`ft_hash`)
-   **Chaining for collision handling** via linked lists
-   **Replace-on-insert** behavior when a key already exists
-   **Custom free-function** support for deallocating stored items

------------------------------------------------------------------------

## Data Structures

### `t_ht`

``` c
typedef struct s_ht
{
    char *key;
    void *value;
} t_ht;
```

### Hash Table Container

The hash table uses:

``` c
t_linkedlist_array
```

from the linked-list array module.

------------------------------------------------------------------------

## API Overview

### `int ft_hash(char *key);`

Computes and returns a DJB2-based hash modulo `ENV_HASH_SIZE`.

### `t_linkedlist_array *ft_init_ht(int size, t_ht **key_value, void (*ft_free_item_ht)(void *arg));`

Initializes a hash table of `size` and populates it with initial
key/value pairs.

------------------------------------------------------------------------

### `void *ft_find_ht(t_linkedlist_array *ht, char *key);`

Searches for a key and returns the `t_linkedlist_node *` containing it,
or `NULL`.

------------------------------------------------------------------------

### `void ft_include_item_ht(t_linkedlist_array *ht, t_ht *new, void (*ft_free_item_ht)(void *arg));`

Inserts or replaces an entry.

------------------------------------------------------------------------

### `void ft_remove_item_ht(t_linkedlist_array *ht, t_ht *new, void (*ft_free_item_ht)(void *arg));`

Removes an entry from the table.


## Notes

-   The module assumes that keys are unique.
-   Collisions are handled via linked lists (separate chaining).
-   The caller must provide a free-function to safely deallocate values.
