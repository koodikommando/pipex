/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_processes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okarejok <okarejok@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:55:35 by okarejok          #+#    #+#             */
/*   Updated: 2024/02/10 13:47:46 by okarejok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*get_command(t_pipex *pipex, char **paths, char *cmd)
{
	int		i;
	char	*aux;
	char	*command;

	i = 0;
	while (paths[i])
	{
		aux = paths[i];
		command = ft_strjoin(aux, cmd);
		if (!command)
			error_exit(pipex, ERROR_MALLOC, 1);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		i++;
	}
	return (NULL);
}

static void	get_command_args(t_pipex *pipex, char *argv)
{
	pipex->cmd_args = pipex_split(argv, ' ');
	if (pipex->cmd_args == NULL)
		error_exit(pipex, ERROR_MALLOC, 1);
	if (pipex->cmd_args[0] == NULL)
		error_exit(pipex, ERROR_CMD, 127);
}

void	first_child(t_pipex *pipex, char **argv, char **envp)
{
	pipex->infile = open(argv[1], O_RDONLY);
	if (pipex->infile < 0)
		error_exit(pipex, ERROR_INFILE, 1);
	dup2(pipex->pipe[1], STDOUT_FILENO);
	close(pipex->pipe[1]);
	dup2(pipex->infile, STDIN_FILENO);
	close(pipex->infile);
	close(pipex->pipe[0]);
	get_command_args(pipex, argv[2]);
	if (ft_strchr(pipex->cmd_args[0], '/') || pipex->cmd_args[0][0] == '.')
	{
		if (access(pipex->cmd_args[0], X_OK) == -1)
			error_exit(pipex, ERROR_PATH, 127);
		execve(pipex->cmd_args[0], pipex->cmd_args, envp);
	}
	else
	{
		find_paths(pipex, envp);
		pipex->cmd = get_command(pipex, pipex->paths, pipex->cmd_args[0]);
		if (!pipex->cmd)
			error_exit(pipex, ERROR_CMD, 127);
		execve(pipex->cmd, pipex->cmd_args, envp);
	}
	error_exit(pipex, ERROR_CMD, 127);
}

void	second_child(t_pipex *pipex, char **argv, char **envp)
{
	pipex->outfile = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pipex->outfile == -1)
		error_exit(pipex, ERROR_OUTFILE, 1);
	dup2(pipex->pipe[0], STDIN_FILENO);
	close(pipex->pipe[0]);
	dup2(pipex->outfile, STDOUT_FILENO);
	close(pipex->outfile);
	close(pipex->pipe[1]);
	get_command_args(pipex, argv[3]);
	if (ft_strchr(pipex->cmd_args[0], '/') || pipex->cmd_args[0][0] == '.')
	{
		if (access(pipex->cmd_args[0], X_OK) == -1)
			error_exit(pipex, ERROR_PATH, 127);
		execve(pipex->cmd_args[0], pipex->cmd_args, envp);
	}
	else
	{
		find_paths(pipex, envp);
		pipex->cmd = get_command(pipex, pipex->paths, pipex->cmd_args[0]);
		if (!pipex->cmd)
			error_exit(pipex, ERROR_CMD, 127);
		execve(pipex->cmd, pipex->cmd_args, envp);
	}
	error_exit(pipex, ERROR_CMD, 127);
}
