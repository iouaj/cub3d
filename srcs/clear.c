/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 18:04:53 by iouajjou          #+#    #+#             */
/*   Updated: 2024/09/06 12:24:47 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_textures(t_texture *t, void *mlx_ptr)
{
	size_t	i;

	i = 0;
	while (i < 4)
	{
		if (t[i].img)
		{
			mlx_destroy_image(mlx_ptr, t[i].img);
			t[i].img = NULL;
		}
		if (t[i].path)
		{
			free(t[i].path);
			t[i].path = NULL;
		}
		i++;
	}
}

void	free_data(t_data *d)
{
	free_tab(d->map);
	free_textures(d->textures, d->mlx_ptr);
	if (d->mlx_ptr)
		mlx_destroy_display(d->mlx_ptr);
	if (d->mlx_ptr)
		free(d->mlx_ptr);
	free(d);
}
