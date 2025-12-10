/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_glob_i.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 11:08:11 by ighannam          #+#    #+#             */
/*   Updated: 2025/12/10 16:53:18 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static char	*ft_remove_duplicated_stars(const char *s);
static char	**ft_list_curr_repo(void);
static int	ft_count_curr_dir_entries(void);
static char	**ft_match_glob(char **curr_repo, char *after_removal);

char	**ft_expand_glob(const char *s)
{
	char	*after_removal;
	char	**list_curr_repo;
	char	**matched;
	char	*removed;
	char	*prefix;
	
	after_removal = ft_remove_duplicated_stars(s);
	prefix = ft_get_prefix(s);
	removed = ft_remove_prefix(s, prefix);
	list_curr_repo = ft_list_curr_repo();
	matched = ft_match_glob(list_curr_repo, removed);
	if (matched[0] == NULL)
	{
		ft_clean_array_str(matched);
		ft_clean_array_str(list_curr_repo);
		free(after_removal);
		free(removed);
		return (NULL);
	}
	matched = ft_put_prefix(matched, prefix);
	ft_ordene_array_str_alpha(matched);
	ft_clean_array_str(list_curr_repo);
	free(after_removal);
	free(removed);
	free(prefix);
	return (matched);
}

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

char *ft_get_prefix(const char *s)
{
	char *prefix;
	int len;
	char *pwd;
	char *with_bar;

	if (s[0] == '.' && s[1] == '/')
		return(ft_strdup("./"));
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
		free (prefix);
		free (pwd);
		return (NULL);
	}
	free(pwd);
	free(with_bar);
	return (prefix);
}

char	*ft_remove_prefix(const char *s, char *prefix)
{
	char	*removed;
	int len_prefix;
	int len_s;

	if (!s)
		return (NULL);
	if (!prefix)
		return (ft_strdup(s));
	len_prefix = ft_strlen(prefix);
	len_s = ft_strlen(s);
	removed = ft_substr(s, len_prefix, len_s - len_prefix);
	return (removed);
}

static char	*ft_remove_duplicated_stars(const char *s)
{
	char	*after_removal;
	int		len;
	int		i;
	int		j;

	i = 1;
	j = 1;
	len = ft_strlen(s);
	after_removal = ft_calloc(len + 1, sizeof(char));
	after_removal[0] = s[0];
	while (s[i])
	{
		if ((s[i] == '*' && s[i - 1] != '*') || s[i] != '*')
		{
			after_removal[j] = s[i];
			j++;
		}
		i++;
	}
	return (after_removal);
}

static char	**ft_list_curr_repo(void)
{
	char			**curr_repo;
	DIR				*dir;
	struct dirent	*dir_entries;
	int				i;

	dir = opendir(".");
	if (!dir)
		return (NULL);
	dir_entries = readdir(dir);
	curr_repo = ft_calloc(ft_count_curr_dir_entries() + 1, sizeof(char *));
	if (!curr_repo)
	{
		closedir(dir);
		return (NULL);
	}
	i = 0;
	while (dir_entries)
	{
		curr_repo[i] = ft_strdup(dir_entries->d_name);
		i++;
		dir_entries = readdir(dir);
	}
	closedir(dir);
	return (curr_repo);
}

static int	ft_count_curr_dir_entries(void)
{
	DIR				*dir;
	struct dirent	*dir_entries;
	int				count_dir_entries;

	dir = opendir(".");
	if (!dir)
		return (0);
	dir_entries = readdir(dir);
	count_dir_entries = 0;
	while (dir_entries)
	{
		count_dir_entries++;
		dir_entries = readdir(dir);
	}
	closedir(dir);
	return (count_dir_entries);
}

static char	**ft_match_glob(char **curr_repo, char *after_removal)
{
	char	**matched;
	int		size_matched;
	int		i;

	if (!curr_repo)
		return (ft_calloc(1, sizeof(char *)));
	size_matched = 0;
	i = -1;
	while (curr_repo[++i])
	{
		if (ft_matched_glob(after_removal, curr_repo[i]) == 1)
			size_matched++;
	}
	matched = ft_calloc(size_matched + 1, sizeof(char *));
	i = -1;
	size_matched = 0;
	while (curr_repo[++i])
	{
		if (ft_matched_glob(after_removal, curr_repo[i]) == 1)
		{
			matched[size_matched] = ft_strdup(curr_repo[i]);
			size_matched++;
		}
	}
	return (matched);
}
