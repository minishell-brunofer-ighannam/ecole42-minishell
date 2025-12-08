/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 15:40:29 by ighannam          #+#    #+#             */
/*   Updated: 2025/12/08 17:03:48 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	ft_keys_export(t_linkedlist_array *export, char **keys_export);
static void	ft_print_export(t_linkedlist_array *ht, char *key);
static int	ft_validate_key_export(t_ht *content);

int	ft_export(t_linkedlist_array *ht_env, const char *key_value)
{
	char		**keys_export;
	int			i;
	t_ht		*content;
	t_env_value	*value;

	if (!key_value)
	{
		keys_export = ft_calloc(ht_env->nodes_amount + 1, sizeof(char *));
		ft_keys_export(ht_env, keys_export);
		ft_ordene_array_str(keys_export);
		i = -1;
		while (keys_export[++i])
			ft_print_export(ht_env, keys_export[i]);
		free(keys_export);
		return (0);
	}
	content = ft_content_node_ht(key_value);
	value = content->value;
	if (ft_validate_key_export(content) == 0)
		return (1);
	if (value->value || !ft_find_ht(ht_env, content->key))
		ft_include_item_ht(ht_env, content, ft_free_item_ht_env);
	return (0);
}

static int	ft_validate_key_export(t_ht *content)
{
	int		i;
	char	*key;

	key = content->key;
	i = -1;
	while (key[++i])
	{
		if (ft_isalnum(key[i]) == 0 && key[i] != '_')
		{
			i = 0;
			break ;
		}
	}
	if (((ft_isalpha(key[0]) == 0) && key[0] != '_') || i == 0)
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(content->key, 2);
		ft_putstr_fd(((t_env_value *)(content->value))->value, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		free(content->key);
		free(content->value);
		free(content);
		return (0);
	}
	return (1);
}

static void	ft_keys_export(t_linkedlist_array *export, char **keys_export)
{
	t_linkedlist_node	*node;
	t_linkedlist		**list;
	t_ht				*content;
	int					i;
	int					j;

	list = export->list;
	i = 0;
	j = 0;
	while (list[i])
	{
		node = list[i]->first;
		while (node)
		{
			content = (t_ht *)node->content;
			keys_export[j] = content->key;
			j++;
			node = node->next;
		}
		i++;
	}
}

static void	ft_print_export(t_linkedlist_array *ht, char *key)
{
	t_ht				*content;
	t_env_value			*env_value;
	t_linkedlist_node	*n;

	n = (t_linkedlist_node *)ft_find_ht(ht, key);
	if (n)
	{
		content = n->content;
		if (!content || !content->key || ft_strncmp(content->key, "_",
				ft_strlen(content->key)) == 0)
			return ;
		env_value = (t_env_value *)content->value;
		if (env_value->set == 0 && env_value->value)
			printf("declare -x %s=\"%s\"\n", content->key, env_value->value);
		else if (env_value->set == 0 && !env_value->value)
			printf("declare -x %s\n", content->key);
		else if (env_value->set == 0 && *(env_value->value) == 0)
			printf("declare -x %s=\"\"\n", content->key);
	}
}
