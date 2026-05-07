NAME :=  ircserv



ESC := \033
RESET := $(ESC)[0m
TEXT_NEON_GREEN := $(ESC)[38;5;46m
TEXT_NEON_RED := $(ESC)[38;5;196m
YELLOW=\033[0;33m
SRCS_DIR = srcs/
CMD_DIR = commands/
RED=\033[0;31m
BLUE=\033[0;34m
PURPLE=\033[0;35m
BUILD_DIR := build/


SRCS := $(SRCS_DIR)main.cpp \
		$(SRCS_DIR)Server.cpp \
		$(SRCS_DIR)Client.cpp \
		$(SRCS_DIR)$(CMD_DIR)CommandParser.cpp \
		$(SRCS_DIR)$(CMD_DIR)PassCommand.cpp \
		$(SRCS_DIR)$(CMD_DIR)NickCommand.cpp \
		$(SRCS_DIR)$(CMD_DIR)UserCommand.cpp \
		$(SRCS_DIR)$(CMD_DIR)PingCommand.cpp \
		$(SRCS_DIR)$(CMD_DIR)QuitCommand.cpp \
		$(SRCS_DIR)$(CMD_DIR)PongCommand.cpp \
		$(SRCS_DIR)$(CMD_DIR)PrivmsgCommand.cpp



OBJ := $(patsubst $(SRCS_DIR)%.cpp, $(BUILD_DIR)%.o, $(SRCS))


CC := c++

CXXFLAGS := -Wall -Werror -Wextra -std=c++98 -g -I includes -I includes/commands

all: banner ${NAME}

banner :
	@echo "		$(BLUE) █████ ███████████     █████████ $(RESET)"
	@echo "		$(BLUE)$(PURPLE)░$(BLUE)$(PURPLE)░$(BLUE)███ $(PURPLE)░$(BLUE)$(PURPLE)░$(BLUE)███$(PURPLE)░$(BLUE)$(PURPLE)░$(BLUE)$(PURPLE)░$(BLUE)$(PURPLE)░$(BLUE)$(PURPLE)░$(BLUE)███   ███$(PURPLE)░$(BLUE)$(PURPLE)░$(BLUE)$(PURPLE)░$(BLUE)$(PURPLE)░$(BLUE)$(PURPLE)░$(BLUE)███$(RESET)"
	@echo "		$(BLUE) $(PURPLE)░$(BLUE)███  $(PURPLE)░$(BLUE)███    $(PURPLE)░$(BLUE)███  ███     $(PURPLE)░$(BLUE)$(PURPLE)░$(BLUE)$(PURPLE)░$(BLUE) $(RESET)"
	@echo "		$(BLUE) $(PURPLE)░$(BLUE)███  $(PURPLE)░$(BLUE)██████████  $(PURPLE)░$(BLUE)███         $(RESET)"
	@echo "		$(BLUE) $(PURPLE)░$(BLUE)███  $(PURPLE)░$(BLUE)███$(PURPLE)░$(BLUE)$(PURPLE)░$(BLUE)$(PURPLE)░$(BLUE)$(PURPLE)░$(BLUE)$(PURPLE)░$(BLUE)███ $(PURPLE)░$(BLUE)███         $(RESET)"
	@echo "		$(BLUE) $(PURPLE)░$(BLUE)███  $(PURPLE)░$(BLUE)███    $(PURPLE)░$(BLUE)███ $(PURPLE)░$(BLUE)$(PURPLE)░$(BLUE)███     ███$(RESET)"
	@echo "		$(BLUE) █████ █████   █████ $(PURPLE)░$(BLUE)$(PURPLE)░$(BLUE)█████████ $(RESET)"
	@echo "		$(BLUE)$(PURPLE)░$(BLUE)$(PURPLE)░$(BLUE)$(PURPLE)░$(BLUE)$(PURPLE)░$(BLUE)$(PURPLE)░$(BLUE) $(PURPLE)░$(BLUE)$(PURPLE)░$(BLUE)$(PURPLE)░$(BLUE)$(PURPLE)░$(BLUE)$(PURPLE)░$(BLUE)   $(PURPLE)░$(BLUE)$(PURPLE)░$(BLUE)$(PURPLE)░$(BLUE)$(PURPLE)░$(BLUE)$(PURPLE)░$(BLUE)   $(PURPLE)░$(BLUE)$(PURPLE)░$(BLUE)$(PURPLE)░$(BLUE)$(PURPLE)░$(BLUE)$(PURPLE)░$(BLUE)$(PURPLE)░$(BLUE)$(PURPLE)░$(BLUE)$(PURPLE)░$(BLUE)$(PURPLE)░$(BLUE)  $(RESET)"
                                 
                                 
                                 


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