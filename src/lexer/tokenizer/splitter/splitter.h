/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitter.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 23:38:47 by valero            #+#    #+#             */
/*   Updated: 2025/11/07 02:09:52 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPLITTER_H
# define SPLITTER_H

# include "../../../linkedlist/linkedlist.h"
# include <stdbool.h>

typedef enum e_quote_state		t_quote_state;
enum e_quote_state
{
	NO_QUOTE_OPEN,
	QUOTE_OPEN,
	INSIDE_QUOTE,
	CLOSED_QUOTE,
};

typedef struct s_quote_info		t_quote_info;
struct s_quote_info
{
	t_quote_state	state;
	int				open_quote_type;
};

typedef struct s_int_array		t_int_array;
struct s_int_array
{
	int	len;
	int	*array;
};

typedef struct s_granilar_split	t_granilar_split;
struct s_granilar_split
{
	int	size;

};

bool	ft_is_quote(const char *str, int idx);
void	ft_raw_splitter_get_words_position(
			const char *str, t_int_array *array);
char	**ft_raw_splitter(char const *str);

#endif
