/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okarejok <okarejok@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:56:08 by okarejok          #+#    #+#             */
/*   Updated: 2024/01/26 18:52:18 by okarejok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_parent(t_pipex *pipex)
{
	int	i;

	i = 0;
	close(pipex->infile);
	close(pipex->outfile);
	while (pipex->paths[i])
	{
		free(pipex->paths[i]);
		i++;
	}
	free(pipex->paths);
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
			while (paths[i])
			{
				paths[i] = ft_strjoin(paths[i], "/");
				i++;
			}
			pipex->paths = paths;
			return ;
		}
		envp++;
	}
	error_exit(ERROR_PATH, 1);
}

void	free_child(t_pipex *pipex)
{
	int	j;

	j = 0;
	while (pipex->cmd_args[j])
	{
		free(pipex->cmd_args[j]);
		j++;
	}
	free(pipex->cmd_args);
	j = 0;
	while (pipex->paths[j])
	{
		free(pipex->paths[j]);
		j++;
	}
	free(pipex->cmd);
	free(pipex->paths);

}

void	error_exit(char *error, int errcode)
{
	perror(error);
	exit(errcode);
}
