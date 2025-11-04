/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 19:49:18 by brunofer          #+#    #+#             */
/*   Updated: 2025/09/29 14:26:15 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libstr.h"

static char	**run_split(char const *s, int	*coord_arr, int coord_arr_len);
static void	delete_words(char ***str, int end);
static int	split_with_coords(char const *src,
				int *coord_arr, int coord_arr_len, char **words);

char	**ft_split(char const *s, char c)
{
	int	*coord_arr;
	int	coord_arr_len;
	int	i;

	if (!s)
		return (NULL);
	coord_arr = (int *)malloc((ft_strlen((char *)s) + 1) * sizeof(int));
	if (!coord_arr)
		return (NULL);
	coord_arr_len = 0;
	i = -1;
	while (s[++i])
	{
		if (((i == 0) && (s[i] != c))
			|| ((i > 0) && (s[i] != c) && (s[i - 1] == c)))
			coord_arr[coord_arr_len++] = i;
		else if ((i > 0) && (s[i] == c && s[i - 1] != c))
			coord_arr[coord_arr_len++] = i - 1;
		else if ((s[i] != c && s[i + 1] == '\0'))
			coord_arr[coord_arr_len++] = i;
	}
	if (coord_arr_len % 2 != 0)
		coord_arr[coord_arr_len++] = i - 1;
	return (run_split(s, coord_arr, coord_arr_len));
}

static char	**run_split(char const *s, int	*coord_arr, int coord_arr_len)
{
	char	**words;

	words = (char **)malloc(((coord_arr_len / 2) + 1) * sizeof(char *));
	if (!words)
		return (NULL);
	if (!split_with_coords(s, coord_arr, coord_arr_len, words))
		return (NULL);
	free(coord_arr);
	words[(coord_arr_len / 2)] = (void *)0;
	return (words);
}

static void	delete_words(char ***str, int end)
{
	while (end >= 0)
	{
		free((*str)[end]);
		(*str)[end] = NULL;
		end--;
	}
	free(*str);
	*str = NULL;
}

static int	split_with_coords(char const *src,
		int *coord_arr, int coord_arr_len, char **words)
{
	int	i_words;
	int	i_src;
	int	i_current_word;

	i_words = -1;
	while (++i_words < (coord_arr_len / 2))
	{
		words[i_words] = malloc(
				(coord_arr[i_words * 2 + 1] - coord_arr[i_words * 2]) + 2
				);
		if (!words[i_words])
		{
			delete_words(&words, i_words - 1);
			return (0);
		}
		i_src = coord_arr[i_words * 2];
		i_current_word = 0;
		while (i_src <= coord_arr[i_words * 2 + 1])
			words[i_words][i_current_word++] = src[i_src++];
		words[i_words][i_current_word] = '\0';
	}
	return (1);
}
