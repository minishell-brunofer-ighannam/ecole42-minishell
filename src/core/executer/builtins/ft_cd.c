/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 11:31:58 by ighannam          #+#    #+#             */
/*   Updated: 2025/12/13 14:06:38 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executer.h"

static void	ft_update_ht(t_binary_tree_node *node, char *pwd, char *old_pwd);
static int	ft_verify_cd(t_binary_tree_node *node, char *old_pwd);
static int	ft_cd_without_arg(t_binary_tree_node *node, char *old_pwd);

int	ft_cd(t_binary_tree_node *node)
{
	char				*pwd;
	char				*old_pwd;
	t_linkedlist_node	*node_ht;
	t_ht				*ht;

	node_ht = ft_find_ht(ft_get_ht_env(node), "PWD");
	if (!node_ht)
		old_pwd = ft_strdup("");
	else
	{
		ht = node_ht->content;
		old_pwd = ft_strdup(((t_env_value *)ht->value)->value);
	}
	if (ft_verify_cd(node, old_pwd) == 1)
		return (1);
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

static int	ft_verify_cd(t_binary_tree_node *node, char *old_pwd)
{
	if (ft_get_argv(node)[1] == NULL || ft_strcmp(ft_get_argv(node)[1],
			"~") == 0)
		return (ft_cd_without_arg(node, old_pwd));
	if (ft_get_argv(node)[2] != NULL)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO);
		free(old_pwd);
		return (1);
	}
	if (chdir((ft_get_tokens(node))[1]->last_build->token_expanded) == -1)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(old_pwd, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		if (errno == ESTALE)
			ft_putendl_fd("No such file or directory", STDERR_FILENO);
		else
		{
			ft_putendl_fd(strerror(errno), STDERR_FILENO);
		}
		free(old_pwd);
		return (1);
	}
	return (0);
}

static void	ft_update_ht(t_binary_tree_node *node, char *pwd, char *old_pwd)
{
	t_linkedlist_node	*item_list_pwd;
	t_linkedlist_node	*item_list_old_pwd;
	char				*key_value_pwd;
	char				*key_value_old_pwd;

	(void)item_list_old_pwd;
	(void)item_list_pwd;
	item_list_pwd = (t_linkedlist_node *)ft_find_ht(ft_get_ht_env(node), "PWD");
	key_value_pwd = ft_strjoin("PWD=", pwd);
	ft_set(ft_get_ht_env(node), key_value_pwd);
	item_list_old_pwd = (t_linkedlist_node *)ft_find_ht(ft_get_ht_env(node),
			"OLDPWD");
	key_value_old_pwd = ft_strjoin("OLDPWD=", old_pwd);
	ft_set(ft_get_ht_env(node), key_value_old_pwd);
	free(key_value_old_pwd);
	free(key_value_pwd);
	free(old_pwd);
	free(pwd);
}

static int	ft_cd_without_arg(t_binary_tree_node *node, char *old_pwd)
{
	t_linkedlist_node	*node_home;
	t_ht				*ht_content;

	node_home = ft_find_ht(ft_get_ht_env(node), "HOME");
	if (node_home)
		ht_content = node_home->content;
	if (!node_home)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
		free(old_pwd);
		return (1);
	}
	if (chdir(((t_env_value *)(ht_content->value))->value) == -1)
	{
		perror("cd");
		free(old_pwd);
		return (1);
	}
	return (0);
}
