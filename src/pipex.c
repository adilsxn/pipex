/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 12:13:38 by acuva-nu          #+#    #+#             */
/*   Updated: 2024/01/24 10:32:34 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	redirection(int in, int out, t_ppx *p)
{
	if (dup2(in, STDIN_FILENO) == -1)
		err_out("Output redirection error", p);
	if (dup2(out, STDOUT_FILENO) == -1)
		err_out("Output redirection error", p);
}

static void	parent(t_ppx *p)
{
	close_fds(p->in, p->out);
	p->index--;
	while (p->index >= 0)
	{
		waitpid(p->pids[p->index], NULL, WNOHANG);
		p->index--;
	}
	free(p->pids);
	free(p->tube);
}

static void	child(t_ppx *p)
{
	if (p->index == 0)
		redirection(p->in, p->tube[1], p);
	else if (p->index == p->cmd_nbr - 1)
		redirection(p->tube[2 * p->index - 2], p->out, p);
	else
		redirection(p->tube[2 * p->index - 2], p->tube[2 * p->index + 1], p);
	close_fds(p->in, p->out);
	p->cmd_path = cmd_finder(p);
	if (!p->cmd_path || !p->cmd_opts)
		err_out("Error on command_path", p);
	if (execve(p->cmd_path, p->cmd_opts, p->envp) == -1)
		err_out("Error trying to execute cmd", p);
}

void	piper(t_ppx *p)
{
	if (pipe(p->tube) == -1)
		err_out("Error while creating pipe", p);
	p->index = 0;
	while (p->index < p->cmd_nbr - 1)
	{
		p->pids[p->index] = fork();
		if (p->pids[p->index] == -1)
			err_out("Error on fork", p);
		if (p->pids[p->index] == 0)
		{
			child(p);
			free_strs(p->cmd_opts, p->cmd_path);
		}
		p->index++;
	}
	parent(p);
	if (p->hd == 1)
		unlink(".tmpfile");
}
