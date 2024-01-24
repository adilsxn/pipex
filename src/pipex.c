/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 12:13:38 by acuva-nu          #+#    #+#             */
/*   Updated: 2024/01/24 12:24:31 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	redirection(int in, int out, t_ppx *p)
{
	if (dup2(in, STDIN_FILENO) == -1)
		err_out("Output redirection error", p);
	if (dup2(out, STDOUT_FILENO) == -1)
		err_out("Output redirection error", p);
}

static int	parent(t_ppx *p)
{
	pid_t	pid;
	int status;
	int ret_code;

	
	close_fds(p->in, p->out);
	p->index--;
	ret_code = 1;
	while (p->index >= 0)
	{
		pid = waitpid(p->pids[p->index], &status, WNOHANG);
		if (pid == p->pids[p->cmd_nbr - 1])
			if (p->index == p->cmd_nbr - 1 && WIFEXITED(status))
				ret_code = WEXITSTATUS(status);
		p->index--;
	}
	free(p->pids);
	free(p->tube);
	return (ret_code);
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
	p->cmd_opts = ft_split(p->av[p->index + 2 + p->hd], ' ');
	p->cmd_path = cmd_finder(p->cmd_opts[0], p);
	if (!p->cmd_path || !p->cmd_opts)
		err_out("command not found", p);
	if (execve(p->cmd_path, p->cmd_opts, p->envp) == -1)
		err_out(p->cmd_opts[0], p);
}

int	piper(t_ppx *p)
{
	int ret_code;

	if (pipe(p->tube) == -1)
		err_out("Pipex: ", p);
	p->index = 0;
	while (p->index < p->cmd_nbr - 1)
	{
		p->pids[p->index] = fork();
		if (p->pids[p->index] == -1)
			err_out("Error on fork: ", p);
		if (p->pids[p->index] == 0)
			child(p);
		free_strs(p->cmd_opts, p->cmd_path);
		p->index++;
	}
	ret_code = parent(p);
	if (p->hd == 1)
		unlink(".tmpfile");
	return (ret_code);
}
