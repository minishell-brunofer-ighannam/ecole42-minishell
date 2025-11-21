/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raw_splitter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 17:35:20 by valero            #+#    #+#             */
/*   Updated: 2025/11/20 21:45:25 by valero           ###   ########.fr       */
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
 * Função principal de entrada. Varre a string original,
 * detecta limites de palavras (respeitando aspas) e monta
 * a estrutura final `t_splited_prompt`.
 *
 * Lógica:
 * - Aloca vetor de coordenadas.
 * - Identifica posições de início/fim via
 *   `ft_raw_splitter_get_words_position`.
 * - Converte coordenadas em substrings com `ft_run_split`.
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
 * Converte o array de coordenadas em tokens reais.
 *
 * Lógica:
 * - Cria estrutura `t_splited_prompt`.
 * - Aloca array de strings conforme quantidade de pares.
 * - Copia cada trecho usando `coord_arr`.
 * - Constrói o array de coordenadas final.
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
 * Libera um array parcial de strings em caso de erro
 * durante a criação dos tokens.
 *
 * Função utilitária de limpeza.
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
 * Substring splitter baseado em coordenadas.
 *
 * Lógica:
 * - Para cada par {start,end}, aloca e copia o trecho.
 * - Em erro, limpa tudo com `ft_delete_words`.
 *
 * Não interpreta aspas; apenas corta pelos índices fornecidos.
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
