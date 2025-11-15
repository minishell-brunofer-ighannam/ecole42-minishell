/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_glob_test.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 10:55:34 by ighannam          #+#    #+#             */
/*   Updated: 2025/11/15 12:42:37 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void ft_print_array_char(char **list);

int main(void)
{
	char **expanded;

	printf("\n===== Teste * =====\n");
	expanded = ft_expand_glob("*");
	ft_print_array_char(expanded);
	ft_clean_array_str(expanded);
	printf("\n\n");

	printf("\n===== Teste .* =====\n");
	expanded = ft_expand_glob(".*");
	ft_print_array_char(expanded);
	ft_clean_array_str(expanded);
	printf("\n\n");


	printf("\n===== Teste *e =====\n");
	expanded = ft_expand_glob("*e");
	ft_print_array_char(expanded);
	ft_clean_array_str(expanded);
	printf("\n\n");


	printf("\n===== Teste *e* =====\n");
	expanded = ft_expand_glob("*e*");
	ft_print_array_char(expanded);
	ft_clean_array_str(expanded);
	printf("\n\n");
	

	printf("\n===== Teste *e*_*s* =====\n");
	expanded = ft_expand_glob("*e*_*s*");
	ft_print_array_char(expanded);
	ft_clean_array_str(expanded);
	printf("\n\n");


	printf("\n===== Teste *eeee* =====\n");
	expanded = ft_expand_glob("*eeee*");
	ft_print_array_char(expanded);
	ft_clean_array_str(expanded);
	printf("\n\n");

	
	return (0);
}

static void ft_print_array_char(char **list)
{
	if (!list)
		return;
	int i = 0;
	while (list[i])
	{
		printf("%s  ", list[i]);
		i++;
	}	
}