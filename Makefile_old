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

BSRCS      = $(shell find ./src/bonus -type f -name *.c)
NAME       = pipex
CC         = cc
CFLAGS     = -g -Wall -Wextra -Werror -fsanitize=address
LIBFT 	   = -Llibft -lft
RM         = rm -f
INCS       = inc/

all: ${NAME}

${NAME}: runlibft norm
	${CC} ${CFLAGS} -o ${NAME} ${BSRCS}  -I ${INCS} ${LIBFT}

ignore: runlibft
	${CC} $C{FLAGS} -o ${NAME} ${BSRCS}  -I ${INCS} ${LIBFT}

clean:
	${RM} ${NAME}

fclean: clean
	make -C libft fclean

re: fclean all

runlibft:
	make -C libft

norm:
	norminette -R CheckForbiddenSourceHeader ${SRCS} ${BSRCS}
	norminette -R CheckDefine ${INCS}

mandatory_path: all
	@./pipex input.txt "/bin/grep give" "wc -l" output.txt

mandatory_normal: all
	@./pipex input.txt "grep give" "wc -l" output.txt

mandatory_wpath: all
	@./pipex input.txt "/bin/gret give" "wc -l" output.txt

mandatory_wnormal: all
	@./pipex input.txt "crep give" "wc -l" output.txt

bonus_mc1: bonus
	@./pipex input.txt "grep give" "grep you" "wc -l" output.txt

bonus_mc2: bonus
	@./pipex input.txt "ls -l" "rep .txt" "grep input" "wc -l" output.txt

bonus_hd: bonus
	@./pipex here_doc EOF "grep azul" "grep bicicleta" "wc -l" output.txt

.PHONY: all re clean fclean bonus