/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_processes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okarejok <okarejok@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:55:35 by okarejok          #+#    #+#             */
/*   Updated: 2024/01/26 19:57:52 by okarejok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*get_command(char **paths, char *cmd)
{
	int		i;
	char	*aux;
	char	*command;

	i = 0;
	while (paths[i])
	{
		aux = ft_strjoin(paths[i], "/");
		command = ft_strjoin(aux, cmd);
		if (access(command, 0) == 0)
		{
			free(aux);
			aux = NULL;
			return (command);
		}
		free(command);
		i++;
	}
	return (NULL);
}

void	first_child(t_pipex *pipex, char **argv, char **envp)
{
	pipex->cmd_args = ft_split(argv[2], ' ');
	if (pipex->cmd_args == NULL)
	{
		free_child(pipex);
		error_exit(ERROR_MALLOC, 1);
	}
	if (pipex->cmd_args[0] == NULL)
	{
		free_child(pipex);
		error_exit(ERROR_CMD, 1);
	}
	pipex->cmd = get_command(pipex->paths, pipex->cmd_args[0]);
	if (!pipex->cmd)
		error_exit(ERROR_CMD, 127);
	if (dup2(pipex->pipe[1], STDOUT_FILENO) < 0)
		error_exit(ERROR_DUP, 1);
	if (dup2(pipex->infile, STDIN_FILENO) < 0)
		error_exit(ERROR_DUP, 1);
	close(pipex->pipe[0]);
	execve(pipex->cmd, pipex->cmd_args, envp);
	free_child(pipex);
	error_exit(ERROR_CMD, 127);
	return ;
}

void	second_child(t_pipex *pipex, char **argv, char **envp)
{
	pipex->cmd_args = ft_split(argv[3], ' ');
	if (pipex->cmd_args == NULL)
	{
		free_child(pipex);
		error_exit(ERROR_MALLOC, 1);
	}
	if (pipex->cmd_args[0] == NULL)
	{
		free_child(pipex);
		error_exit(ERROR_CMD, 1);
	}
	pipex->cmd = get_command(pipex->paths, pipex->cmd_args[0]);
	if (!pipex->cmd)
		error_exit(ERROR_CMD, 127);
	if (dup2(pipex->pipe[0], STDIN_FILENO) < 0)
		error_exit(ERROR_DUP, 1);
	if (dup2(pipex->outfile, STDOUT_FILENO) < 0)
		error_exit(ERROR_DUP, 1);
	close(pipex->pipe[1]);
	execve(pipex->cmd, pipex->cmd_args, envp);
	free_child(pipex);
	error_exit(ERROR_CMD, 127);
	return ;
}