/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 21:31:45 by iouajjou          #+#    #+#             */
/*   Updated: 2024/09/05 22:46:04 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_wspace(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (TRUE);
	return (FALSE);
}

int	is_carac_valid(char c)
{
	if (c == '1')
		return (TRUE);
	if (c == '0')
		return (TRUE);
	if (c == 'N')
		return (TRUE);
	if (c == 'S')
		return (TRUE);
	if (c == 'W')
		return (TRUE);
	if (c == 'E')
		return (TRUE);
	return (FALSE);
}

static int	get_index(char **descriptor)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (descriptor && descriptor[i])
	{
		j = 0;
		while (is_wspace(descriptor[i][j]))
			j++;
		while (is_carac_valid(descriptor[i][j]))
			j++;
		if (descriptor[i][j] == 0)
			break ;
		i++;
	}
	return (i);
}

char	**get_map(char **descriptor)
{
	size_t	i;
	size_t	j;
	char	**map;

	i = get_index(descriptor);
	map = ft_calloc(size_tab(descriptor) - i + 1, sizeof(char *));
	if (!map)
	{
		free_tab(descriptor);
		return (NULL);
	}
	j = 0;
	while (descriptor && descriptor[i])
	{
		map[j] = ft_strdup(descriptor[i]);
		if (!map)
		{
			free_tab(map);
			free_tab(descriptor);
			return (NULL);
		}
		i++;
		j++;
	}
	map[j] = NULL;
	return (map);
}
