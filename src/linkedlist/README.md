# Linked List Module (`t_linkedlist`)

This module provides a simple and safe implementation of **doubly-linked lists** in C.
It allows dynamic management of nodes with generic content and ensures safe memory handling.

## Features

- Create and initialize linked lists and nodes.
- Add nodes to the end of the list.
- Destroy nodes or entire lists safely.
- Handles content cleanup through user-provided functions.
- Fully tested and confirmed **memory-leak free**.

## Data Structures

### `t_linkedlist_node`

Represents a single node in the list:

- `content`: pointer to the data stored in the node.
- `next`: pointer to the next node (`NULL` if last).
- `prev`: pointer to the previous node (`NULL` if first).
- `destroy`: function to free the node and its content safely.

### `t_linkedlist`

Represents the doubly-linked list:

- `size`: number of nodes in the list.
- `first`: pointer to the first node.
- `last`: pointer to the last node.
- `push`: function to append a new node to the list.
- `destroy`: function to free all nodes and the list itself.

## Functions

- `ft_new_node(void *content)` – create a new node.
- `ft_destroy_node(t_linkedlist_node **node, void (*free_content)(void *))` – destroy a node safely.
- `ft_new_linkedlist(void)` – create a new empty list.
- `ft_push_new_node(t_linkedlist *list, void *content)` – add a node to the end of the list.
- `ft_linkedlist_destroy(t_linkedlist **list, void (*free_content)(void *))` – destroy all nodes and the list.

## Usage Examples

### Creating a List

```c
t_linkedlist *list;

list = ft_new_linkedlist();
if (!list)
    return (1); // handle allocation error
```

### Adding Nodes

```c
list->push(list, strdup("Alice"));
list->push(list, strdup("Bob"));
list->push(list, strdup("Charlie"));
```

### Accessing Nodes

```c
printf("First node: %s\n", (char *)list->first->content);
printf("Second node: %s\n", (char *)list->first->next->content);
printf("Last node: %s\n", (char *)list->last->content);
```

### Traversing Backwards

```c
printf("Second-to-last node: %s\n", (char *)list->last->prev->content);
```

### Destroying the List

```c
list->destroy(&list, free);
if (list == NULL)
    printf("List successfully destroyed\n");
```

## Notes

- All content added to the list should be dynamically allocated if it needs to be freed safely.
- The list and nodes are designed to be memory-leak safe when using the destroy functions correctly.
- The module supports generic content; you can store any type of data by using `void*`.
- Tested thoroughly: no memory leaks observed.
