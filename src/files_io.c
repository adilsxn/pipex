/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_io.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 20:08:47 by acuva-nu          #+#    #+#             */
/*   Updated: 2024/01/24 12:53:30 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	get_in(t_ppx *p)
{
	if (p->hd == 1)
	{
		heredoc(p);
		p->in = open(".tmpfile", O_RDONLY);
		if (p->in == -1)
			clean_out(err_msg("here_doc", ": ", strerror(errno), 1), p);
	}
	else
	{
		p->in = open(p->av[1], O_RDONLY, 0644);
		if (p->in == -1)
			err_msg(strerror(errno), ": ", p->av[1], 1);	
	}
}

void	get_out(t_ppx *p)
{

	if (p->hd == 1)
		p->out = open(p->av[p->ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		p->out = open(p->av[p->ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (p->out == -1)
		err_msg(strerror(errno), ": ", p->av[p->ac - 1], 1);	

}

void	heredoc(t_ppx *p)
{
	int		hd_fd;
	int 	in_fd;
	char	*line;

	hd_fd = open(".tmpfile", O_CREAT | O_WRONLY | O_APPEND, 0644);
	in_fd = dup(STDIN_FILENO);
	if (hd_fd == -1)
		clean_out(err_msg("here_doc", ": ", strerror(errno), 1), p);
	line = "";
	while (1)
	{
		ft_putstr_fd("here_doc> ", 1);
		line = get_next_line(in_fd);
		if (!line)
			break ;
		if (ft_strlen(p->av[2]) + 1 == ft_strlen(line)
			 && !ft_strncmp(p->av[2], line, ft_strlen(p->av[2] + 1)))
				close(in_fd);
		else
			ft_putstr_fd(line, hd_fd);
		free(line);
	}
	close(hd_fd);
}
