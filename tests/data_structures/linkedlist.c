/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linkedlist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 13:41:35 by valero            #+#    #+#             */
/*   Updated: 2025/11/30 21:58:34 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../src/data_structures/data_structures.h"
#include "../tests.h"

int	main(void)
{
	t_linkedlist	*list;

	list = ft_new_linkedlist();
	list->push(list, ft_strdup("Bruno"));
	list->push(list, ft_strdup("Fernendes"));
	list->push(list, ft_strdup("Valero"));
	list->push(list, ft_strdup("Nunes"));
	printf("test 1: %s", status(!ft_strncmp(list->first->content, "Bruno", 6)));
	printf(" %s %s %s\n", PRINT_LIGHT_BLACK, "push 1st element", PRINT_RESET);
	printf("test 2: %s", status(!ft_strncmp(list->last->content, "Nunes", 6)));
	printf(" %s %s %s\n", PRINT_LIGHT_BLACK, "push 2nd element", PRINT_RESET);
	printf("test 3: %s", status(!ft_strncmp(list->first->next->content, "Fernendes", 10)));
	printf(" %s %s %s\n", PRINT_LIGHT_BLACK, "push 3rd element", PRINT_RESET);
	printf("test 4: %s", status(!ft_strncmp(list->last->prev->content, "Valero", 7)));
	printf(" %s %s %s\n", PRINT_LIGHT_BLACK, "push 4th element", PRINT_RESET);
	list->destroy(&list, free);
	printf("test 5: %s", status(list == NULL));
	printf(" %s %s %s\n", PRINT_LIGHT_BLACK, "destroy linkedlist", PRINT_RESET);
}
