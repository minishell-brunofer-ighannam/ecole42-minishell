# HASHTABLE PARA O ENV

O programa precisa herdar o **envp da main para executar comandos (buscar os executáveis e executar o built-in env) e guardar variáveis de ambiente. Inclusive, variáveis declaradas com export ficam no env também.

Para guardar o env optamos por utilizar a estrutura de hashtable. A escolha se deu para aprendermos essa estrutura e porque é um jeito eficiente de procurar informações, uma vez que a busca é feita por possição em um array e não percorrendo toda uma estrutura até encontrar algo.

Para gerar a hashtable com as variáveis do **envp, temos:
- int ft_hash(char *key) --> retorna a posição do valor de "key" na table a partir da chave e de um valor pre-defindo ENV_HASH_SIZE 256. Função usada: djb2 hash function (hash = ((hash << 5) + hash) + *key;)
- void	ft_set(t_env **env, char *key, char *value, int set) --> inclui ou atualiza uma chave e valor na hashtable
- void	ft_unset(t_env **env, char *key) --> exclui uma chave e valor da hashtable
- t_env	**ft_init_ht(char **envp) --> inicia a hashtable com as variáveis de ambiente
- char	**ft_split_env(char *s) --> função auxiliar para tratar o que é chave e o que é valor no env para formar a hashtable
- char	*ft_find_env_value(char *key, t_env **env) --> localizar valor na hashtable a partir de uma chave
- void	ft_env(t_env **env) --> função built-in env que poderá ser chamada se estiver contida na árvore
- void	ft_export(t_env **env, char *key, char *value) --> função built-in export que poderá ser chamada se estiver contida na árvore
- int	ft_count_keys_export(t_env **env) --> função auxiliar para contar quantas chaves o export tem. Ela é útil para alocarmos o array e ordená-lo depois, uma vez que a função export mostra os pares de chave e valor em ordem alfabética
- char	**ft_keys_array_export(t_env **env) --> forma o array com as chaves referentes ao export. Esse array será posteriormente ordenado
- void	ft_ordene_keys(char **all_keys) --> coloca um array de chars em ordem alfabética
- void	ft_swap_keys(int i, int j, char **all_keys)
- char	*ft_find_path(t_env **env, char *cmd) --> retorna o caminho de um comando



-set --> fazer flag para separar o que for set (ISA=10 (sem o export antes) vai só para o set) --> nesse caso, proponho que o nome do comando seja set.
-env --> imprime sempre a mesma coisa no _=
-export --> não imprime nada no _=
-OBS.: a última string do comando fica armazenada no _= no set

