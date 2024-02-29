/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgibert <tgibert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 08:06:08 by tgibert           #+#    #+#             */
/*   Updated: 2024/02/28 15:38:32 by tgibert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "pipex.h"

int		check_acces(char *file, char mode);
void	check_argc(int argc);
void	heredoc_handle(char *limiter);

#endif //PIPEX_BONUS_H