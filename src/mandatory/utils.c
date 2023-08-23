/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 16:01:13 by acuva-nu          #+#    #+#             */
/*   Updated: 2023/02/25 18:33:29 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	err_out(char *s, t_ppx *p)
{
	if (p->cmd_path != NULL)
	{
		free(p->cmd_path);
		p->cmd_path = NULL;
	}
	if (p->cmd_opts != NULL)
		free_strs(p->cmd_opts, NULL);
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
