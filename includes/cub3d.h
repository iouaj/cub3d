#ifndef CUB3D_H
# define CUB3D_H

# include "get_next_line.h"
# include "../srcs/libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>

# define TRUE 0
# define FALSE 1

# define WALL 1
# define SPACE 0

enum TEXT
{
	NO,
	SO,
	WE,
	EA
};

typedef struct s_texture
{
	char	*path;
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
	t_list		*map;
}	t_data;

t_data	*init_data(char **descriptor);

size_t	size_tab(char **tab);
void	free_tab(char **tab);
#endif
