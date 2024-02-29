/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgibert <tgibert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 09:41:57 by tgibert           #+#    #+#             */
/*   Updated: 2024/02/26 08:10:16 by tgibert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include "libft/libft.h"

char	*get_env_path(char **env);
char	*get_cmd_path(char **env, char *cmd);
int		open_mode(char *path, char mode);
void	execute_cmd(char *cmd, char **env);

#endif