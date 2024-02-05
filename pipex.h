/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okarejok <okarejok@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:03:47 by okarejok          #+#    #+#             */
/*   Updated: 2024/02/05 18:25:24 by okarejok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include "get_next_line/get_next_line.h"

/* write, read, close, fork, pipe, acess, dup2, execve */
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>

/* waitpid, wait */
# include <sys/wait.h>

/* open, unlink */
# include <fcntl.h>

/* malloc, free, exit */
# include <stdlib.h>

/* perror */
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

}	t_pipex;

# define ERROR_INFILE "Infile"
# define ERROR_OUTFILE "Outfile"
# define ERROR_INPUT "Invalid number of arguments.\n"
# define ERROR_PIPE "Pipe"
# define ERROR_CMD "Command not found.\n"
# define ERROR_FORK "Fork"
# define ERROR_DUP "Dup2"
# define ERROR_CLOSE "Close"
# define ERROR_PATH "Path"
# define ERROR_MALLOC "Malloc"

void	find_paths(t_pipex *pipex, char **envp);
void	free_parent(t_pipex *pipex);
void	first_child(t_pipex *pipex, char **argv, char **envp);
void	second_child(t_pipex *pipex, char **argv, char **envp);
void	error_exit(char *error, int errcode);
void	free_child(t_pipex *pipex);
void	error_message(char *error);
char	**pipex_split(char const *s, char const c);


#endif