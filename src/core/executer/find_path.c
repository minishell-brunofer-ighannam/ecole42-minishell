/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 14:40:26 by ighannam          #+#    #+#             */
/*   Updated: 2025/12/12 21:24:33 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

static char	**ft_possible_paths(t_linkedlist_array *ht_env);
static char	*ft_aux_find_path(char **possible_paths, char *cmd);
static void	ft_print_cmd_not_found(char *cmd);

char	*ft_find_path(t_linkedlist_array *ht_env, char *cmd)
{
	char	*path;
	char	**possible_paths;

	possible_paths = ft_possible_paths(ht_env);
	path = ft_aux_find_path(possible_paths, cmd);
	ft_clean_array_str(possible_paths);
	return (path);
}

static char	**ft_possible_paths(t_linkedlist_array *ht_env)
{
	t_linkedlist_node	*node_path;
	t_ht				*content;
	t_env_value			*value;
	char				**possible_paths;

	node_path = (t_linkedlist_node *)ft_find_ht(ht_env, "PATH");
	if (!node_path)
		return (NULL);
	content = (t_ht *)node_path->content;
	value = (t_env_value *)content->value;
	if (!value || !value->value)
		return (NULL);
	possible_paths = ft_split(value->value, ':');
	return (possible_paths);
}

static char	*ft_aux_find_path(char **possible_paths, char *cmd)
{
	int		i;
	char	*path;
	char	*path_temp;

	if (!possible_paths || cmd == NULL || !ft_strcmp("..", cmd))
	{
		ft_print_cmd_not_found(cmd);
		return (NULL);
	}
	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	i = -1;
	while (possible_paths[++i])
	{
		path = ft_strjoin(possible_paths[i], "/");
		path_temp = path;
		path = ft_strjoin(path, cmd);
		free(path_temp);
		if (access(path, X_OK) == 0)
			return (path);
		else
			free(path);
	}
	ft_print_cmd_not_found(cmd);
	return (NULL);
}

static void	ft_print_cmd_not_found(char *cmd)
{
	char	*path;

	if (!cmd)
		path = ft_strdup("'': command not found");
	else
		path = ft_strjoin(cmd, ": command not found");
	ft_putstr_fd(path, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	free(path);
}
