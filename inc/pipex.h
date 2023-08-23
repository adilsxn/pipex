/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 13:01:34 by acuva-nu          #+#    #+#             */
/*   Updated: 2023/03/01 21:07:00 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

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
	int		child;
	int		*tube;
	int		in;
	int		out;
	int		cmd_nbr;
	char	**cmd_opts;
	char	*cmd_path;
}			t_ppx;

char		*cmd_finder(int iter, t_ppx *p);
void		entry(t_ppx *p);
void		err_out(char *s, t_ppx *p);
void		piper(t_ppx *p, int iter);
void		heredoc(char **argv);
void		free_strs(char **str1, char *str2);
#endif // !PIPEX_H
