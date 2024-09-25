/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:52:38 by iouajjou          #+#    #+#             */
/*   Updated: 2024/09/25 14:32:18 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	set_texture(char *line_descr, char *key, void *mlx_ptr, t_texture *t)
{
	char	*line;

	if (t->path || t->img || t->addr)
	{
		ft_putstr_fd("Error : double textures\n", STDERR_FILENO);
		return (-1);
	}
	line = ft_strdup(line_descr);
	if (!line)
		return (ft_putstr_fd("Error : alloc fail\n", 2), -1);
	t->path = get_path(line, key);
	if (!t->path)
		return (ft_putstr_fd("Error : alloc fail\n", 2), -1);
	t->img = mlx_xpm_file_to_image(mlx_ptr, t->path, &t->width, &t->height);
	if (!t->img)
		return (ft_putstr_fd("Error : alloc fail\n", 2), -1);
	t->addr = mlx_get_data_addr(t->img, &t->bpp, &t->line_length, &t->endian);
	return (1);
}

int	check_color_already_set(t_color c)
{
	if (c.id != NULL)
		return (TRUE);
	if (c.rgb.r != -1)
		return (TRUE);
	if (c.rgb.g != -1)
		return (TRUE);
	if (c.rgb.b != -1)
		return (TRUE);
	return (FALSE);
}

int	texture(t_data *d, char *line, int count)
{
	if (!ft_strncmp(line, "NO ", 3))
	{
		if (set_texture(line, "NO", d->mlx_ptr, &d->textures[NO]) == -1)
			return (free_data(d), -1);
		return (d->textures[NO].id = NO, ++count);
	}
	else if (!ft_strncmp(line, "SO ", 3))
	{
		if (set_texture(line, "SO", d->mlx_ptr, &d->textures[SO]) == -1)
			return (free_data(d), -1);
		return (d->textures[SO].id = SO, ++count);
	}
	else if (!ft_strncmp(line, "EA ", 3))
	{
		if (set_texture(line, "EA", d->mlx_ptr, &d->textures[EA]) == -1)
			return (free_data(d), -1);
		return (d->textures[EA].id = EA, ++count);
	}
	else if (!ft_strncmp(line, "WE ", 3))
	{
		if (set_texture(line, "WE", d->mlx_ptr, &d->textures[WE]) == -1)
			return (free_data(d), -1);
		return (d->textures[WE].id = WE, ++count);
	}
	return (count);
}

int	color(t_data *d, char *line, int count)
{
	if (!ft_strncmp(line, "F ", 2))
	{
		if (check_color_already_set(d->floor) == TRUE)
			return (free_data(d), -1);
		d->floor = set_color(line, "F");
		return (++count);
	}
	else if (!ft_strncmp(line, "C ", 2))
	{
		if (check_color_already_set(d->ceiling) == TRUE)
			return (free_data(d), -1);
		d->ceiling = set_color(line, "C");
		return (++count);
	}
	return (count);
}

int	parse_descriptor(t_data *d)
{
	int		count;
	size_t	i;
	size_t	j;

	count = 0;
	i = 0;
	while (count != 6 && d->descriptor[i])
	{
		j = 0;
		while (d->descriptor[i][j] && is_wspace(d->descriptor[i][j]) == TRUE)
			j++;
		count = texture(d, d->descriptor[i] + j, count);
		if (count == -1)
			return (-1);
		count = color(d, d->descriptor[i] + j, count);
		if (count == -1)
			return (-1);
		i++;
	}
	return (i);
}
