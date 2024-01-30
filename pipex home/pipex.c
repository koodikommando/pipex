/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okarejok <okarejok@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 15:15:29 by okarejok          #+#    #+#             */
/*   Updated: 2024/01/29 17:15:42 by okarejok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static  void	close_pipes(t_pipex *pipex)
{
	close(pipex->pipe[0]);
	close(pipex->pipe[1]);
}

static void	create_forks(t_pipex *pipex, char **argv, char **envp)
{
	pipex->pid1 = fork();
	if (pipex->pid1 == -1)
		error_exit(ERROR_FORK, 1);
	if (pipex->pid1 == 0)
		first_child(pipex, argv, envp);
	else
	{
		pipex->pid2 = fork();
		if (pipex->pid2 == -1)
		{
			waitpid(pipex->pid1, &pipex->status, 0);
			error_exit(ERROR_FORK, 1);
		}
		if (pipex->pid2 == 0)
			second_child(pipex, argv, envp);
	}
}

int	main(int argc, char *argv[], char **envp)
{
	t_pipex	pipex;

	pipex.cmd_args = NULL;
	pipex.cmd = NULL;
	pipex.paths = NULL;
	if (argc != 5 || !envp)
		return (1);
	if (pipe(pipex.pipe) < 0)
		error_exit(ERROR_PIPE, 1);
	find_paths(&pipex, envp);
	create_forks(&pipex, argv, envp);
	close_pipes(&pipex);
	waitpid(pipex.pid1, &pipex.status, 0);
	waitpid(pipex.pid2, &pipex.status, 0);
	free_parent(&pipex);
	return (WEXITSTATUS(pipex.status));
}
