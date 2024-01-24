/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 16:01:13 by acuva-nu          #+#    #+#             */
/*   Updated: 2024/01/24 10:28:54 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	err_out(char *s, t_ppx *p)
{
	if (p->cmd_path != NULL)
	{
		free(p->cmd_path);
		p->cmd_path = NULL;
	}
	if (p->cmd_opts != NULL)
		free_strs(p->cmd_opts, NULL);
	if (p->pids != NULL)
		free(p->pids);
	if (p->tube != NULL)
		free(p->tube);
	if (p->hd == 1)
		unlink(".tmpfile");
	perror(s);
	exit(EXIT_FAILURE);
}

void	free_strs(char **str1, char *str2)
{
	int	i;

	i = -1;
	while (str1[++i])
	{
		free(str1[i]);
		str1[i] = NULL;
	}
	free(str1);
	str1 = NULL;
	free(str2);
	str2 = NULL;
}

void	close_pipes(t_ppx *p)
{
	int	iter;

	iter = -1;
	while (p->tube[++iter])
		close(p->tube[iter]);
	free(p->tube);
}

void	close_fds(int in, int out)
{
	close(in);
	close(out);
}

