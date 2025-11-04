# Libft – Custom Edition ⚙️

This repository contains a **customized** version of [libft](https://github.com/bruno-valero/ecole42-libft), originally developed for the [École 42](https://www.42sp.org.br/) curriculum.
Here, the library has been **adapted, expanded, and personalized** to meet my own needs in future projects, without the restrictions of the 42 regulations for the libft project.

> **Note:** The **original libft**, exactly as submitted for evaluation at 42, is available in the official repository:
> 📌 [https://github.com/bruno-valero/ecole42-libft](https://github.com/bruno-valero/ecole42-libft)

---

## 🧠 Purpose

The goals of this version are:
- Add new useful functions that are not part of the official libft.
- Modify existing functions for greater flexibility and efficiency.
- Create an independent repository to avoid mixing information with the original project.
- Serve as a **personal codebase** for use in any C project (including other projects from École 42 Cursus).

---

## 📁 Project Structure

- **Original Functions**
  Includes all functions implemented in the official libft version.
- **New Functions** *(constantly expanding)*
  - Additional utility functions for strings, memory, numbers, file handling, etc.
- **Adjustments and Optimizations**
  - Behavioral changes, performance improvements, and functions with extra parameters.

---

## 🔧 Compilation

To compile the library:

```bash
make
```

Other available commands:

```bash
make clean   # Remove object files (.o)
make fclean  # Remove object files and libft.a
make re      # Recompile the library from scratch
```

Compilation flags used:

```
-Wall -Wextra -Werror
```

---

## 📌 Notes

* This project **strictly follows all Norminette rules** and all restrictions imposed by 42.
* It may contain functions inspired by external libraries or my own implementations.
* Structure and functionality are subject to continuous changes.

---

## 📚 References

* [Original libft documentation](https://github.com/bruno-valero/ecole42-libft)
* Linux man pages: `man strlen`, `man memcpy`, etc.
* Personal study material and external references.
