/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 14:40:26 by ighannam          #+#    #+#             */
/*   Updated: 2025/11/10 11:14:09 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


char *ft_remove_dupplicated_asterisk(char *)
{
	char *clean_glob;

	
}

char	*ft_find_path(t_env **env, char *cmd)
{
	int		i;
	char	*path;
	char	*path_temp;
	char	**possible_paths;

	possible_paths = ft_split(ft_find_env_value("PATH", env), ':');
	i = -1;
	if (!possible_paths || ft_strlen(cmd) == 0)
		return (NULL);
	if (ft_strchr(cmd, '/') && access(cmd, F_OK) == 0)
		return (ft_strdup(cmd));
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
	printf("command not found: %s\n", cmd);
	return (NULL);
}

int	execute_cmd(t_node *cmd, char **envp)
{
	int pid;


	if (cmd->built_in == 1)
	{
		//call function
	}
	else
	{
		pid = fork();
		if (pid == 0)
		{
			/* code */
		}
	}

}
