SRC				=	main.c #sources here

SRC_DIR			:=	sources/
OBJ_DIR			:=	objects/
SRC				:=	$(addprefix $(SRC_DIR), $(SRC))
OBJ				:=	$(subst $(SRC_DIR), $(OBJ_DIR), $(SRC:.c=.o))
NAME			:=	fdf

# DEBUG			:=	-g 
CC				:=	gcc -Wall -Werror -Wextra $(DEBUG)
INCLUDES		:=	-I includes $(LIBFT_INCLUDE) $(MLX42_INCLUDE)

LIBFT_DIR		:=	libft/
LIBFT_INCLUDE	:=	-I $(LIBFT_DIR)/includes
LIBFT			:=	$(LIBFT_DIR)libft.a
LIBFT_FLAGS		:=	-L $(LIBFT_DIR)

MLX42_DIR		:= MLX42/
MLX42_INCLUDE	:= -I $(MLX42_DIR)include
MLX42			:= $(MLX42_DIR)build/libmlx42.a
MLX42_FLAGS		:= -L $(MLX42_DIR)build/

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ_DIR) $(OBJ)
	$(CC)$(INCLUDES) $(LIBFT_FLAGS) $(MLX42_FLAGS) $(OBJ) -lft -o $@
	@echo "$(CC)$(INCLUDES) -lft -o $(NAME)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(CC)$(INCLUDES) -c $< -o $@
	@echo "$(CC)$< $@"

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	@rm -f $(OBJ)
	@rm -f $(NAME)

re: clean all

libft/Makefile:
	git submodule init
	git submodule update --remote

libft:
	git submodule init
	git submodule update --remote
	@make --no-print-directory -C $(LIBFT_DIR) re

$(LIBFT): libft/Makefile
	@make --no-print-directory -C $(LIBFT_DIR)

clean_libft:
	@make --no-print-directory -C $(LIBFT_DIR) clean

fclean: clean
	@rm -rf $(OBJ_DIR) $(B_OBJ_DIR)
	@make --no-print-directory -C $(LIBFT_DIR) fclean

norm:
	@norminette $(SRC) $(INC_DIR) $(LIBFT_DIR) || true

.PHONY: all clean re bonus fclean norm libft