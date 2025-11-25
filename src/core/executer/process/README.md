# Process

This is the **process module**, responsible for managing processes, pipes,
and related tasks in a structured way. One of the key components of this
module is the **child_process** functionality, which simplifies creating
child processes with optional inter-process communication via pipes.

## Child Process

The `child_process` component allows you to:

- Create a child process using `fork()`.
- Automatically manage pipes for communication between parent and child.
- Execute a user-defined task in the child process.
- Clean up resources safely using a `destroy` function.

It is designed with flexibility in mind, allowing callbacks for both pipe
management and child task execution, with generic arguments passed through
`void*` pointers.

### Flow Diagram

```
            ┌────────────────────────────┐
            │        Parent Process      │
            │                            │
            │ 1. Calls ft_child_process  │
            │ 2. Creates t_child_process │
            │ 3. Creates pipes (pipe())  │
            │ 4. Calls manage_pipes()    │
            └────────────┬───────────────┘
                         │ fork()
                         ▼
            ┌──────────────────────────┐
            │       Child Process      │
            │                          │
            │ 1. pid == 0              │
            │ 2. Executes child_task() │
            │ 3. Performs child work   │
            │ 4. exit(0) at the end    │
            └────────────┬─────────────┘
                         │
                         │ Pipes
                         │
         ┌───────────────┴───────────────┐
         │                               │
  pipe[0] (read)                     pipe[1] (write)
         │                               │
         ▼                               ▼
   Parent reads data <- Child writes -> Child
```


### Notes

- `child_process` is ideal for modular code that needs controlled
  process creation.
- Pipes provide a simple mechanism for bidirectional communication
  between parent and child processes.
- Resource management is handled via the `destroy` function,
  preventing memory leaks or dangling pipes.
- The current implementation **has been tested** with the provided unit
  tests:
  - Simple child process creation.
  - Pipe communication (child writes, parent reads).
  - Execution of `/bin/ls -la` via `execve` in a child process.
- All tested cases passed successfully without memory leaks.
- **Caution:** Although these tests cover key scenarios, it's recommended
  to test `child_process` in other circumstances and edge cases
  depending on your application needs.
