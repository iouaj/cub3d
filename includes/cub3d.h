/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 17:21:54 by iouajjou          #+#    #+#             */
/*   Updated: 2024/09/17 18:06:59 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "get_next_line.h"
# include "../srcs/libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include <math.h>
# include <../mlx_linux/mlx.h>

# define TRUE 0
# define FALSE 1

# define VERTICAL 1
# define HORIZONTAL 0

# define WALL '1'
# define SPACE '0'

# define ESC 65307
# define LEFT_CAM 65361
# define RIGHT_CAM 65363

//QWERTY
# define FRONT 119
# define BACK 115
# define RIGHT 100
# define LEFT 97

// //AZERTY
// # define FRONT 122
// # define BACK 115
// # define RIGHT 100
// # define LEFT 113

// # define CELLSIZE 64

# define WIN_HEIGHT 1080
# define WIN_WIDTH 1920

# define BLUE 0x0000FF
# define GREEN 0x00FF00

# define ROT_SPEED 0.1
# define MOVE_SPEED 0.15

// # define TEXTURE_HEIGHT 64
// # define TEXTURE_WIDTH 64

enum e_TEXT
{
	NO,
	SO,
	WE,
	EA
};

typedef struct s_ray_val
{
	int		hitside;
	int		step_x;
	int		step_y;
	int		map_x;
	int		map_y;
	int		draw_start;
	int		draw_end;
	int		line_height;
	double	per_wall_dist;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	raydir_x;
	double	raydir_y;
}	t_ray;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_texture
{
	int		id;
	char	*path;
	void	*img;
	int		width;
	int		height;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
	int		text_x;
	int		text_y;
}	t_texture;

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

typedef struct s_color
{
	char	*id;
	t_rgb	rgb;
}	t_color;

typedef struct s_data
{
	t_texture	textures[4];
	t_color		floor;
	t_color		ceiling;
	char		**map;
	char		**descriptor;
	void		*mlx_ptr;
	void		*win_ptr;
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	t_img		*img;
	size_t		action;
}	t_data;

void			loop(t_data *data);

//movement
void			front_move(t_data *d);
void			back_move(t_data *d);
void			right_move(t_data *d);
void			left_move(t_data *d);
double			get_margin(double dir);
//rotation
void			rotate_right(t_data *d);
void			rotate_left(t_data *d);

void			pixel_put_img(t_img *img, int x, int y, int color);
t_img			*create_img(t_data *d);

unsigned int	rgb_to_decimal(t_color c);

t_data			*init_data(char **descriptor);
char			**get_map(char **descriptor);
char			*ft_search_keyword_line(char **descriptor, char *keyword);
char			*get_path(char *line, char *key);
void			get_colors(t_data *d);
void			get_all_texture(t_data *d);
int				check_color(t_color c, t_data *d);
int				check_textures(t_texture *t, t_data *d);

int				is_map_valid(char **map, t_data *d);
int				check_border(int x, int y, char **map);

//utils tab
char			**ft_deep_copy_tab(char **tab);
size_t			size_tab(char **tab);
void			free_tab(char **tab);

//raycasting
void			raycasting(t_data *d, int x, t_img *img);
t_ray			create_ray(int x, t_data *d);

void			draw_line(int x, t_img *img, t_data *d, t_ray *ray);

int				is_wspace(char c);
int				is_in_set(char *set, char c);

void			free_textures(t_texture *t, void *mlx_ptr);
void			free_data(t_data *d);
void			free_img(t_img *img, void *mlx_ptr);
void			*error_init(char *err, t_data *d);
#endif
