# HASHTABLE PARA O ENV

O programa precisa herdar o **envp da main para executar comandos (buscar os executáveis e executar o built-in env) e guardar variáveis de ambiente. Inclusive, variáveis declaradas com export ficam no env também.

Para guardar o env optamos por utilizar a estrutura de hashtable. A escolha se deu para aprendermos essa estrutura e porque é um jeito eficiente de procurar informações, uma vez que a busca é feita por possição em um array e não percorrendo toda uma estrutura até encontrar algo.

Para gerar a hashtable com as variáveis do **envp, temos:
- int ft_hash(char *key) --> retorna a posição do valor de "key" na table a partir da chave e de um valor pre-defindo ENV_HASH_SIZE 256. Função usada: djb2 hash function (hash = ((hash << 5) + hash) + *key;)


