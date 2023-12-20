# SETUP
NAME		=	minishell
LIBFT		=	$(LFT_PATH)libft.a

CFLAGS		=	-Wall -Wextra -Werror -g
RM			=	rm -rf
LIB_CF		=	-L $(LFT_PATH) -lft
READLINE_CF	=	-lreadline -lhistory


INCLUDES	=	-I$(HEADER_DIR) -I$(LFT_PATH)

# FILES AND PATH
LFT_PATH 	=	libft/

HEADER_FILE	=	minishell.h struct.h lexer.h
HEADER_DIR	=	include/
HEADER		=	$(addprefix $(HEADER_DIR), $(HEADER_FILE))

LEXER		=	lexer_list.c lexer_tokenizer.c lexer_utils.c lexer.c
PASER


SRC_DIR		=	src/
SRC			=	$(addprefix $(SRC_DIR), $(LEXER) $(PASER) $(MAIN) $(EXECUTOR) $(BUILTIN))

OBJ_DIR		=	obj/
OBJ			=	$(addprefix $(OBJ_DIR),$(SRC_FILES:%.c=%.o))


# RULES
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
		@mkdir -p $(OBJ_DIR)
		cc $(CFLAGS) $(INCLUDES) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ) $(MLX) $(LIBFT)
		@echo "\n$(YELLOW)Generating FdF executable...$(DEFAULT)\n"
		cc $(OBJ) $(LIB_CF) $(MLX_CF) -o $(NAME)
		@echo "\n$(GREEN)FdF created!$(DEFAULT)\n"

$(MLX): $(MLX_DIR)
		@echo "\n$(YELLOW)Generating MLX42 ...$(DEFAULT)\n"
		@cmake $(MLX_DIR) -B $(MLX_PATH)
		@make -C $(MLX_PATH) -j4
		@echo "\n$(GREEN)MLX42 created$(DEFAULT)\n"

$(LIBFT): $(LFT_PATH)
		@echo "\n$(YELLOW)Generating Libft...$(DEFAULT)\n"
		@make -C $(LFT_PATH)
		@echo "\n$(GREEN)Libft created!$(DEFAULT)\n"

clean: 
		@make clean -C $(LFT_PATH)
		@echo "\n$(RED)Libft objects removed!$(DEFAULT)\n\n"
		@$(RM) $(OBJ_DIR)
		@echo "\n$(RED)FdF objects removed!$(DEFAULT)\n\n"

fclean: clean
		@make fclean -C $(LFT_PATH)
		@$(RM) $(MLX_PATH)
		@echo "\n$(RED)All libraries removed!$(DEFAULT)\n\n"
		@$(RM) $(NAME)
		@echo "\n$(RED)FdF removed!$(DEFAULT)\n\n"

re: fclean all

.PHONY: all clean fclean re bonus

# COLORS
RED		=	\033[1;31m
GREEN	=	\033[1;32m
YELLOW	=	\033[1;33m
DEFAULT	=	\033[0m