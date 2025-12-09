/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 11:31:58 by ighannam          #+#    #+#             */
/*   Updated: 2025/12/09 16:29:16 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executer.h"

static void	ft_update_ht(t_binary_tree_node *node, char *pwd, char *old_pwd);
static int	ft_verify_cd(t_binary_tree_node *node);

int	ft_cd(t_binary_tree_node *node)
{
	char	*pwd;
	char	*old_pwd;
	t_ht	*ht;

	ht = ft_find_ht(ft_get_ht_env(node), "PWD")->content;
	old_pwd = ft_strdup(((t_env_value *)ht->value)->value);
	if (ft_verify_cd(node) == 1)
	{
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

static int	ft_verify_cd(t_binary_tree_node *node)
{
	if (!(ft_get_tokens(node))[1])
	{
		ft_putstr_fd("cd: missing argument\n", STDERR_FILENO);
		return (1);
	}
	if (ft_get_argv(node)[2] != NULL)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	if (chdir((ft_get_tokens(node))[1]->last_build->token_expanded) == -1)
	{
		perror("cd");
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

	item_list_pwd = (t_linkedlist_node *)ft_find_ht(ft_get_ht_env(node), "PWD");
	key_value_pwd = ft_strjoin("PWD=", pwd);
	if (item_list_pwd)
		ft_set(ft_get_ht_env(node), key_value_pwd);
	item_list_old_pwd = (t_linkedlist_node *)ft_find_ht(ft_get_ht_env(node),
			"OLDPWD");
	key_value_old_pwd = ft_strjoin("OLDPWD=", old_pwd);
	if (item_list_old_pwd)
		ft_set(ft_get_ht_env(node), key_value_old_pwd);
	free(key_value_old_pwd);
	free(key_value_pwd);
	free(old_pwd);
	free(pwd);
}
