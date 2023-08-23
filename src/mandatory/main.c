/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 16:55:13 by acuva-nu          #+#    #+#             */
/*   Updated: 2023/02/25 18:33:14 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static t_ppx	starter(int ac, char **av, char **envp)
{
	t_ppx	p;

	p.ac = ac;
	p.av = av;
	p.envp = envp;
	p.cmd_nbr = ac - 3;
	p.in = -1;
	p.out = -1;
	p.pid = -1;
	p.cmd_path = NULL;
	p.cmd_opts = NULL;
	return (p);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_ppx	p;
	int		i;

	if (argc != 5)
	{
		ft_putstr_fd("Usage is as follow:\n", 1);
		ft_putstr_fd("./pipex input cmd1 cmd2 outputc\n", 1);
		return (0);
	}
	p = starter(argc, argv, envp);
	entry(&p);
	i = -1;
	while (++i < p.cmd_nbr)
		piper(&p, i);
	return (0);
}
