/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 12:13:38 by acuva-nu          #+#    #+#             */
/*   Updated: 2023/02/25 18:33:27 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	entry(t_ppx *p)
{
	p->in = open(p->av[1], O_RDONLY);
	if (p->in == -1)
		err_out("Error while opening infile", p);
	dup2(p->in, STDIN_FILENO);
	p->out = open(p->av[p->ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (p->out == -1)
		err_out("Error while opening outfile", p);
}

void	piper(t_ppx *p, int iter)
{
	if (pipe(p->tube) == -1)
		err_out("Error while creating pipe", p);
	p->pid = fork();
	if (p->pid == -1)
		err_out("Error on fork", p);
	if (p->pid == 0)
	{
		close(p->tube[0]);
		if (iter == p->cmd_nbr - 1)
			dup2(p->out, STDOUT_FILENO);
		else
			dup2(p->tube[1], STDOUT_FILENO);
		p->cmd_path = cmd_finder(iter, p);
		if (!p->cmd_path || execve(p->cmd_path, p->cmd_opts, p->envp) == -1)
			err_out("Error trying to execute cmd", p);
		free_strs(NULL, p->cmd_path);
	}
	else
	{
		close(p->tube[1]);
		wait(NULL);
		dup2(p->tube[0], STDIN_FILENO);
	}
}
