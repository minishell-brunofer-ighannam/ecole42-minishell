/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raw_splitter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 17:35:20 by valero            #+#    #+#             */
/*   Updated: 2025/11/07 02:06:54 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "splitter.h"

static char	**ft_run_split(char const *str, int	*coord_arr, int coord_arr_len);
static void	ft_delete_words(char ***str, int end);
static int	ft_split_with_coords(char const *src,
				int *coord_arr, int coord_arr_len, char **words);

/**
 * # ft_raw_splitter
 *
 * ---
 *
 * Splits a raw command line string into substrings,
 * preserving quoted segments and escaped spaces.
 *
 * Works as the first stage of lexical processing,
 * generating an array of unprocessed words that
 * still include quotes and escape characters.
 *
 * ## Logic
 * - Validates `str` and allocates `coord_arr` sized
 *   to the length of `str`.
 * - Calls `ft_raw_splitter_get_words_position()` to
 *   fill coordinate pairs marking each word's start
 *   and end positions.
 * - Calls `ft_run_split()` to allocate and copy
 *   substrings from `str` using the coordinates.
 * - Frees all memory and returns `NULL` on failure.
 *
 * ## Parameters
 * - `str`: Raw input string to split.
 *
 * ## Returns
 * - Array of strings (`char **`) containing all
 *   extracted words, NULL-terminated.
 * - Returns `NULL` if allocation fails or if
 *   `str` is NULL.
 *
 * ## Notes
 * - Does not perform expansions or syntax parsing.
 * - Quote behavior controlled by
 *   `ft_raw_splitter_update_quote_state()`.
 * - Escaped quotes and spaces are preserved.
 */
char	**ft_raw_splitter(char const *str)
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
 * ---
 *
 * Allocates and builds an array of words using the
 * coordinates provided in `coord_arr`.
 *
 * Each pair of indexes in `coord_arr` defines the start
 * and end of a word within `str`. This function uses
 * `ft_split_with_coords()` to extract each word and
 * return a NULL-terminated array.
 *
 * ## Logic
 * - Allocates memory for `(coord_arr_len / 2) + 1` pointers.
 * - Calls `ft_split_with_coords()` to fill each position.
 * - Frees `coord_arr` after use.
 * - Sets the last element of `words` to `NULL`.
 *
 * ## Parameters
 * - `str`: Original string to split.
 * - `coord_arr`: Array containing start/end indexes.
 * - `coord_arr_len`: Total number of coordinates.
 *
 * ## Returns
 * - `char **`: Array of allocated words.
 * - `NULL`: If allocation or split fails.
 *
 * ## Notes
 * - Frees `coord_arr` internally.
 * - Does not modify `str`.
 * - Returned array must be freed by the caller.
 */
static char	**ft_run_split(char const *str, int	*coord_arr, int coord_arr_len)
{
	char	**words;

	words = (char **)malloc(((coord_arr_len / 2) + 1) * sizeof(char *));
	if (!words)
		return (NULL);
	if (!ft_split_with_coords(str, coord_arr, coord_arr_len, words))
		return (NULL);
	free(coord_arr);
	words[(coord_arr_len / 2)] = (void *)0;
	return (words);
}

/**
 * # ft_delete_words
 *
 * ---
 *
 * Frees all allocated words in a string array up to
 * the given index, and then frees the array itself.
 *
 * Used to clean up partially built arrays in case
 * of allocation errors during splitting.
 *
 * ## Logic
 * - Iterates backward from `end` to 0.
 * - Frees each string and sets its pointer to NULL.
 * - Frees the main array pointer and nullifies it.
 *
 * ## Parameters
 * - `str`: Pointer to the string array to free.
 * - `end`: Last valid index to free.
 *
 * ## Notes
 * - Safely handles partial cleanup after failure.
 * - Sets all freed pointers to NULL to avoid reuse.
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
 * ---
 *
 * Fills an array of strings using the coordinate pairs
 * in `coord_arr` to copy substrings from `src`.
 *
 * Each pair `(start, end)` defines the range of one word.
 * The function allocates and copies each segment, then
 * null-terminates it.
 *
 * ## Logic
 * - Loops over `(coord_arr_len / 2)` pairs.
 * - Allocates each word based on the segment length.
 * - Copies characters from `src[start]` to `src[end]`.
 * - Null-terminates each word.
 * - On allocation failure:
 *   - Calls `ft_delete_words()` to free prior words.
 *   - Returns 0.
 *
 * ## Parameters
 * - `src`: Original string.
 * - `coord_arr`: Array of start/end indexes.
 * - `coord_arr_len`: Total number of coordinates.
 * - `words`: Target array to fill.
 *
 * ## Returns
 * - `1` on success.
 * - `0` on allocation failure.
 *
 * ## Notes
 * - Does not allocate `words` itself.
 * - Keeps consistent order with coordinate pairs.
 * - Ensures each copied word is properly terminated.
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
