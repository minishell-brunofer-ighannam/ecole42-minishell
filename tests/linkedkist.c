/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linkedkist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 13:41:35 by valero            #+#    #+#             */
/*   Updated: 2025/11/07 15:19:57 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tests.h"

int	main(void)
{
	t_linkedlist	*list;

	list = ft_new_linkedlist();
	list->push(list, ft_strdup("Bruno"));
	list->push(list, ft_strdup("Fernendes"));
	list->push(list, ft_strdup("Valero"));
	list->push(list, ft_strdup("Nunes"));
	printf("test 1: %s\n", status(!ft_strncmp(list->first->content, "Bruno", 6)));
	printf("test 2: %s\n", status(!ft_strncmp(list->last->content, "Nunes", 6)));
	printf("test 3: %s\n", status(!ft_strncmp(list->first->next->content, "Fernendes", 10)));
	printf("test 4: %s\n", status(!ft_strncmp(list->last->prev->content, "Valero", 7)));
	list->destroy(&list, free);
	printf("test 5: %s\n", status(list == NULL));
}
