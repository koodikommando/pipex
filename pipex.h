/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okarejok <okarejok@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:03:47 by okarejok          #+#    #+#             */
/*   Updated: 2024/10/15 18:26:35 by okarejok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct t_pipex
{
	char	**paths;
	char	**cmd_args;
	int		infile;
	int		outfile;
	int		pid1;
	int		pid2;
	int		pipe[2];
	int		status;
	char	*cmd;
	char	*infile_name;
	char	*outfile_name;

}	t_pipex;

# define ERROR_INFILE "Infile"
# define ERROR_OUTFILE "Outfile"
# define ERROR_INPUT "Invalid number of arguments.\n"
# define ERROR_PIPE "Pipe"
# define ERROR_CMD "Command not found.\n"
# define ERROR_FORK "Fork"
# define ERROR_CLOSE "Close"
# define ERROR_PATH "Path"
# define ERROR_MALLOC "Malloc"
# define ERROR_EXECVE "Execve() Failed"

void	find_paths(t_pipex *pipex, char **envp);
void	free_parent(t_pipex *pipex);
void	first_child(t_pipex *pipex, char **argv, char **envp);
void	second_child(t_pipex *pipex, char **argv, char **envp);
void	error_exit(t_pipex *pipex, char *error, int errcode);
void	free_child(t_pipex *pipex);
void	error_message(char *error);
char	**pipex_split(char const *s, char const c);

#endif
