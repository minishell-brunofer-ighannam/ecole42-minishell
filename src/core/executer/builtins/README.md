## Module Overview

Implemented builtins:

env

export

set (internal helper)

unset

These builtins operate on environment entries stored in a hash table.
Each entry contains a key and a value structure that stores both the string value and a flag that indicates whether the variable was explicitly assigned.

## Data Structures

Environment variables are stored using:

A hash table entry (key + value pointer)

A value structure containing:

the variable value string

an integer flag named "set"

A hash table made of an array of linked lists

Example structure layout (not actual code):

```c
typedef struct s_env_value {
char *value;
int set;
} t_env_value;

typedef struct s_ht {
char *key;
void *value;
} t_ht;
```

# Builtins Description

## 1. env

The env builtin prints the environment in the format KEY=value.

Behavior:

Variables with set = 1 are skipped

Variables with NULL values are skipped

Empty values print as KEY=

The key "_" is printed as _=/usr/bin/env

Environment traversal uses the hash table iterator function

Example usage:

```text
env
```

## 2. export

The export builtin supports two behaviors.

Case 1: export without arguments

Gathers all environment keys

Sorts them alphabetically

Prints them in Bash-like format:

declare -x KEY="VALUE"

declare -x KEY

declare -x KEY=""

The key "_" is skipped.

Case 2: export KEY=VALUE

Parses the assignment

Inserts or updates the variable in the hash table

Uses the project’s hash table insertion logic

Example:

```text
export PATH=/usr/bin
```

## 3. set

This is an internal helper used to manage the "set" flag of each variable.

Behavior:

If the variable does not exist or has set = 1, the new entry also receives set = 1

If the variable exists with set = 0, the new entry receives set = 0

The variable is then inserted into the hash table

## 4. unset

The unset builtin removes a variable from the environment.

Behavior:

If the key exists, it is removed from the hash table

If the key does not exist, nothing happens

Memory is freed using the environment-specific free function

Example:

```text
unset HOME
```


# Current Status

The builtins module currently includes:

Fully functional env, export, set, and unset builtins

Bash-like behavior when export is called without arguments

Sorted output for export

Correct handling of empty values and the "_" variable

Reliable integration with the custom hash table implementation

Safe memory management

# Future Improvements

Implement additional Minishell builtins (cd, pwd, echo, exit)

