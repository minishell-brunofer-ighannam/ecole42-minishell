# Lexer

O lexer geralmente **não interpreta a estrutura da frase**, mas apenas transforma o texto cru em tokens significativos. Porém ele pode se basear em algumas restrições gramaticais para decidir o tipo do token, e se ele é válido, ou não.

## Tipo do Token

Então o token será classificado em alguns tipos:

```c
typedef enum e_token_type {
    TOKEN_CMD,				// comando
    TOKEN_ARG,				// argumento
    TOKEN_PIPE,				// pipe
    TOKEN_REDIRECT_IN,		// redirect de entrada
    TOKEN_REDIRECT_OUT,		// redirect de saída
    TOKEN_PAREN_OPEN,		// abertura de parênteses
    TOKEN_PAREN_CLOSE,		// fechamento de parênteses
    TOKEN_END				// fim da frase
}   t_token_type;
```
E haverá lassificações do tipo de áspas que ele terá.

```c
typedef enum e_quote_type {
    QUOTE_NONE,
    QUOTE_SINGLE,
    QUOTE_DOUBLE
}   t_quote_type;
```

Dessa forma a estrutura do token será essa:

```c
typedef struct s_token {
    char			*value;			// valor do token
    t_token_type	type;			// tipo do token
    int				position;		// índice na linha
    int				arg_index;		// se for argumento, qual o número dele
    bool			valid;			// se está numa posição sintaticamente válida
	bool			is_expandable;	// se é expandível
	t_quote_type	quote_type;		// tipo de áspas
}   t_token;
```
Podemos ter uma estrutura para uma linha, ou seja, o conjunto de tokens que formam a alinha:

```c
typedef struct s_token_group {
    t_token	**tokens;
	int		size;
}	t_token_group
```
## Checagem de Token Válido

Depois de tokenizar haverá uma função para cada tipo de token que irá dizer se aquele token é válido, ou não, exemplo:

```c
void	validate_token_cmd(t_token *token, t_token_group *token_group)
{
	t_token	**tokens;
	t_token	*left_token;
	t_token	*right_token;

	// by default token is valid, the below code will change that if needed.
	token->valid = true;
	tokens = token_group->tokens;

	// get the token on the left
	if (token->position == 0)
		left_token = NULL;
	else
		left_token = tokens[token->position - 1];
	// get the token on the right
	if (token->position == token_group->size - 1)
		right_token = NULL;
	else
		right_token = tokens[token->position + 1];
	// validate token position
	if (left_token && (left_token->type != TOKEN_PIPE || left_token->type != TOKEN_PAREN_OPEN))
		token->valid = false;
	if (right_token && (right_token->type == TOKEN_PAREN_CLOSE))
		token->valid = false;
}
```

