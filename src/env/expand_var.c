/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 13:50:52 by ighannam          #+#    #+#             */
/*   Updated: 2025/11/13 18:09:46 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*ft_remove_first_char(char *s);
static char	*ft_get_pid(void);
static char	*ft_expand_regular(char *key, t_linkedlist_array *ht_env);

char	*ft_expand_var(char *s, t_linkedlist_array *ht_env)
{
	char	*key;
	char	*expanded;

	key = ft_remove_first_char(s);
	if (!key)
		return (NULL);
	else if (key[0] == '$')
		expanded = ft_get_pid();
	else if (key[0] == '0')
	{
		expanded = ft_calloc(10, sizeof(char));
		ft_strlcpy(expanded, "minishell", 10);
	}
	else if (ft_isdigit(key[0]) == 1)
		return (NULL);
	else
		expanded = ft_expand_regular(key, ht_env);
	free(key);
	return (expanded);
}

static char	*ft_expand_regular(char *key, t_linkedlist_array *ht_env)
{
	char	*expanded;
	char	*value;
	int		len;

	if (!ft_find_ht(ht_env, key))
		return (NULL);
	value = ((t_env_value *)((t_ht *)((t_linkedlist_node *)ft_find_ht(ht_env,
						key))->content)->value)->value;
	len = ft_strlen(value);
	expanded = ft_calloc(len + 1, sizeof(char));
	ft_strlcpy(expanded, value, len + 1);
	return (expanded);
}

static char	*ft_remove_first_char(char *s)
{
	char	*s_without_first;
	int		len;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	if (len == 0)
		return (NULL);
	s_without_first = malloc(len);
	if (!s_without_first)
		return (NULL);
	i = 1;
	j = 0;
	while (s[i])
	{
		s_without_first[j] = s[i];
		i++;
		j++;
	}
	s_without_first[j] = '\0';
	return (s_without_first);
}

static char	*ft_get_pid(void)
{
	int		fd;
	char	buf[32];
	int		bytes_read;
	char	*pid;
	int		pid_int;

	fd = open("/proc/self/stat", O_RDONLY);
	if (fd < 0)
		return (NULL);
	bytes_read = read(fd, buf, sizeof(buf) - 1);
	if (bytes_read <= 0)
		return (NULL);
	buf[bytes_read] = '\0';
	pid_int = ft_atoi(buf);
	pid = ft_itoa(pid_int);
	return (pid);
}
