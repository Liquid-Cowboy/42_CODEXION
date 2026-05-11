# === colors ===
GREEN       := \033[0;32m
BLUE        := \033[0;34m
RED         := \033[0;31m
RESET       := \033[0m

# === executable ===
NAME		:= codexion

# === compilation ===
CFLAGS		:=-Wall -Wextra -Werror -pthread -Iincludes
CC			:=cc

# === files ===
SRC_DIR		:= srcs
SRCS		:= $(shell find $(SRC_DIR) -name "*.c")
OBJ_DIR		:=objs
OBJS		:= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

ARGS		:= 12 10000 100 100 100 3 100 edf


all: $(NAME)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@echo "$(GREEN)Compiling program...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	@echo "$(RED)Cleaning binaries...$(RESET)"
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "$(RED)Cleaning executable...$(RESET)"
	@rm -rf $(NAME)

def: $(NAME)
	@echo "$(GREEN)Starting program with default arguments...$(RESET)"
	./$(NAME) $(ARGS)

re: clean all

.PHONY: all clean fclean re def