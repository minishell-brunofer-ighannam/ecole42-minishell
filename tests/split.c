/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 18:13:48 by valero            #+#    #+#             */
/*   Updated: 2025/11/06 18:58:29 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/lexer/tokenizer/tokenizer.h"
#include <stdio.h>

int	main(void)
{
	char	**splitted = ft_major_token_split("echo \"hello Bruno \" | grep br");
	int		i = -1;
	while (splitted[++i])
		printf("%s\n", splitted[i]);
}
