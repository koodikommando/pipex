/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_processes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okarejok <okarejok@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:55:35 by okarejok          #+#    #+#             */
/*   Updated: 2024/01/30 17:49:04 by okarejok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*get_command(char **paths, char *cmd, t_pipex *pipex)
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
	if (access(pipex->cmd_args[0], 0) == 0)
		return (ft_strdup(pipex->cmd_args[0]));
	return (NULL);
}

static char	**get_command_args(t_pipex *pipex, char *argv)
{
	char	**cmd_args;

	cmd_args = ft_split(argv, ' ');
	if (cmd_args == NULL)
	{
		free_child(pipex);
		error_exit(ERROR_MALLOC, 1);
	}
	if (cmd_args == NULL)
	{
		free_child(pipex);
		error_exit(ERROR_CMD, 1);
	}
	return (cmd_args);
}

void	first_child(t_pipex *pipex, char **argv, char **envp)
{
	pipex->infile = open(argv[1], O_RDONLY);
	if (pipex->infile < 0)
	{
		free_child(pipex);
		error_exit(ERROR_INFILE, 1);
	}
	pipex->cmd_args = get_command_args(pipex, argv[2]);
	pipex->cmd = get_command(pipex->paths, pipex->cmd_args[0], pipex);
	if (!pipex->cmd)
		error_exit(ERROR_CMD, 127);
	if (dup2(pipex->pipe[1], STDOUT_FILENO) < 0)
		error_exit(ERROR_DUP, 1);
	if (dup2(pipex->infile, STDIN_FILENO) < 0)
		error_exit(ERROR_DUP, 1);
	close(pipex->pipe[0]);
	if (execve(pipex->cmd, pipex->cmd_args, envp) == -1)
	{
		free_child(pipex);
		error_exit("Execve failed", 1);
	}
	free_child(pipex);
	error_exit(ERROR_CMD, 127);
	return ;
}

void	second_child(t_pipex *pipex, char **argv, char **envp)
{
	pipex->outfile = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pipex->outfile == -1)
	{
		free_child(pipex);
		error_exit(ERROR_OUTFILE, 1);
	}
	pipex->cmd_args = get_command_args(pipex, argv[3]);
	pipex->cmd = get_command(pipex->paths, pipex->cmd_args[0], pipex);
	if (!pipex->cmd)
		error_exit(ERROR_CMD, 127);
	if (dup2(pipex->pipe[0], STDIN_FILENO) < 0)
		error_exit(ERROR_DUP, 1);
	if (dup2(pipex->outfile, STDOUT_FILENO) < 0)
		error_exit(ERROR_DUP, 1);
	close(pipex->pipe[1]);
	if (execve(pipex->cmd, pipex->cmd_args, envp) == -1)
	{
		free_child(pipex);
		error_exit("Execve failed", 1);
	}
	free_child(pipex);
	error_exit(ERROR_CMD, 127);
	return ;
}
