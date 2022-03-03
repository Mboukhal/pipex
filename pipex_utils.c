/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukhal <mboukhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 20:35:15 by mboukhal          #+#    #+#             */
/*   Updated: 2022/03/03 13:44:23 by mboukhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	cheak_access(char *tmp, int *i, char **line, int *len)
{
	if (access (tmp, X_OK) == 0)
	{
		*i = 0;
		while (line[(*i)++] != NULL)
			free(line[*i]);
		free(line);
		return (EXIT_FAILURE);
	}
	ft_bzero(tmp, len[0] + len[1] + 2);
	free(tmp);
	(*i)++;
	return (EXIT_SUCCESS);
}

char	*check_valid_path(char **env_var, char *cmd)
{
	int		i[3];
	char	*tmp;
	char	**line;
	int		len[2];

	i[0] = 0;
	i[1] = 0;
	if (!(access(cmd, X_OK)))
		return (cmd);
	while (env_var[i[0]++] != NULL)
		if (!(ft_strncmp(env_var[i[0]], "PATH=", 5)))
			break ;
	line = ft_split(ft_strchr(env_var[i[0]], '/'), ':');
	len[1] = ft_strlen(cmd);
	while (line[i[1]] != NULL)
	{
		len[0] = ft_strlen(line[i[1]]);
		tmp = malloc (sizeof(char) * (len[0] + len[1] + 2));
		ft_strlcpy(tmp, line[i[1]], len[0] + 1);
		tmp[len[0]] = '/';
		ft_strlcat(tmp, cmd, len[0] + len[1] + 2);
		if (cheak_access(tmp, &i[1], line, len) == EXIT_FAILURE)
			break ;
	}
	return (tmp);
}

void open_in_out_put(int *fd, const char **cmd)
{
	fd[0] = open(cmd[1], O_RDONLY);
	if (fd[0] == -1)
	{
		perror (cmd[1]);
		exit (EXIT_FAILURE);
	}
	fd[1] = open(cmd[4], O_WRONLY | O_CREAT, 0766 );
	if (fd[1] == -1)
	{
		close(fd[0]);
		perror (cmd[4]);
		exit (EXIT_FAILURE);
	}
}
