/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 14:58:31 by valero            #+#    #+#             */
/*   Updated: 2025/11/24 20:33:01 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer_internal.h"

/**
*  # ft_coord_dup
*
* Duplica uma coordenada [start, end].
*
* Lógica:
* - Aloca novo vetor de 2 inteiros.
* - Copia start e end do original.
*
* Papel:
* Fornece coordenadas independentes quando múltiplas estruturas
* precisam referenciar os mesmos limites da string.
*/
int	*ft_coord_dup(int *coord)
{
	int	*new_coord;

	new_coord = malloc(2 * sizeof(int));
	new_coord[0] = coord[0];
	new_coord[1] = coord[1];
	return (new_coord);
}

/**
*  # ft_new_coord
*
* Cria uma nova coordenada [start, end].
*
* Lógica:
* - Aloca vetor de 2 inteiros.
* - Atribui valores baseados nos argumentos recebidos.
*
* Papel:
* Utilitário simples para registrar regiões da string original,
* usado tanto pelo splitter quanto pelo tokenizer.
*/
int	*ft_new_coord(int start, int end)
{
	int	*new_coord;

	new_coord = malloc(2 * sizeof(int));
	new_coord[0] = start;
	new_coord[1] = end;
	return (new_coord);
}
