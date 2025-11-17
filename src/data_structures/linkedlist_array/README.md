# 🧩 linkedlist_array Module

---

## 📘 Overview

The **`linkedlist_array`** module implements a composite data structure that combines **a fixed array of dynamic linked lists**.
It is ideal for storing groups of elements that need to be **organized by category or index** — while keeping the **flexibility** of linked lists in each group.

Each position in the array (`list[i]`) contains a `t_linkedlist`, which can grow dynamically as elements are added.
This approach allows you to structure data hierarchically, for example:

- Buckets in a *hash table*
- Lists of tokens grouped by type
- Categorized symbol tables
- Independent queues under one manager

---

## ✅ Reliability and Memory Safety

All core functions of this module have been **unit tested** to ensure stability and correct behavior in various scenarios.
Tests verify creation, insertion, destruction, and boundary handling (invalid indexes, empty arrays, etc.).

Additionally, the module has been **verified to be free of memory leaks**,
ensuring safe memory management through proper use of the internal `destroy()` and user-provided `free_content` callbacks.
This makes `linkedlist_array` a **reliable and leak-free component** suitable for integration in larger C projects.

---

## 🧱 Main Structure

```c
typedef struct s_linkedlist_array
{
	int					size;          // Number of internal lists
	int					nodes_amount;  // Total nodes across all lists
	t_linkedlist		**list;        // Array of linked list pointers
	t_linkedlist_node	*(*push)(
			t_linkedlist_array *self, int idx, void *content);
	void				*(*destroy)(
			t_linkedlist_array **self, void (*free_content)(void *arg));
}	t_linkedlist_array;
```

---

## ⚙️ Core Functions

### `ft_new_linkedlist_array(int size)`

Creates and initializes a new `t_linkedlist_array` instance with `size` internal linked lists.

### Behavior:

- Allocates memory for the structure and each internal list.
- Sets function pointers (`push`, `destroy`).
- Returns `NULL` if any allocation fails.

#### Example:

```c
t_linkedlist_array *arr = ft_new_linkedlist_array(3);
// Creates an array with 3 independent lists
```

---

### `arr->push(arr, idx, content)`

Adds a new node containing `content` to the list at index `idx`.

### Behavior:

- Validates the index before insertion.
- Calls the internal list’s `push()` function to append the content.
- Increments the global `nodes_amount` counter.
- Returns a pointer to the new node, or `NULL` on error.

#### Example:

```c
int *a = malloc(sizeof(int));
*a = 42;
arr->push(arr, 0, a);  // adds 42 to list at index 0
```

---

### `arr->destroy(&arr, free)`

Releases all memory associated with the array and its internal linked lists.


### Behavior:

- Iterates through all internal lists, calling their `destroy()` function.
- Uses the `free_content` callback to free node contents.
- Frees the main structure and sets the reference pointer to `NULL`.

#### Example:

```c
arr->destroy(&arr, free); // frees everything and sets arr = NULL
```

---

## 🧩 Possible Applications

- **Hash table buckets**: each index holds a list of collisions (`list[idx]`).
- **Token grouping**: each list represents a token type.
- **Parallel queue manager**: each list acts as an independent queue.
- **Composite structures**: enables managing 2D dynamic data easily.

---

## 🧠 Summary

| Function / Field | Description |
|------|----------|
| **`ft_new_linkedlist_array()`** | Creates and initializes the array structure. |
| **`push()`** | Adds an element to a specific list. |
| **`destroy()`** | Frees all allocated memory. |
| **`size`** | Number of internal lists. |
| **`nodes_amount`** | Total number of nodes across all lists. |
| **`list[i]`** | Pointer to the linked list at index `i`. |

---

## 🧠 Summary

- Memory ownership of inserted content belongs to the user.
The `free_content` callback must properly free each node’s content.
- The `destroy()` function always **sets the main pointer to NULL**,
preventing dangling references.
- The module is designed to be **lightweight, safe, and modular**,
integrating easily with other components of your library.
