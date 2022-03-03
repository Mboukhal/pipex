/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukhal <mboukhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 14:57:30 by mboukhal          #+#    #+#             */
/*   Updated: 2022/03/02 14:41:56 by mboukhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <errno.h>
# include"libft.h"

# define FILE_FOUND            1
# define FILE_NOT_FOUND        1

// void	open_files(int *fd1, int *fd2, char *file_in, char *file_out);
void	open_in_out_put(int *fd, const char **cmd);
char	*check_valid_path(char **env_var, char *cmd);
int		cheak_path(char *path);

#endif	/* PIPEX_H */
