/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 18:53:40 by brunofer          #+#    #+#             */
/*   Updated: 2025/08/21 12:12:37 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

# include <stdlib.h>

typedef struct s_list_node
{
	void				*content;
	struct s_list_node	*next;
	struct s_list_node	*prev;
}	t_list_node;

typedef struct s_list
{
	int			length;
	t_list_node	*head;
	t_list_node	*tail;
}	t_list;

#endif
