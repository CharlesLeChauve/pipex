/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgibert <tgibert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 09:41:24 by tgibert           #+#    #+#             */
/*   Updated: 2024/02/27 11:25:52 by tgibert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_freetab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	execute_cmd(char *cmd, char **env)
{
	char	*path;
	char	**cmd_arr;
	char	err_msg[124];

	cmd_arr = ft_split(cmd, ' ');
	ft_bzero(err_msg, 124);
	path = get_cmd_path(env, cmd_arr[0]);
	if (execve(path, cmd_arr, env) == -1)
	{
		ft_sprintf(err_msg, "command not found: %s\n", cmd_arr[0]);
		ft_putstr_fd(err_msg, STDERR_FILENO);
		ft_freetab(cmd_arr);
		exit (1);
	}
	ft_freetab(cmd_arr);
}

int	open_mode(char *path, char mode)
{
	int	fd;

	if (mode == 'r')
	{
		fd = open(path, O_RDONLY);
		return (fd);
	}
	if (mode == 'w')
	{
		fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		return (fd);
	}
	if (mode == 'a')
	{
		fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
		return (fd);
	}
	return (-1);
}

char	*get_env_path(char **env)
{
	int		i;
	char	*env_path;

	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
			env_path = ft_strdup(&env[i][5]);
	}
	return (env_path);
}

char	*get_cmd_path(char **env, char *cmd)
{
	char	*paths;
	char	**paths_array;
	char	*cmd_path;
	int		i;

	i = 0;
	paths = get_env_path(env);
	paths_array = ft_split(paths, ':');
	free(paths);
	while (paths_array[i])
	{
		cmd_path = ft_strjoin(paths_array[i], "/");
		cmd_path = ft_strjoin(cmd_path, cmd);
		if (access(cmd_path, X_OK) != -1)
		{
			ft_freetab(paths_array);
			return (cmd_path);
		}
		free(cmd_path);
		i++;
	}
	ft_freetab(paths_array);
	return (NULL);
}
