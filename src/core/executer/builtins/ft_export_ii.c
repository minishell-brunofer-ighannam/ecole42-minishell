/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_ii.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 23:16:12 by ighannam          #+#    #+#             */
/*   Updated: 2025/12/09 23:16:58 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ft_free_content_ht(t_ht *content)
{
	free(content->key);
	free(((t_env_value *)(content->value))->value);
	free(content->value);
	free(content);
}
