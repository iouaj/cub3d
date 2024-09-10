/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 21:54:15 by iouajjou          #+#    #+#             */
/*   Updated: 2024/09/10 18:40:47 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

double	get_direction_x(t_data *data, double angle)
{
	double	rayDirecX;
	double	dirX;
	double	dirY;
	double	cameraX;
	double	planeX;

	cameraX = 2 * ((data->pos_x + 1) / WIN_HEIGHT) - 1;
	dirX = cos(angle);
	dirY = sin(angle);
	planeX = -dirY * 0.66;
	rayDirecX = dirX + planeX * cameraX;
	return (rayDirecX);
}

double	get_direction_y(t_data *data, double angle)
{
	double	rayDirectY;
	double	dirX;
	double	dirY;
	double	cameraX;
	double	planeY;

	cameraX = 2 * ((data->pos_x + 1) / WIN_HEIGHT) - 1;
	dirX = cos(angle);
	dirY = sin(angle);
	planeY = dirX * 0.66;
	rayDirectY = dirY + planeY * cameraX;
	return (rayDirectY);
}

//x variable if vertical wall
//y variable if horizontal wall
double	get_distance(int map, double pos, double step, double rayDir)
{
	return ((map - pos + (1 - step) / 2) / rayDir);
}

int	get_wall_height(double distance)
{
	return (WIN_HEIGHT / distance);
}

// void	render_img(int x, int y, double distance, t_data *d)
// {
// 	int	wallHeight;
// 	int	drawStart;
// 	int	drawEnd;

// 	wallHeight = get_wall_height(distance);

// 	drawStart = -wallHeight / 2 + WIN_HEIGHT / 2;

// 	(void) drawStart;
// 	(void) drawEnd;

// 	render_background(&img, d);
// }

void	find_wall(double posX, double posY, double rayDirX, double rayDirY, char **map)
{
	double	deltaDistX;
	double	deltaDistY;
	int		stepX;
	int		stepY;
	double	sideDistX;
	double	sideDistY;
	int		mapX;
	int		mapY;
	int		hitside;

	deltaDistX = sqrt(1 + pow(rayDirY / rayDirX, 2));
	deltaDistY = sqrt(1 + pow(rayDirX / rayDirY, 2));
	// deltaDistX = fabs(1 / rayDirX);
	// deltaDistY = fabs(1 / rayDirY);
	printf("DeltaDistX %f\n", deltaDistX);
	printf("DeltaDistY %f\n", deltaDistY);
	mapX = posX;
	mapY = posY;

	if (rayDirX > 0)
		stepX = 1;
	else
		stepX = -1;
	if (rayDirY > 0)
		stepY = 1;
	else
		stepY = -1;

	if (stepX == 1)
		sideDistX = (mapX + 1.0 - posX) * deltaDistX;
	else
		sideDistX = (posX - mapX) * deltaDistX;

	if (stepY == 1)
		sideDistY = (mapY + 1.0 - posY) * deltaDistX;
	else
		sideDistY = (posY - mapY) * deltaDistX;

	// printf("sideDistX %f\n", sideDistX);
	// printf("sideDistY %f\n", sideDistY);

	while (map[mapY][mapX] != WALL)
	{
		printf("looking %d %d\n", mapX, mapY);
		printf("case : %c\n", map[mapY][mapX]);

		if (sideDistX < sideDistY)
		{
			mapX += stepX;
			sideDistX += deltaDistX;
			hitside = VERTICAL;
		}
		else
		{
			mapY += stepY;
			sideDistY += deltaDistY;
			hitside = HORIZONTAL;
		}
		printf("next look %d %d\n", mapX, mapY);
		printf("case : %c\n", map[mapY][mapX]);
	}
	printf("Il y a un mur en (%d, %d)\n", mapX, mapY);
	(void) hitside;
	return ;

}

void	check_horizontal(t_data *d, int angle)
{
	double	rayDirecX;
	double	rayDirecY;

	printf("angle %d\n", angle);
	rayDirecX = get_direction_x(d, angle);
	printf("rayDirecX %f\n", rayDirecX);
	rayDirecY = get_direction_y(d, angle);
	printf("rayDirecY %f\n", rayDirecY);
	find_wall(d->pos_x, d->pos_y, rayDirecX, rayDirecY, d->map);
	printf("--------------------------\n");
}
