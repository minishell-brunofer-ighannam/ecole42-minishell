/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 23:14:30 by valero            #+#    #+#             */
/*   Updated: 2025/11/11 14:45:03 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	// printf("quotes: %d\n", verify_quotes("teste \"quotes closed\" \"haha\" \" "));
	// printf("parenthesis: %d\n", verify_parenthesis("teste (\"quotes closed)\" \"haha\" \" "));
	printf("promp1: %d\n", verify_prompt("teste (\"quotes closed)\" \"haha\" \" "));
	printf("promp2: %d\n", verify_prompt("teste (\"quotes closed)\") \"haha\" \" "));
}
