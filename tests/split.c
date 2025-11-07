/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 18:13:48 by valero            #+#    #+#             */
/*   Updated: 2025/11/06 23:47:08 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/lexer/tokenizer/tokenizer.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	char	**splitted;
	int		i;

	if (argc < 2)
		splitted = ft_raw_splitter("echo \"hello Bruno \" | grep br");
	else
		splitted = ft_raw_splitter(argv[1]);
	i = -1;
	while (splitted[++i])
		printf("[%s] ", splitted[i]);
	printf("\n");
}
