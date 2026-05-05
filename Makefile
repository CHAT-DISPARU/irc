NAME :=  ircserv



ESC := \033
RESET := $(ESC)[0m
TEXT_NEON_GREEN := $(ESC)[38;5;46m
TEXT_NEON_RED := $(ESC)[38;5;196m
YELLOW=\033[0;33m
SRCS_DIR = srcs/


SRCS := $(SRCS_DIR)main.cpp \
		$(SRCS_DIR)Server.cpp \
		$(SRCS_DIR)Client.cpp



OBJ := $(SRCS:%.cpp=%.o)


CC := c++

CXXFLAGS := -Wall -Werror -Wextra -std=c++98 -g -I includes

all: ${NAME}


$(NAME): $(LIBFT) ${OBJ}
	@echo "$(TEXT_NEON_GREEN)✅ Compilation of $(NAME) finished !$(RESET)"
	@${CC} -o ${NAME} ${OBJ} ${CXXFLAGS}


%.o: %.cpp
	@$(CC) $(CXXFLAGS) $< -c -o $@

clean:
	@echo "$(YELLOW)🧹 file .o cleaned successfully $(RESET)"
	@rm -f ${OBJ}

fclean: clean
	@echo "$(TEXT_NEON_RED)🧨 $(NAME) deleted$(RESET)"
	@rm -f ${NAME}

re: fclean all

.PHONY: clean fclean re all