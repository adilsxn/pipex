/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 20:08:47 by acuva-nu          #+#    #+#             */
/*   Updated: 2023/03/01 20:28:18 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	get_in(t_ppx *p)
{
	int	in;

	if (p->hd == 1)
	{
		heredoc(p->av);
		in = open(".tmpfile", O_RDONLY);
		if (in == -1)
			err_out("Error while opening hd_tmpfile", p);
	}
	else
	{
		in = open(p->av[1], O_RDONLY);
		if (in == -1)
			err_out("Error while opening infile", p);
	}
	return (in);
}

int	get_out(t_ppx *p)
{
	int	out;

	if (p->hd == 1)
		out = open(p->av[p->ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		out = open(p->av[p->ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (out == -1)
		err_out("Error while opening outfile", p);
	return (out);
}

void	heredoc(char **argv)
{
	int		hd_fd;
	char	*line;
	char	*tmp;
	char	*delim;

	hd_fd = open(".tmpfile", O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (hd_fd == -1)
	{
		perror("Error while trying to open .tmpfile");
		return ;
	}
	tmp = ft_strdup(argv[2]);
	delim = ft_strjoin(tmp, "\n");
	while (1)
	{
		ft_putstr_fd(">", 1);
		line = get_next_line(0);
		if (ft_strlen(line) == ft_strlen(delim))
			if (!ft_strncmp(delim, line, ft_strlen(delim)))
				break ;
		ft_putstr_fd(line, hd_fd);
		free(line);
	}
	free_3strs(tmp, delim, line);
	close(hd_fd);
}
