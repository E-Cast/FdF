SRC				=	main.c \
					map.c

SRC_DIR			:=	sources/
OBJ_DIR			:=	objects/
SRC				:=	$(addprefix $(SRC_DIR), $(SRC))
OBJ				:=	$(subst $(SRC_DIR), $(OBJ_DIR), $(SRC:.c=.o))
NAME			:=	fdf

LIBFT_DIR		:=	libft/
LIBFT_INCLUDE	:=	-I $(LIBFT_DIR)includes
LIBFT			:=	$(LIBFT_DIR)libft.a
LIBFT_FLAGS		:=	-L $(LIBFT_DIR) -lft

MLX42_DIR		:= MLX42/
MLX42_INCLUDE	:= -I $(MLX42_DIR)include
MLX42			:= $(MLX42_DIR)build/libmlx42.a
MLX42_FLAGS		:= -ldl -lglfw -pthread -lm

DEBUG			:=	-g
OPTIMIZE		:=	-Ofast
CC				:=	gcc -Wall -Werror -Wextra -Wunreachable-code $(DEBUG) $(OPTIMIZE)
INCLUDES		:=	-I includes $(LIBFT_INCLUDE) $(MLX42_INCLUDE)

all: $(NAME)

$(NAME): $(LIBFT) $(MLX42) $(OBJ_DIR) $(OBJ)
	@$(CC)$(OBJ) $(MLX42) $(INCLUDES) $(LIBFT_FLAGS) $(MLX42_FLAGS) -o $@
	@echo "$(CC) $(INCLUDES) $(LIBFT_FLAGS) $(MLX42_FLAGS) -o $(NAME)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(CC) $(INCLUDES) -c $< -o $@
	@echo "$(CC)$< $@"

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	@rm -f $(OBJ)
	@rm -f $(NAME)

re: clean all

libft/Makefile:
	git submodule init libft/
	git submodule update --remote libft/

$(LIBFT): libft/Makefile
	@make -C $(LIBFT_DIR)

libft:
	git submodule init libft/
	git submodule update --remote libft/
	@make -C $(LIBFT_DIR) re

MLX42/build/:
	git submodule init MLX42/
	git submodule update --remote MLX42/

$(MLX42): MLX42/build/
	@cmake $(MLX42_DIR) -B $(MLX42_DIR)build
	@make -C $(MLX42_DIR)/build -j4

mlx42:
	git submodule init MLX42/
	git submodule update --remote MLX42/
	rm -rf $(MLX42_DIR)build
	@cmake $(MLX42_DIR) -B $(MLX42_DIR)build
	@make -C $(MLX42_DIR)/build -j4

clean_libft:
	@make --no-print-directory -C $(LIBFT_DIR) clean

fclean: clean
	@rm -rf $(OBJ_DIR) $(B_OBJ_DIR)
	@make --no-print-directory -C $(LIBFT_DIR) fclean

norm:
	@norminette $(SRC) $(INC_DIR) $(LIBFT_DIR) || true

.PHONY: all clean re bonus fclean norm libft