#================================================
# VARIABLES
#================================================

NAME	:= libasm.a

AR		:= ar
ARFLAGS	:= rcs

AS		:= nasm
ASFLAGS	:= -f elf64

#================================================
# DIRECTORY
#================================================

SRC_DIR	:= srcs/
OBJ_DIR	:= objs/
BON_DIR	:= bonus/

#================================================
# SOURCES
#================================================

SRCS	:= $(SRC_DIR)/ft_strlen.s /

OBJS	:= $(SRCS:$(SRC_DIR)/%.s=$(OBJ_DIR)/%.o)

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
	@echo "$(BLUE)$(NAME) created$(RESET)"

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)Objects deleted$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)$(NAME) deleted$(RESET)"

re: fclean all

.PHONY: all clean fclean re