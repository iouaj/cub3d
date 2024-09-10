/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 15:06:05 by iouajjou          #+#    #+#             */
/*   Updated: 2024/09/10 18:53:12 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	pixel_put_img(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

t_img	create_img(t_data *d)
{
	t_img	img;

	img.img = mlx_new_image(d->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	if (!img.img)
	{
		img.addr = NULL;
		return (img);
	}
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	if (!img.addr)
	{
		mlx_destroy_image(d->mlx_ptr, img.img);
		img.img = NULL;
	}
	return (img);
}

unsigned int	rgb_to_decimal(t_color c)
{
	return (c.rgb.r * pow(256, 2) + c.rgb.g * 256 + c.rgb.b);
}

double	absolute(double nb)
{
	if (nb >= 0)
		return (0);
	return (-nb);
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
