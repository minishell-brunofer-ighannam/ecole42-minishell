/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 07:02:52 by brunofer          #+#    #+#             */
/*   Updated: 2025/08/18 19:44:07 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libstr.h"

static int		is_valid_char(char c, char const *set);
static int		*fill_coords(char const *s1, char const *set, int *coords);
static int		is_valid_coords(int *coords);

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	char	*str;
	int		coords[2];

	if (!s1 || !set)
		return (NULL);
	if (!is_valid_coords(fill_coords(s1, set, coords)))
		return (ft_strdup(""));
	str = malloc(coords[1] - coords[0] + 2);
	if (!str)
		return (NULL);
	i = 0;
	while (coords[0] <= coords[1])
		str[i++] = s1[coords[0]++];
	str[i] = '\0';
	return (str);
}

static int	*fill_coords(char const *s1, char const *set, int *coords)
{
	int	i;

	coords[0] = -1;
	coords[1] = -1;
	i = -1;
	while (s1[++i])
	{
		if (!i && is_valid_char(s1[i], set))
			coords[0] = i;
		if (!is_valid_char(s1[i - 1], set) && is_valid_char(s1[i], set))
			coords[0] = i;
		if (coords[0] >= 0)
			break ;
	}
	i = ft_strlen(s1);
	while (s1[--i])
	{
		if (is_valid_char(s1[i], set) && !s1[i + 1])
			coords[1] = i;
		if (is_valid_char(s1[i], set) && !is_valid_char(s1[i + 1], set))
			coords[1] = i;
		if (coords[1] >= 0)
			break ;
	}
	return (coords);
}

static int	is_valid_char(char c, char const *set)
{
	int	i;

	i = -1;
	while (set[++i])
		if (set[i] == c)
			return (0);
	return (1);
}

static int	is_valid_coords(int *coords)
{
	if (coords[0] < 0 || coords[1] < 0)
		return (0);
	return (1);
}
