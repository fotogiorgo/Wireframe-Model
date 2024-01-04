NAME	:= wireframe

SRC		:=	bonus/fdf_bonus.c \
			bonus/draw_img_bonus.c \
			bonus/rotate_bonus.c \
			bonus/get_map_bonus.c \
			bonus/init_bonus.c \
			bonus/exit_handling_bonus.c

SRCDIR := ./src
OBJ := $(SRC:%.c=%.o)
DEP := $(OBJ:%.o=%.d)

MLX_LIB			:= -lglfw -L ~/.brew/opt/glfw/lib -lm
MLX_NAME		:= ./MLX42/build/libmlx42.a
FT_DIR			:= ./libft
FT_SRC_DIR		:= $(FT_DIR)
LIBFT_NAME		:= $(FT_DIR)/libft.a
LFT_FLAG		:= -L$(FT_DIR)/ -lft
CC				:= cc
SHARED			:= -Wall -Wextra -Werror -Ofast -march=native
INCLUDE_MACOS	:= -I$(FT_SRC_DIR) $(MLX_NAME) $(MLX_LIB)
INCLUDE_LINUX	:= -I$(FT_SRC_DIR) $(MLX_NAME) $(MLX_LIB)
INCLUDE_LIBFT	:= -I./libft/
INCLUDE_MLX		:= -I./MLX42/include/MLX42/
INCLUDE_LOCAL	:= -I./bonus/
HEADERS			:= $(INCLUDE_LIBFT) $(INCLUDE_MLX) $(INCLUDE_LOCAL)
CFLAGS 			:= $(SHARED) $(INCLUDE_MACOS) $(HEADERS)

all: $(NAME)

$(NAME): $(LIBFT_NAME) $(MLX_NAME) $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) $(LFT_FLAG) -o $(NAME)

$(LIBFT_NAME):
	make -C ./libft

$(MLX_NAME):
	cd ./MLX42 && cmake -B build && cmake --build build -j4

-include $(DEP)

$(OBJDIR)/%.o: %.c
	@$(shell [ ! -d $(@D) ] && mkdir -p $(@D))
	$(CC) $(SHARED) $(HEADERS) -MMD -c $< -o $@

clean:
	make clean -C $(FT_DIR)
	/bin/rm -rf $(OBJDIR)

fclean: clean
	make fclean -C $(FT_DIR)
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
