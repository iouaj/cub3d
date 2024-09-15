/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 15:06:05 by iouajjou          #+#    #+#             */
/*   Updated: 2024/09/15 21:06:06 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	pixel_put_img(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x > WIN_WIDTH || x < 0 || y > WIN_HEIGHT || y < 0)
	{
		printf("Error : Out of windows (%d, %d)\n", x, y);
		exit(EXIT_FAILURE) ;
	}
	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

t_img	*create_img(t_data *d)
{
	t_img	*img;

	img = malloc(sizeof(t_img));
	if (!img)
		return (NULL);
	img->img = mlx_new_image(d->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	if (!img->img)
	{
		free(img);
		return (NULL);
	}
	img->addr = mlx_get_data_addr(img->img, &img->bpp,
			&img->line_length, &img->endian);
	if (!img->addr)
	{
		mlx_destroy_image(d->mlx_ptr, img->img);
		free(img);
		return (NULL);
	}
	return (img);
}

unsigned int	rgb_to_decimal(t_color c)
{
	return (c.rgb.r * pow(256, 2) + c.rgb.g * 256 + c.rgb.b);
}

int	is_in_set(char *set, char c)
{
	size_t	i;

	i = 0;
	while (set && set[i])
	{
		if (c == set[i])
			return (TRUE);
		i++;
	}
	return (FALSE);
}

int	is_wspace(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (TRUE);
	return (FALSE);
}
