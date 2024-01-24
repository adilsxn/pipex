/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 12:03:30 by acuva-nu          #+#    #+#             */
/*   Updated: 2024/01/24 12:44:20 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libft/inc/libft.h"
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

char		*cmd_finder(char *cmd, t_ppx *p);
void	clean_out(int ret_code, t_ppx *p);
int	err_msg(char *s1, char *s2, char *s3, int ret);
int	piper(t_ppx *p);
void		heredoc(t_ppx *p);
void		free_strs(char **str1, char *str2);
void		close_fds(int in, int out);
void		get_in(t_ppx *p);
void		get_out(t_ppx *p);
void		close_pipes(t_ppx *p);
#endif // !PIPEX_BONUS_H
