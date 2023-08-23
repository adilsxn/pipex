/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 12:03:30 by acuva-nu          #+#    #+#             */
/*   Updated: 2023/03/01 21:16:29 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "get_next_line.h"
# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_ppx
{
	char	**envp;
	char	**av;
	int		ac;
	int		hd;
	int		*pids;
	int		index;
	int		*tube;
	int		in;
	int		out;
	int		cmd_nbr;
	char	**cmd_opts;
	char	*cmd_path;
}			t_ppx;

char		*cmd_finder(t_ppx *p);
void		err_out(char *s, t_ppx *p);
void		piper(t_ppx *p);
void		heredoc(char **argv);
void		free_strs(char **str1, char *str2);
void		close_fds(int in, int out);
int			get_in(t_ppx *p);
int			get_out(t_ppx *p);
void		close_pipes(t_ppx *p);
void		free_3strs(char *str1, char *str2, char *str3);
#endif // !PIPEX_BONUS_H
