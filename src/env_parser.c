/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 12:37:47 by acuva-nu          #+#    #+#             */
/*   Updated: 2024/01/24 12:40:29 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

char	*cmd_finder(char *cmd, t_ppx *p)
{
	char	**paths;
	char	*path;
	int		i;

	i = -1;
	if (access(cmd, F_OK | X_OK) == 0)
			return (ft_strdup(cmd));
	path = NULL;
	paths = useful_paths(p->envp);
	if (!paths)
		return (NULL);
	while (paths[++i])
	{
		path = ft_strjoin(paths[i], cmd);
		if (!path)
		{
			free_strs(paths, NULL);
			clean_out(err_msg("path error", "", "", 1), p);
		}
		if (access(path, F_OK | X_OK) == 0)
			break; 
	}
	free_strs(paths, NULL);
	return (path);
}
