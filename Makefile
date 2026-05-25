#================================================
# VARIABLES
#================================================

NAME	:= libasm.a

AR		:= ar
ARFLAGS	:= rcs

AS		:= nasm
ASFLAGS	:= -f elf64

CC		:= cc
CFLAGS	:= -Wall -Wextra -Werror

#================================================
# DIRECTORY
#================================================

INC_DIR		:= incs
SRC_DIR		:= srcs
OBJ_DIR		:= objs
BON_DIR		:= bonus
TEST_DIR	:= test

#================================================
# SOURCES
#================================================

SRCS		:= $(SRC_DIR)/ft_strlen.s \

OBJS		:= $(SRCS:$(SRC_DIR)/%.s=$(OBJ_DIR)/%.o)

TEST_SRC	:= $(TEST_DIR)/main.c
TEST_BIN	:= test_asm

#================================================
# COLORS
#================================================

BLUE	:= \033[0;34m
RED		:= \033[0;31m
RESET	:= \033[0m

#================================================
# RULES
#================================================

all: $(NAME)

# Creates the objs/folder if it does not exist + compiles .s -> o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.s
	@mkdir -p $(OBJ_DIR)
	$(AS) $(ASFLAGS) -o $@ $<

# Creates the static library
$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $(NAME) $(OBJS)
	@echo -e "$(BLUE)$(NAME) created$(RESET)"

test: $(NAME)
	$(CC) $(CFLAGS) -I$(INC_DIR) $(TEST_SRC) -L. -lasm -o $(TEST_BIN)
	@echo -e "$(GREEN)$(TEST_BIN) compiled$(RESET)"
	@echo -e "$(BLUE)Running tests...$(RESET)"
	@./$(TEST_BIN)

clean:
	@rm -rf $(OBJ_DIR)
	@echo -e "$(RED)Objects deleted$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@rm -f $(TEST_BIN)
	@echo -e "$(RED)$(NAME) deleted$(RESET)"

re: fclean all

.PHONY: all clean fclean re