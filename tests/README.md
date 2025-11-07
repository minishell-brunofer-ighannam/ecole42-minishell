# 🧪 Automated Tests

The project has an **automated testing system in C**, integrated with the **Makefile**.
All tests located inside the [`tests/`](./tests) folder can be executed automatically using the `tests` flag of `make`.

---

## ⚙️ How to Run All Tests

To compile and execute **all tests automatically**, simply run:

```bash
make tests
```
### The command:
- Compiles the test files defined in the Makefile.
- Executes each test binary individually.
- Displays the result of each test formatted in the terminal.
- Runs **Valgrind** to check for memory leaks.

### Example of expected output:

```bash
code% make tests
testting split...
test 1: OK
test 2: OK

testting linkedkist...
test 1: OK
test 2: OK
test 3: OK
test 4: OK
test 5: OK
```
## 🧩 Structure of a Test

Each test is implemented as a C program inside the `tests/` folder, usually with an independent `main()`.

**Example**: `tests/linkedkist.c`

```c
#include "minishell.h"
#include "tests.h"

int	main(void)
{
	t_linkedlist	*list;

	list = ft_new_linkedlist();
	list->push(list, ft_strdup("Bruno"));
	list->push(list, ft_strdup("Fernendes"));
	list->push(list, ft_strdup("Valero"));
	list->push(list, ft_strdup("Nunes"));

	printf("test 1: %s\n", status(!ft_strncmp(list->first->content, "Bruno", 6)));
	printf("test 2: %s\n", status(!ft_strncmp(list->last->content, "Nunes", 6)));
	printf("test 3: %s\n", status(!ft_strncmp(list->first->next->content, "Fernendes", 10)));
	printf("test 4: %s\n", status(!ft_strncmp(list->last->prev->content, "Valero", 7)));

	list->destroy(&list, free);
	printf("test 5: %s\n", status(list == NULL));
}
```

### Each test must:

- Include the `tests.h` header (which contains utilities like the `status()` function).
- Display results in the format test X: OK or test X: ERROR.
- **Free all allocated memory** before exiting.

## 🧠 How to Create a New Test

1. Create a new file inside the `tests/` folder

	Exemplo:
	```bash
	touch tests/myfeature.c
	```
2. Implement the test following the pattern shown above.
3. Add a new compilation rule in the **Makefile**, similar to the others:
	```makefile
	myfeature: tests/myfeature.c tests/tests.c $(COMPILATION_DEPENDENCIES)
		@echo "$(LIGHT_GREEN)>> $(BOLD)compiling$(RESET) $(LIGHT_CYAN)./$@$(RESET)..." && sleep $(SLEEP)
		@$(CC) $(CFLAGS) $^ -o $@ $(DEPENDENCIES)
	```
4. Finally, add the new test to the tests: rule, so that it is compiled and executed automatically:
	```makefile
	# add the executable name (myfeature) in this example.
	tests: split linkedkist myfeature
		@clear && echo "code% make tests"
		@echo "$(LIGHT_GREEN)$(BOLD)testting$(RESET) $(LIGHT_CYAN)split$(RESET)..." && sleep $(SLEEP)
		@valgrind -q --track-origins=yes --show-leak-kinds=all --leak-check=full ./split
		@echo "$(LIGHT_GREEN)$(BOLD)testting$(RESET) $(LIGHT_CYAN)linkedkist$(RESET)..." && sleep $(SLEEP)
		@valgrind -q --track-origins=yes --show-leak-kinds=all --leak-check=full ./linkedkist
		@echo "$(LIGHT_GREEN)$(BOLD)testting$(RESET) $(LIGHT_CYAN)myfeature$(RESET)..." && sleep $(SLEEP) # add the print
		@valgrind -q --track-origins=yes --show-leak-kinds=all --leak-check=full ./myfeature # add the command
	```

## 🧹 Tips and Best Practices

- Always use `valgrind` to ensure there are no memory leaks.
- Use **clear and short names** for test binaries (`linkedkist`, `split`, `parser`, etc.).
- Prefer creating a **separate test for each module** of the project.
- Use **helper functions** in `tests/tests.c` to avoid code repetition.
