/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_glob_ii.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 15:42:31 by ighannam          #+#    #+#             */
/*   Updated: 2025/11/15 15:43:30 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static void	ft_handle_star(int *star, int *match, int *i, int j);
static void	ft_handle_match(int *i, int *j);
static void	ft_handle_not_match(int *i, int star, int *j, int *match);

int	ft_matched_glob(char *after_removal, char *to_match)
{
	int	star;
	int	match;
	int	i;
	int	j;

	i = 0;
	j = 0;
	star = -1;
	match = 0;
	if (to_match[0] == '.' && after_removal[0] != '.')
		return (0);
	while (to_match[j])
	{
		if (after_removal[i] == '*')
			ft_handle_star(&star, &match, &i, j);
		else if (after_removal[i] == to_match[j])
			ft_handle_match(&i, &j);
		else if (star != -1)
			ft_handle_not_match(&i, star, &j, &match);
		else
			return (0);
	}
	while (after_removal[i] == '*')
		i++;
	return (after_removal[i] == '\0');
}

static void	ft_handle_star(int *star, int *match, int *i, int j)
{
	*star = *i;
	*i = *i + 1;
	*match = j;
}

static void	ft_handle_match(int *i, int *j)
{
	*i = *i + 1;
	*j = *j + 1;
}

static void	ft_handle_not_match(int *i, int star, int *j, int *match)
{
	*i = star + 1;
	*match = *match + 1;
	*j = *match;
}