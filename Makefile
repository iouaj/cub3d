NAME = cub3d

CC = cc
CFLAGS = -Wall -Wextra -Werror

INCLUDES =

MLX_PATH = mlx_linux
MLX = $(MLX_PATH)/libmlx_linux.a

LIBFT_PATH = srcs/libft
LIBFT = $(LIBFT_PATH)/libft.a

SRC_PATH = srcs
SRC_FILES = main.c \
			checkmap.c \
			init.c \
			clear.c \
			utils.c \
			utils_tab.c \
			map.c \
			render.c \
			raycasting.c \
			gnl/get_next_line.c \
			gnl/get_next_line_utils.c


SRC = $(addprefix $(SRC_PATH)/, $(SRC_FILES))

OBJS_FILES = $(SRC_FILES:.c=.o)
OBJS = $(SRC:.c=.o)

all: $(NAME)
	@echo '$(NAME) create.'

norminette:
	@norminette $(SRC) $(INCLUDES)

%.o: %.c
	@$(CC) -Wall -Wextra -Werror -I/usr/include -Imlx_linux -O3 -c $< -o $@

$(NAME) : $(MLX) $(LIBFT) $(OBJS)
	$(CC) $(OBJS) $(LIBFT) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

$(MLX) :
	@make -C $(MLX_PATH) --no-print-directory

$(LIBFT) :
	@make -C $(LIBFT_PATH) --no-print-directory
	@make bonus -C $(LIBFT_PATH) --no-print-directory

clean:
	@rm -f $(OBJS)
	@make fclean -C $(LIBFT_PATH) --no-print-directory

fclean: clean
	@rm -f $(NAME)
	@make clean -C $(MLX_PATH) --no-print-directory
	@echo 'Full clean.'

re: fclean
	@make all

.PHONY: all clean fclean re norminette
