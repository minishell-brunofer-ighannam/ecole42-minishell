/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 11:31:58 by ighannam          #+#    #+#             */
/*   Updated: 2025/12/01 08:38:19 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executer.h"

static void	ft_update_ht(t_binary_tree_node *node, char *pwd, char *old_pwd);

int	ft_cd(t_binary_tree_node *node)
{
	char	*pwd;
	char	*old_pwd;

	old_pwd = getcwd(NULL, 0);
	if (!(ft_get_tokens(node))[1])
	{
		ft_putstr_fd("cd: missing argument\n", STDERR_FILENO);
		return (1);
	}
	if (chdir((ft_get_tokens(node))[1]->value) == -1)
	{
		perror("cd");
		if (old_pwd)
			free(old_pwd);
		return (1);
	}
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		perror("getcwd");
		free(old_pwd);
		return (1);
	}
	ft_update_ht(node, pwd, old_pwd);
	return (0);
}

static void	ft_update_ht(t_binary_tree_node *node, char *pwd, char *old_pwd)
{
	t_linkedlist_node	*item_list_pwd;
	t_linkedlist_node	*item_list_old_pwd;
	char				*key_value_pwd;
	char				*key_value_old_pwd;

	item_list_pwd = (t_linkedlist_node *)ft_find_ht(ft_get_ht_env(node), "PWD");
	key_value_pwd = ft_strjoin("PWD=", pwd);
	if (item_list_pwd)
		ft_set(ft_get_ht_env(node), key_value_pwd);
	item_list_old_pwd = (t_linkedlist_node *)ft_find_ht(ft_get_ht_env(node), "OLDPWD");
	key_value_old_pwd = ft_strjoin("OLDPWD=", old_pwd);
	if (item_list_old_pwd)
		ft_set(ft_get_ht_env(node), key_value_old_pwd);
	free(pwd);
	free(old_pwd);
	free(key_value_pwd);
	free(key_value_old_pwd);
}
