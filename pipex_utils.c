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

static int	cheak_access(char *tmp, int *i, char **line, int *len)
{
	if (access (tmp, X_OK) == 0)
	{
		*i = 0;
		while (line[(*i)++] != NULL)
			free(line[*i]);
		free(line);
		return (EXIT_FAILURE);
	}
	ft_bzero(tmp, len[0] + len[1] + 1);
	free(tmp);
	(*i)++;
	return (EXIT_SUCCESS);
}

static char	*set_cmd_test_path(int *len, char *path, char *cmd)
{
	char	*tmp;

	len[0] = ft_strlen(path);
	tmp = malloc (sizeof(char) * (len[0] + len[1] + 2));
	if (!tmp || cmd[0] == ' ')
		exit(EXIT_FAILURE);
	ft_strlcpy(tmp, path, len[0] + 1);
	tmp[len[0]] = '/';
	tmp[len[0] + 1] = '\0';
	ft_strlcat(tmp, cmd, len[0] + len[1] + 2);
	return (tmp);
}

char *allocate_scrypt(char *cmd)
{
	int		cmd_len;
	char	*tmp;

	if (access (cmd, X_OK) != 0)
		return (NULL);
	cmd_len = ft_strlen(cmd);
	tmp = malloc (sizeof(char) * (cmd_len + 1));
	ft_strlcpy(tmp, cmd, cmd_len + 1);
	tmp[cmd_len] = '\0';
	return(tmp);
}

char	*check_valid_path(char **env_var, char *cmd)
{
	int		i[3];
	char	*tmp;
	char	**line;
	int		len[2];

	i[0] = 0;
	i[1] = 0;
	if (cmd[0] == '.' && cmd[1] == '/' )
	{
		tmp = allocate_scrypt(cmd);
		return (tmp);
	}
	while (env_var[i[0]++] != NULL)
		if (!(ft_strncmp(env_var[i[0]], "PATH=", 5)))
			break ;
	line = ft_split(&env_var[i[0]][5], ':');
	len[1] = ft_strlen(cmd);
	while (line[i[1]])
	{
		tmp = set_cmd_test_path(len, line[i[1]], cmd);
		if (cheak_access(tmp, &i[1], line, len) == EXIT_FAILURE)
			break ;
	}
	// printf("+%s+\n", tmp);
	return (tmp);
}

void	open_in_out_put(int *fd, const char **cmd)
{
	fd[0] = open(cmd[1], O_RDONLY);
	if (fd[0] == -1)
	{
		perror (cmd[1]);
		exit (EXIT_FAILURE);
	}
	fd[1] = open(cmd[4], O_WRONLY | O_CREAT, 0766);
	if (fd[1] == -1)
	{
		close(fd[0]);
		perror (cmd[4]);
		exit (EXIT_FAILURE);
	}
}
