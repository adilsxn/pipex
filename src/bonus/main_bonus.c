/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 16:55:13 by acuva-nu          #+#    #+#             */
/*   Updated: 2023/03/01 21:43:09 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	pipe_creator(t_ppx *p)
{
	int	iter;

	iter = 0;
	while (iter < p->cmd_nbr - 1)
	{
		if (pipe(p->tube + 2 * iter) == -1)
			err_out("Error creating pipes", p);
		iter++;
	}
}

static t_ppx	starter(int ac, char **av, char **envp)
{
	t_ppx	p;

	p.ac = ac;
	p.av = av;
	p.envp = envp;
	if (!ft_strncmp(av[1], "here_doc", 8))
		p.hd = 1;
	else
		p.hd = 0;
	p.cmd_nbr = ac - 3 - p.hd;
	p.in = get_in(&p);
	p.out = get_out(&p);
	p.pids = malloc(sizeof(p.pids) * p.cmd_nbr);
	if (!p.pids)
		err_out("Error allocating space for pids", &p);
	p.tube = malloc(sizeof(p.tube) * 2 * (p.cmd_nbr - 1));
	if (!p.tube)
		err_out("Error allocating space for pipe", &p);
	pipe_creator(&p);
	p.cmd_path = NULL;
	p.cmd_opts = NULL;
	return (p);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_ppx	p;

	if (argc < 5)
	{
		ft_putstr_fd("./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2\n", 1);
		ft_putstr_fd(" ./pipex here_doc LIMITER cmd cmd1 file\n", 1);
		return (0);
	}
	p = starter(argc, argv, envp);
	piper(&p);
	return (0);
}
