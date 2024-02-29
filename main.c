/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgibert <tgibert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 07:49:28 by tgibert           #+#    #+#             */
/*   Updated: 2024/02/27 07:21:48 by tgibert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	do_child(char **argv, char **env, int pipe_fd[2])
{
	int	fd;

	if (access(argv[1], F_OK) != 0)
	{
		ft_printf("no such file or directory : %s\n", argv[1]);
		exit(0);
	}
	if (access(argv[1], R_OK) != 0)
	{
		ft_printf("permission denied : %s\n", argv[1]);
		exit(0);
	}
	fd = open_mode(argv[1], 'r');
	dup2(fd, 0);
	dup2(pipe_fd[1], 1);
	close(pipe_fd[0]);
	execute_cmd(argv[2], env);
	close(fd);
}

void	do_parent(char **argv, char **env, int pipe_fd[2])
{
	int	fd;

	if (access(argv[4], F_OK) == 0 && access(argv[4], W_OK) != 0)
	{
		ft_printf("permission denied : %s\n", argv[4]);
		exit(0);
	}
	fd = open_mode(argv[4], 'w');
	dup2(fd, 1);
	dup2(pipe_fd[0], 0);
	close(pipe_fd[1]);
	execute_cmd(argv[3], env);
	close(fd);
}

int	main(int ac, char *av[], char **env)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (ac != 5)
	{
		ft_putstr_fd("This program takes 4 arguments;\n\
			./pipex <file1> <cmd1> <cmd2> <file2>\n", 2);
		exit(0);
	}
	if (pipe(pipe_fd) == -1)
		exit(-1);
	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd("Fork failed\n", STDERR_FILENO);
		return (0);
	}
	if (pid == 0)
		do_child(av, env, pipe_fd);
	else if (pid > 0)
	{
		waitpid(0, &(int){0}, 0);
		do_parent(av, env, pipe_fd);
	}
}
