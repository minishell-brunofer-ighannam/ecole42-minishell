/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raw_splitter_internal.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 20:07:48 by valero            #+#    #+#             */
/*   Updated: 2025/11/20 21:43:55 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAW_SPLITTER_INTERNAL_H
# define RAW_SPLITTER_INTERNAL_H

# include "../splitter_internal.h"
# include <stdbool.h>
# include <stdlib.h>

/**
 * # t_quote_state
 *
 * Estado interno do parser de aspas.
 * Representa transições entre abertura, conteúdo e
 * fechamento de aspas, usado para decidir quando
 * iniciar/terminar tokens.
 */
typedef enum e_quote_state							t_quote_state;
enum e_quote_state
{
	NO_QUOTE_OPEN,
	QUOTE_OPEN,
	INSIDE_QUOTE,
	CLOSED_QUOTE,
};

/**
 * # t_quote_info
 *
 * Conjunto de informações sobre o estado atual das aspas.
 * - `state`: estado da FSM.
 * - `open_quote_type`: tipo de aspas atualmente abertas.
 *
 * Controla toda a lógica de delimitação de palavras dentro/fora de aspas.
 */
typedef struct s_quote_info							t_quote_info;
struct s_quote_info
{
	t_quote_state	state;
	int				open_quote_type;
};

/**
 * # t_int_array
 *
 * Estrutura auxiliar para armazenar dinamicamente os índices
 * de início e fim de cada palavra detectada.
 *
 * Usada durante a varredura inicial da string.
 */
typedef struct s_int_array							t_int_array;
struct s_int_array
{
	int	len;
	int	*array;
};

void				ft_raw_splitter_update_quote_state(
						t_quote_info *quote_info, char quote, bool is_word_end);
bool				ft_is_start_quote_after_multiple_closing(
						const char *str, int i, t_quote_state state);
bool				ft_has_entered_quote(
						const char *str, int i, t_quote_state state);
bool				ft_is_start_consecutive_quote(
						const char *str, int i, t_quote_info quote_info);
bool				ft_is_start_or_end_quote(
						const char *str, int i, t_quote_info quote_info);
void				ft_raw_splitter_get_words_position(
						const char *str, t_int_array *array);

#endif
