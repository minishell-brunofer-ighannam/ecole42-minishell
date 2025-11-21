/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 22:36:19 by valero            #+#    #+#             */
/*   Updated: 2025/11/20 23:29:27 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "splitter_internal.h"

/**
 * # ft_splitter
 *
 * Função de alto nível que unifica todo o fluxo:
 * recebe a string bruta, executa o refinamento completo
 * e retorna o `t_splited_prompt` final.
 *
 * Papel:
 * - Serve como interface simples para o usuário.
 * - Encapsula a lógica interna (`ft_raw_splitter` + refinamento).
 * - Garante que sempre retorna apenas o resultado final já filtrado.
 *
 * Observação:
 * Não realiza nenhuma lógica própria — delega tudo para
 * `ft_refined_splitter`, que coordena o processo completo.
 */
t_splited_prompt	*ft_splitter(char const *str)
{
	t_splited_prompt	*splitted;

	splitted = ft_refined_splitter(str);
	return (splitted);
}
