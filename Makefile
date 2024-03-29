# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acuva-nu <acuva-nu@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/29 12:35:24 by acuva-nu          #+#    #+#              #
#    Updated: 2024/01/24 10:47:00 by acuva-nu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRCS       = src/pipex.c src/files_io.c src/utils.c src/env_parser.c src/main.c

OBJS       = ${SRCS:src/%.c=$(OBJ_DIR)/%.o}
BUILD_DIR  = build
OBJ_DIR    = ${BUILD_DIR}/obj
INCS 	   = inc/
NAME       = ${BUILD_DIR}/pipex
CC         = cc
CFLAGS     = -g -Wall -Wextra -Werror -g -fsanitize=address
LDFLAGS 	 = -L./libft -lft
RM         = rm -rf

all: ${NAME}

$(OBJ_DIR)/%.o: src/%.c | $(BUILD_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INCS) ${LDFLAGS}

${NAME}: ${OBJS} | $(BUILD_DIR)
	@echo "Compiling Pipex"
	@make -s -C libft
	@${CC} ${CFLAGS}  $^ -o $@  -I ${INCS} ${LDFLAGS}
	@echo "Pipex created"

bonus: all

${BUILD_DIR}:
	@mkdir -p ${BUILD_DIR}
	@mkdir -p ${OBJ_DIR} ${B_OBJ_DIR}

clean:
	@${RM} ${OBJS} ${B_OBJS}
	@make clean -s -C libft

fclean: clean
	@${RM} ${BUILD_DIR}
	@make fclean -s -C libft
	@echo "Pipex deleted"

re: fclean all

norm:
	norminette -R CheckForbiddenSourceHeader ${SRCS}
	norminette -R CheckDefine ${INCS}

.PHONY: all re clean fclean bonus
