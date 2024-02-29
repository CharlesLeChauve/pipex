/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgibert <tgibert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:43:14 by tgibert           #+#    #+#             */
/*   Updated: 2024/02/29 12:26:22 by tgibert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	check_open(char *file)
{
	int	fd;

	if (access(file, F_OK) != 0)
	{
		ft_printf("no such file or directory : %s\n", file);
		exit(0);
	}
	if (access(file, R_OK) != 0)
	{
		ft_printf("permission denied : %s\n", file);
		exit(0);
	}
	fd = open_mode(file, 'r');
	return (fd);
}


void	do_input_child(int pipe_fd[2], char *argv[], char **env)
{
	int	fd;

	if (ft_strncmp("here_doc", argv[1], 9))
	{
		fd = check_open(argv[1]);
		dup2(fd, 0);
	}
	dup2(pipe_fd[1], 1);
	close(pipe_fd[0]);
	execute_cmd(argv[2], env);
	if (fd)
		close(fd);
}

void	do_child(int pipe_fd[2], char *cmd, char **env)
{
	close(pipe_fd[0]);
	dup2(pipe_fd[1], 1);
	execute_cmd(cmd, env);
}

int	open_write(char *file, char mode)
{
	int	fd;

	if (access(file, F_OK) == 0 && access(file, W_OK) != 0)
	{
		ft_printf("permission denied : %s\n", file);
		exit(EXIT_FAILURE);
	}
	if (mode == 'w')
		fd = open_mode(file, 'w');
	else if (mode == 'a')
		fd = open_mode(file, 'a');
	else
		fd = -1;
	return (fd);
}

void	do_output(char *av[], char **env, char mode, int ac)
{
	int fd;

	fd = open_write(av[ac - 1], mode);
	dup2(fd, 1);
	execute_cmd(av[ac - 2], env);
	if (fd)
		close(fd);
}

void	do_parent(int pipe_fd[2])
{
	waitpid(0, &(int){0}, 0);
	close(pipe_fd[1]);
	dup2(pipe_fd[0], 0);
}

void	do_pipe(int	iter, char *av[], char **env)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == 0)
	{
		if (iter == 1)
			do_input_child(pipe_fd, av, env);
		else
			do_child(pipe_fd, av[iter], env);
	}
	else if (pid > 0)
	{
		waitpid(0, &(int){0}, 0);
		do_parent(pipe_fd);
	}
		
}

int	main(int ac, char *av[], char **env)
{
	int	i;

	i = 1;
	check_argc(ac);
	if (!ft_strncmp("here_doc", av[1], 8))
	{
		heredoc_handle(av[2]);
		i += 2;
	}
	while (i < ac - 2)
	{
		do_pipe(i, av, env);
		i++;
	}
	if (!ft_strncmp("here_doc", av[1], 8))
		do_output(av, env, 'a', ac);
	else
		do_output(av, env, 'w', ac);
}
