/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 16:01:13 by acuva-nu          #+#    #+#             */
/*   Updated: 2024/01/24 12:43:42 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	err_msg(char *s1, char *s2, char *s3, int ret)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(s1, 2);
	ft_putstr_fd(s2, 2);
	ft_putendl_fd(s3, 2);
	return(ret);
}
void	clean_out(int ret_code, t_ppx *p)
{
	if (p)
	{
		if (p->cmd_path != NULL || p->cmd_opts != NULL)
			free_strs(p->cmd_opts, p->cmd_path);
		if (p->pids != NULL)
			free(p->pids);
		if (p->tube != NULL)
			free(p->tube);
	}
	if (p->hd == 1)
		unlink(".tmpfile");
	exit(ret_code);
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

