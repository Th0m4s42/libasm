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
BON_OBJ_DIR	:= objs_bonus
TEST_DIR	:= test

#================================================
# SOURCES
#================================================

SRCS		:= $(SRC_DIR)/ft_strlen.s \
				$(SRC_DIR)/ft_strcpy.s \
				$(SRC_DIR)/ft_strcmp.s \
				$(SRC_DIR)/ft_write.s \
				$(SRC_DIR)/ft_read.s \
				$(SRC_DIR)/ft_strdup.s

BONUS	:= $(BON_DIR)/ft_atoi_base.s \

OBJS		:= $(SRCS:$(SRC_DIR)/%.s=$(OBJ_DIR)/%.o)

BON_OBJ_DIR	:= $(BONUS:$(BON_DIR)/%.s=$(BON_OBJ_DIR)%.o)

TEST_SRC	:= $(TEST_DIR)/main.c
TEST_SRC_B	:= $(TEST_DIR)/bonus.c
TEST_BIN	:= test_asm
TEST_BIN_B	:= test_asm_bonus

#================================================
# COLORS
#================================================

BLUE	:= \033[0;34m
RED		:= \033[0;31m
RESET	:= \033[0m

#================================================
# RULES
#================================================

mandatory: $(NAME)

bonus: $(NAMEB)

all: mandatory bonus

# Creates the objs/folder if it does not exist + compiles .s -> o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.s
	@mkdir -p $(OBJ_DIR)
	$(AS) $(ASFLAGS) -o $@ $<

# Creates the static library
$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $(NAME) $(OBJS)
	@echo -e "$(BLUE)$(NAME) created$(RESET)"

# Creates the bonus static library
$(NAMEB): $(BON_OBJ_DIR)
	$(AR) $(ARFLAGS) $(NAMEB) $(BON_OBJ_DIR)
	@echo -e "$(BLUE)$(NAMEB) created$(RESET)"

test: $(NAME)
	$(CC) -I$(INC_DIR) $(TEST_SRC) -L. -lasm -o $(TEST_BIN)
	@echo -e "$(GREEN)$(TEST_BIN) compiled$(RESET)"
	@echo -e "$(BLUE)Running tests...$(RESET)"
	@./$(TEST_BIN)

test_b: $(NAMEB)
	$(CC) -I$(INC_DIR) $(TEST_SRC_B) -L. -lasm -o $(TEST_BIN_B)
	@echo -e "$(GREEN)$(TEST_BIN_B) compiled$(RESET)"
	@echo -e "$(BLUE)Running tests...$(RESET)"
	@./$(TEST_BIN_B)

clean:
	@rm -rf $(OBJ_DIR)
	@rm -rf $(BON_OBJ_DIR)
	@echo -e "$(RED)Objects deleted$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@rm -f $(NAMEB)
	@rm -f $(TEST_BIN)
	@rm -f $(TEST_BIN_B)
	@echo -e "$(RED)$(NAME) and $(NAMEB) deleted$(RESET)"

re: fclean all

.PHONY: all bonus clean fclean mandatory re