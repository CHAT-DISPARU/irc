NAME :=  ircbot

ESC := \033
RESET := $(ESC)[0m
TEXT_NEON_GREEN := $(ESC)[38;5;46m
TEXT_NEON_RED := $(ESC)[38;5;196m
YELLOW=\033[0;33m
SRCS_DIR = srcs/
RED=\033[0;31m
BLUE=\033[0;34m
PURPLE=\033[0;35m
BUILD_DIR := build/

SRCS := $(SRCS_DIR)main.cpp \
		$(SRCS_DIR)Bot.cpp



OBJ := $(patsubst $(SRCS_DIR)%.cpp, $(BUILD_DIR)%.o, $(SRCS))


CC := c++

CXXFLAGS := -Wall -Werror -Wextra -std=c++98 -g -I includes

all: ${NAME}


$(NAME): $(LIBFT) ${OBJ}
	@echo "$(TEXT_NEON_GREEN)✅ Compilation of $(NAME) finished !$(RESET)"
	@${CC} -o ${NAME} ${OBJ} ${CXXFLAGS}


${BUILD_DIR}%.o: ${SRCS_DIR}%.cpp
	@mkdir -p $(dir $@)
	@${CC} ${CXXFLAGS} -c $< -o $@

clean:
	@echo "$(YELLOW)🧹 file .o cleaned successfully $(RESET)"
	@rm -rf ${BUILD_DIR}

fclean: clean
	@echo "$(TEXT_NEON_RED)🧨 $(NAME) deleted$(RESET)"
	@rm -f ${NAME}

re: fclean all

.PHONY: clean fclean re all