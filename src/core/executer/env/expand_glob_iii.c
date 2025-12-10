/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_glob_iii.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 17:31:01 by ighannam          #+#    #+#             */
/*   Updated: 2025/12/10 17:37:47 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

char	**ft_put_prefix(char **matched, char *prefix)
{
	int		i;
	char	*with_prefix;

	if (!prefix || !matched)
		return (matched);
	i = -1;
	while (matched[++i])
	{
		with_prefix = ft_strjoin(prefix, matched[i]);
		free(matched[i]);
		matched[i] = with_prefix;
	}
	return (matched);
}

char	*ft_get_prefix(const char *s)
{
	char	*prefix;
	int		len;
	char	*pwd;
	char	*with_bar;

	if (s[0] == '.' && s[1] == '/')
		return (ft_strdup("./"));
	len = ft_strlen(s);
	while (--len >= 0 && s[len] != '/')
		;
	if (!len)
		return (NULL);
	prefix = ft_substr(s, 0, len + 1);
	pwd = getcwd(NULL, 0);
	with_bar = ft_strjoin(pwd, "/");
	if (ft_strcmp(prefix, with_bar))
	{
		free(with_bar);
		free(prefix);
		free(pwd);
		return (NULL);
	}
	free(pwd);
	free(with_bar);
	return (prefix);
}

char	*ft_remove_prefix(const char *s, char *prefix)
{
	char	*removed;
	int		len_prefix;
	int		len_s;

	if (!s)
		return (NULL);
	if (!prefix)
		return (ft_strdup(s));
	len_prefix = ft_strlen(prefix);
	len_s = ft_strlen(s);
	removed = ft_substr(s, len_prefix, len_s - len_prefix);
	return (removed);
}
