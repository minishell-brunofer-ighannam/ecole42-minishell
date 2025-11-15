/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expandable_object.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 16:05:39 by valero            #+#    #+#             */
/*   Updated: 2025/11/14 19:07:25 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDABLE_OBJECT_H
# define EXPANDABLE_OBJECT_H

# include <stdbool.h>

typedef struct s_token				t_token;

typedef struct s_expandable_object	t_expandable_object;
struct s_expandable_object
{
	const char			*original_value;
	char				*expanded_value;
	char				*expanded_glob_value;
	bool				has_globs;
	char				**expandable_keys;
	int					**expandable_coord_keys;
	char				**expanded_chuncks;
	void				*(*destroy)(t_expandable_object **self_ref);
};

t_expandable_object	*ft_create_expandable_object(t_token *token);

#endif
