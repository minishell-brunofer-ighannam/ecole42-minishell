/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raw_splitter_quote_states.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 20:46:14 by brunofer          #+#    #+#             */
/*   Updated: 2025/11/20 21:58:41 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raw_splitter_internal.h"

/**
 * # ft_raw_splitter_update_quote_state
 *
 * Atualiza o estado da máquina de aspas,
 * decidindo se estamos abrindo, entrando,
 * fechando ou saindo de aspas.
 *
 * Lógica:
 * - Possui dois fluxos: quando é fim de palavra
 *   e quando é apenas um caractere normal.
 * - Controla o valor `open_quote_type`.
 */
void	ft_raw_splitter_update_quote_state(
				t_quote_info *quote_info, char quote, bool is_word_end)
{
	if (is_word_end)
	{
		if (quote_info->state == NO_QUOTE_OPEN)
			quote_info->state = QUOTE_OPEN;
		else if (quote_info->state == QUOTE_OPEN)
			quote_info->state = INSIDE_QUOTE;
		else if (quote_info->state == INSIDE_QUOTE)
			quote_info->state = CLOSED_QUOTE;
		else
			quote_info->state = NO_QUOTE_OPEN;
		if (quote_info->state == QUOTE_OPEN)
			quote_info->open_quote_type = quote;
		return ;
	}
	if (quote_info->state == NO_QUOTE_OPEN)
		quote_info->state = QUOTE_OPEN;
	else if (quote_info->state == QUOTE_OPEN)
		quote_info->state = INSIDE_QUOTE;
	else if (quote_info->state == INSIDE_QUOTE)
		quote_info->state = CLOSED_QUOTE;
	else
		quote_info->state = INSIDE_QUOTE;
	if (quote_info->state == QUOTE_OPEN)
		quote_info->open_quote_type = quote;
}

/**
 * # ft_is_start_quote_after_multiple_closing
 *
 * Detecta caso específico onde uma nova aspa
 * inicia imediatamente após múltiplos fechamentos,
 * envolvendo backticks.
 *
 * ---
 *
 * ## Exemplo:
 * `...end""""""""new start"`
 */
bool	ft_is_start_quote_after_multiple_closing(
			const char *str, int i, t_quote_state state)
{
	return (ft_is_quote(str, i, "`") && !ft_is_quote(str, i + 1, "`")
		&& ft_is_quote(str, i - 1, "`") && state == CLOSED_QUOTE);
}

/**
 * # ft_has_entered_quote
 *
 * Determina se o parser acabou de entrar
 * no conteúdo interno de uma aspa.
 *
 * ---
 *
 * ## Exemplo:
 * `..."entered a quote...`
 */
bool	ft_has_entered_quote(const char *str, int i, t_quote_state state)
{
	return (!ft_is_quote(str, i, "`") && state == QUOTE_OPEN);
}

/**
 * # ft_is_start_consecutive_quote
 *
 * Detecta aspas consecutivas (ex: `''''''`)
 * que mudam o tipo de aspa aberta.
 *
 * Útil para padrões não convencionais de backticks.
 *
 * ---
 *
 * ## Exemplo:
 *
 * `...starting consecutive quotes""""""...`
 */
bool	ft_is_start_consecutive_quote(
			const char *str, int i, t_quote_info quote_info)
{
	return (quote_info.state == INSIDE_QUOTE && ft_is_quote(str, i, "`")
		&& ft_is_quote(str, i + 1, "`")
		&& str[i + 1] != quote_info.open_quote_type);
}

/**
 * # ft_is_start_or_end_quote
 *
 * Verifica se a posição atual marca início
 * ou término de um bloco entre aspas,
 * levando em conta o tipo de aspa aberto.
 *
 * ---
 *
 * ## Exemplo:
 *
 * `...before"start or end of quotes"after...`
 */
bool	ft_is_start_or_end_quote(
			const char *str, int i, t_quote_info quote_info)
{
	return (ft_is_quote(str, i, "`") && !ft_is_quote(str, i + 1, "`")
		&& !ft_is_quote(str, i - 1, "`") && (!quote_info.open_quote_type
			|| quote_info.open_quote_type == str[i]));
}
