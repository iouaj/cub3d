/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkmap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:51:26 by iouajjou          #+#    #+#             */
/*   Updated: 2024/09/10 17:16:18 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	valid_value(char c)
{
	if (c == WALL)
		return (TRUE);
	if (c == SPACE)
		return (TRUE);
	if (c == 'A')
		return (TRUE);
	return (FALSE);
}

int	case_valid(int x, int y, char **map)
{
	if (x + 1 >= (int)ft_strlen(map[y]) || valid_value(map[y][x + 1]) == FALSE)
		return (FALSE);
	if (x - 1 < 0 || valid_value(map[y][x - 1]) == FALSE)
		return (FALSE);
	if (y + 1 >= (int)size_tab(map) || x >= (int)ft_strlen(map[y + 1]) || valid_value(map[y + 1][x]) == FALSE)
		return (FALSE);
	if (y - 1 < 0 || x >= (int)ft_strlen(map[y - 1]) || valid_value(map[y - 1][x]) == FALSE)
		return (FALSE);
	return (TRUE);
}

int	check_border(int x, int y, char **map)
{
	if (x < 0 || y < 0 || y > (int)size_tab(map) || x > (int)ft_strlen(map[y]) || !map[y][x])
		return (FALSE);
	if (map[y][x] == SPACE || map[y][x] == 'N' || map[y][x] == 'W' || map[y][x] == 'S' || map[y][x] == 'E')
	{
		if (case_valid(x, y, map) == FALSE)
			return (FALSE);
		else
		{
			map[y][x] = 'A';
			return (check_border(x - 1, y, map) + check_border(x + 1, y, map) + check_border(x, y - 1, map) + check_border(x, y + 1, map));
		}
	}
	return (TRUE);
}

int	check_start_position(char **map, t_data *d)
{
	size_t	i;
	size_t	j;
	int		trigger;

	i = 0;
	trigger = 0;
	while (map && map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (is_in_set("NSEW", map[i][j]) == TRUE)
			{
				trigger++;
				d->pos_x = j;
				d->pos_y = i;
			}
			j++;
		}
		i++;
	}
	if (trigger == 1)
		return (TRUE);
	return (FALSE);
}

static int	check_carac(char **map, char *set)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (map && map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (is_in_set(set, map[i][j]) == FALSE)
				return (FALSE);
			j++;
		}
		i++;
	}
	return (TRUE);
}

int	is_map_valid(char **map, t_data *d)
{
	char	**copy;

	if (size_tab(map) < 3)
		return (FALSE);
	if (check_carac(map, "10NSEW ") == FALSE)
		return (FALSE);
	if (check_start_position(map, d) == FALSE)
		return (FALSE);
	copy = ft_deep_copy_tab(map);
	if (!copy)
		return (FALSE);
	if (check_border(d->pos_x, d->pos_y, copy) == FALSE)
	{
		free_tab(copy);
		return (FALSE);
	}
	free_tab(copy);
	return (TRUE);
}
