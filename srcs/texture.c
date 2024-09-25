/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 15:17:03 by iouajjou          #+#    #+#             */
/*   Updated: 2024/09/25 13:28:03 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// void	set_texture(char **descriptor, char *key, void *mlx_ptr, t_texture *t)
// {
// 	char		*line;

// 	line = ft_search_keyword_line(descriptor, key);
// 	if (!line)
// 		return ;
// 	t->path = get_path(line, key);
// 	if (!t->path)
// 		return ;
// 	t->img = mlx_xpm_file_to_image(mlx_ptr, t->path, &t->width, &t->height);
// 	if (!t->img)
// 		return ;
// 	t->addr = mlx_get_data_addr(t->img, &t->bpp, &t->line_length, &t->endian);
// }

// void	get_all_texture(t_data *d)
// {
// 	set_texture(d->descriptor, "NO", d->mlx_ptr, &d->textures[NO]);
// 	set_texture(d->descriptor, "SO", d->mlx_ptr, &d->textures[SO]);
// 	set_texture(d->descriptor, "EA", d->mlx_ptr, &d->textures[EA]);
// 	set_texture(d->descriptor, "WE", d->mlx_ptr, &d->textures[WE]);
// 	d->textures[NO].id = NO;
// 	d->textures[SO].id = SO;
// 	d->textures[WE].id = WE;
// 	d->textures[EA].id = EA;
// }

int	check_textures(t_texture *t, t_data *d)
{
	size_t	i;

	i = 0;
	while (i < 4)
	{
		if (!t[i].path || !t[i].img || !t[i].addr)
		{
			ft_putstr_fd("Error : Invalid path or invalid img\n", 2);
			d->map = NULL;
			free_data(d);
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}
