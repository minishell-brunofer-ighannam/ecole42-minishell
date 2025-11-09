# Splitter

The **Splitter** is a module responsible for breaking a command line into tokens, ready to be processed or executed.
It consists of **two main stages**: **raw splitting** and **token refinement**.

---

## 1. Raw Splitting

Raw splitting is the first stage of the splitter.
It takes the raw command line and performs an initial separation into words, preserving **quotes** and **escaped characters**.
The result is an array of strings that still contains quotes, escaped spaces, and other special characters.

> This stage acts as the foundation for lexical processing, preparing the tokens for refinement.

---

## 2. Token Refinement

Refinement is the second stage of the splitter, responsible for **cleaning and organizing the tokens** obtained from the raw splitting stage.

### Key functions of refinement:

- **Preserve and handle quotes**
  Quotes are maintained when necessary, and segments within quotes are protected from incorrect splitting.
  The quote state is tracked to open, close, or ignore unnecessary quotes.

- **Separate reserved tokens**
  Special shell characters, such as `>`, `<`, `|`, and `&&`, are recognized and separated into individual elements of the final array.
  This ensures operators are not confused with regular words.

- **Merge adjacent strings**
  In cases where quotes split tokens that should be continuous, refinement merges these fragments back together.
  This prevents artificial or incorrectly fragmented tokens.

- **Storage structure**
  Internally, a **linked list array** is used to temporarily store refined tokens.
  After processing, all tokens are copied into a **final string array**, which is returned for further use.

- **Preserve escapes and special characters**
  Escaped spaces and quotes within tokens are preserved so that subsequent parsing can correctly interpret the command line.

> Refinement transforms raw tokens into a clean structure ready for syntax analysis or execution, ensuring that each element of the command line is correctly separated and processed.
