/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raw_splitter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 17:35:20 by valero            #+#    #+#             */
/*   Updated: 2025/12/09 18:12:45 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raw_splitter_internal.h"

static t_splited_prompt	*ft_run_split(
							char const *str,
							int *coord_arr,
							int coord_arr_len);
static void				ft_delete_words(char ***str, int end);
static int				ft_split_with_coords(char const *src,
							int *coord_arr,
							int coord_arr_len,
							char **words);

/**
 * # ft_raw_splitter
 *
 * Main entry function. Scans the original
 * string, detects word boundaries (respecting
 * quotes), and builds the final
 * `t_splited_prompt` structure.
 *
 * Logic:
 * - Allocates a coordinates array.
 * - Identifies start/end positions via
 *   `ft_raw_splitter_get_words_position`.
 * - Converts coordinates into substrings
 *   with `ft_run_split`.
 */
t_splited_prompt	*ft_raw_splitter(char const *str)
{
	int			*coord_arr;
	t_int_array	array;

	if (!str)
		return (NULL);
	coord_arr = (int *)malloc((ft_strlen((char *)str) + 1) * sizeof(int));
	if (!coord_arr)
		return (NULL);
	array.array = coord_arr;
	array.len = 0;
	ft_raw_splitter_get_words_position(str, &array);
	return (ft_run_split(str, array.array, array.len));
}

/**
 * # ft_run_split
 *
 * Converts the coordinates array into
 * actual tokens.
 *
 * Logic:
 * - Creates a `t_splited_prompt` structure.
 * - Allocates a string array based on the
 *   number of coordinate pairs.
 * - Copies each slice using `coord_arr`.
 * - Builds the final coordinates array.
 */
static t_splited_prompt	*ft_run_split(
							char const *str,
							int *coord_arr,
							int coord_arr_len)
{
	char				**words;
	t_splited_prompt	*splited_prompt;
	int					i;

	splited_prompt = ft_create_splited_prompt();
	words = (char **)ft_calloc(((coord_arr_len / 2) + 1), sizeof(char *));
	if (!words)
		return (NULL);
	if (!ft_split_with_coords(str, coord_arr, coord_arr_len, words))
		return (NULL);
	splited_prompt->chuncks = words;
	splited_prompt->coords = ft_calloc(coord_arr_len / 2 + 1, sizeof(int *));
	i = -1;
	while (++i < (coord_arr_len / 2))
	{
		splited_prompt->coords[i] = ft_calloc(2, sizeof(int));
		splited_prompt->coords[i][0] = coord_arr[i * 2];
		splited_prompt->coords[i][1] = coord_arr[i * 2 + 1];
	}
	splited_prompt->len = coord_arr_len / 2;
	free(coord_arr);
	return (splited_prompt);
}

/**
 * # ft_delete_words
 *
 * Frees a partial string array in case
 * of an error during token creation.
 *
 * Utility cleanup function.
 */
static void	ft_delete_words(char ***str, int end)
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

/**
 * # ft_split_with_coords
 *
 * Substring splitter based on coordinates.
 *
 * Logic:
 * - For each {start,end} pair, allocates
 *   and copies the slice.
 * - On error, cleans everything with
 *   `ft_delete_words`.
 *
 * Does not interpret quotes; only cuts
 * using the provided indices.
 */
static int	ft_split_with_coords(char const *src,
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
			ft_delete_words(&words, i_words - 1);
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
