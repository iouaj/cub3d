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

# define CELLSIZE 64

# define WIN_HEIGHT 1080
# define WIN_WIDTH 1920

enum TEXT
{
	NO,
	SO,
	WE,
	EA
};

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_texture
{
	char	*path;
	void	*img;
	int		width;
	int		height;
	char	*id;
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

typedef struct s_data {
	t_texture	textures[4];
	t_color		floor;
	t_color		ceiling;
	char		**map;
	char		**descriptor;
	void		*mlx_ptr;
	void		*win_ptr;
	int			pos_x;
	int			pos_y;
	t_img		*img;
}	t_data;

void	loop(t_data *data);

void	pixel_put_img(t_img *img, int x, int y, int color);
t_img	create_img(t_data *d);

unsigned int	rgb_to_decimal(t_color c);

t_data	*init_data(char **descriptor);
char	**get_map(char **descriptor);

int	is_map_valid(char **map, t_data *d);

//utils tab
char	**ft_deep_copy_tab(char **tab);
size_t	size_tab(char **tab);
void	free_tab(char **tab);

//raycasting
void	check_horizontal(t_data *d, int angle);

double	absolute(double nb);

int	is_wspace(char c);
int	is_in_set(char *set, char c);

void	free_textures(t_texture *t, void *mlx_ptr);
void	free_data(t_data *d);
#endif
