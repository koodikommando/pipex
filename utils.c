/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okarejok <okarejok@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:56:08 by okarejok          #+#    #+#             */
/*   Updated: 2024/10/15 18:38:24 by okarejok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*ft_join_and_free(char *s1, char *s2)
{
	char	*str;

	if (!s1)
	{
		s1 = ft_calloc(1, 1);
		if (!s1)
			return (NULL);
	}
	str = ft_strjoin(s1, s2);
	free(s1);
	return (str);
}

void	find_paths(t_pipex *pipex, char **envp)
{
	int		i;
	char	**paths;

	i = 0;
	while (*envp)
	{
		if (!ft_strncmp(*envp, "PATH", 4))
		{
			paths = ft_split(*envp + 5, ':');
			if (!paths)
				error_exit(pipex, ERROR_MALLOC, 1);
			while (paths[i])
			{
				paths[i] = ft_join_and_free(paths[i], "/");
				if (!paths[i])
					error_exit(pipex, ERROR_MALLOC, 1);
				i++;
			}
			pipex->paths = paths;
			return ;
		}
		envp++;
	}
	error_exit(pipex, ERROR_PATH, 1);
}

void	free_child(t_pipex *pipex)
{
	int	j;

	j = 0;
	if (pipex->cmd)
		free(pipex->cmd);
	if (pipex->paths)
	{
		while (pipex->paths[j])
		{
			free(pipex->paths[j]);
			j++;
		}
		free(pipex->paths);
	}
	if (pipex->cmd_args)
	{
		j = 0;
		while (pipex->cmd_args[j])
		{
			free(pipex->cmd_args[j]);
			j++;
		}
		free(pipex->cmd_args);
	}
}

void	error_exit(t_pipex *pipex, char *error, int errcode)
{
	error = ft_strjoin("pipex: ", error);
	perror(error);
	free(error);
	if (pipex->pid1 == 0 || pipex->pid2 == 0)
		free_child(pipex);
	exit(errcode);
}
