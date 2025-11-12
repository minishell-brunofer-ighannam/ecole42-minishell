/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 14:40:26 by ighannam          #+#    #+#             */
/*   Updated: 2025/11/12 15:39:41 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char **ft_possible_paths(t_linkedlist_array *ht_env);
static void	ft_free_possible_paths(char **possible_paths);

static char **ft_possible_paths(t_linkedlist_array *ht_env)
{
	t_linkedlist_node *node_path;
	t_ht *content;
	t_env_value *value;
	char **possible_paths;

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

static void	ft_free_possible_paths(char **possible_paths)
{
	int	i;

	if (!possible_paths)
		return ;
	i = 0;
	while (possible_paths[i])
	{
		free(possible_paths[i]);
		i++;
	}
	free(possible_paths);
}

char	*ft_find_path(t_linkedlist_array *ht_env, char *cmd)
{
	int		i;
	char	*path;
	char	*path_temp;
	char	**possible_paths;

	if (ft_strchr(cmd, '/') && access(cmd, F_OK) == 0)
		return (ft_strdup(cmd));
	if (!ht_env)
		return (NULL);
	possible_paths = ft_possible_paths(ht_env);
	i = -1;
	if (!possible_paths || ft_strlen(cmd) == 0)
		return (NULL);
	while (possible_paths[++i])
	{
		path = ft_strjoin(possible_paths[i], "/");
		path_temp = path;
		path = ft_strjoin(path, cmd);
		free(path_temp);
		if (access(path, X_OK) == 0)
		{
			ft_free_possible_paths(possible_paths);
			return (path);
		}
		else
			free(path);
	}
	printf("command not found: %s\n", cmd);
	ft_free_possible_paths(possible_paths);
	return (NULL);
}


