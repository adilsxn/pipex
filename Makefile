# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acuva-nu <acuva-nu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/29 12:35:24 by acuva-nu          #+#    #+#              #
#    Updated: 2023/02/25 16:34:52 by acuva-nu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRCS       = src/mandatory/utils.c src/mandatory/parser.c src/mandatory/pipex.c
			 src/mandatory/main.c
B_SRC      = src/bonus/utils_bonus.c src/bonus/parser_bonus.c src/bonus/pipex_bonus.c
			 src/bonus/main_bonus
OBJS       = ${SRCS:src/%.c=$(OBJ_DIR)/%.o}
B_OBJS     = ${B_SRC:src/%.c=$(B_OBJ_DIR)/%.o}
BUILD_DIR  = build
OBJ_DIR    = ${BUILD_DIR}/obj
B_OBJ_DIR  = ${BUILD_DIR}/b_obj
INCS 	   = inc/
NAME       = ${BUILD_DIR}/c_project
B_NAME     = ${BUILD_DIR}/b_c_project
CC         = cc
CFLAGS     = -g -Wall -Wextra -Werror
LDFLAGS 	 = -L./libft -lft
RM         = rm -rf

all: ${NAME}

$(OBJ_DIR)/%.o: src/%.c | $(BUILD_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INCS) ${LDFLAGS}

${NAME}: ${OBJS} | $(BUILD_DIR)
	@echo "Compiling c_project"
	@make -s -C libft
	@${CC} ${CFLAGS}  $^ -o $@  -I ${INCS} ${LDFLAGS}
	@echo "c_project created"

$(B_OBJ_DIR)/%.o: src/%.c | $(BUILD_DIR)
	@$(CC) $(CFLAGS) -I $(INCS) -c $< -o $@

bonus: ${B_NAME}

${B_NAME}: ${B_OBJS} | $(BUILD_DIR)
	@echo "Compiling b_c_project"
	@make -s -C libft
	@${CC} ${CFLAGS}  $^ -o ${B_NAME} -I ${INCS} ${LDFLAGS}
	@echo "b_c_project created"

${BUILD_DIR}:
	@mkdir -p ${BUILD_DIR}
	@mkdir -p ${OBJ_DIR} ${B_OBJ_DIR}

clean:
	@${RM} ${OBJS} ${B_OBJS}
	@make clean -s -C libft

fclean: clean
	@${RM} ${BUILD_DIR}
	@make fclean -s -C libft
	@echo "c_project deleted"

re: fclean all

norm:
	norminette -R CheckForbiddenSourceHeader ${SRCS}
	norminette -R CheckDefine ${INCS}

.PHONY: all re clean fclean bonus
