/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 12:37:47 by acuva-nu          #+#    #+#             */
/*   Updated: 2023/03/01 21:19:21 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static char	*get_path(char **envp)
{
	char	*path;
	int		i;

	i = 0;
	path = NULL;
	while (envp[i] && !ft_strnstr(envp[i], "PATH=", 5))
		i++;
	path = ft_substr(envp[i], 5, ft_strlen(envp[i]));
	return (path);
}

static char	**useful_paths(char **envp)
{
	char	**paths;
	char	*path;
	char	*tmp;
	int		i;

	i = -1;
	path = get_path(envp);
	paths = ft_split(path, ':');
	if (!paths)
	{
		free_strs(paths, path);
	}
	while (paths[++i])
	{
		tmp = paths[i];
		paths[i] = ft_strjoin(paths[i], "/");
		free(tmp);
	}
	free(path);
	return (paths);
}

char	*cmd_finder(t_ppx *p)
{
	char	**paths;
	char	*path;
	int		i;

	paths = useful_paths(p->envp);
	p->cmd_opts = ft_split(p->av[p->index + 2 + p->hd], ' ');
	if (!p->cmd_opts)
		err_out("Error on cmd_opts", p);
	i = -1;
	while (paths[++i])
	{
		path = ft_strjoin(paths[i], p->cmd_opts[0]);
		if (!path)
			return (NULL);
		if (access(path, F_OK | X_OK) == 0)
			return (ft_strdup(path));
		free(path);
	}
	free_strs(paths, NULL);
	return (NULL);
}
