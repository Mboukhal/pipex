/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukhal <mboukhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 16:40:11 by mboukhal          #+#    #+#             */
/*   Updated: 2022/03/10 14:43:07 by mboukhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	exec_pid(int *fd, char **cmd, char **arg, int mode)
{
	int	i;
	int	ret;

	if (mode == 0)
		dup2(fd[1], STDOUT_FILENO);
	else
		dup2(fd[0], STDIN_FILENO);
	dup2(fd[mode + 2], mode);
	i = 0;
	while (i < 4)
		close(fd[i++]);
	ret = execve(cmd[mode], arg, NULL);
	if (ret == -1)
	{
		write (STDERR_FILENO, arg, ft_strlen(cmd[mode]));
		exit (EXIT_FAILURE);
	}
}

static void	execute_pipe(char **cmd, char **arg1, char **arg2, int *file_fd)
{
	int	fd[4];
	int	pid[2];

	fd[2] = file_fd[0];
	fd[3] = file_fd[1];
	if (pipe(fd) == -1)
		return ;
	pid[0] = fork();
	if (pid[0] == -1)
		return ;
	if (pid[0] == 0)
		exec_pid(fd, cmd, arg1, 0);
	waitpid(pid[0], NULL, 0);
	exec_pid(fd, cmd, arg2, 1);
}

static	char	**set_arg(char **cmd_path, char *cmd, char **env_var)
{
	char	*tmp;
	char	**args;
	int		cmd_len;

	cmd_len = ft_strlen(cmd);
	tmp = malloc(sizeof(char) * (cmd_len + 4));
	if (cmd[0] == '.' && cmd[1] == '/')
	{
		*cmd_path = malloc (sizeof(char) * 9);
		ft_strlcpy(*cmd_path, "/bin/sh", 8);
		ft_strlcpy(tmp, "sh ", 4);
		tmp[3] = '\0';
		ft_strlcat(tmp, cmd, cmd_len + 4);
		args = ft_split(tmp, ' ');
	}
	else
	{
		args = ft_split(cmd, ' ');
		*cmd_path = check_valid_path(env_var, args[0]);
	}
	free(tmp);
	return (args);
}

static void	set_file_args(char **av, char **env_var, int *fd)
{
	char	**args1;
	char	**args2;
	char	*cmd_path[2];

	args1 = set_arg(&cmd_path[0], av[2], env_var);
	args2 = set_arg(&cmd_path[1], av[3], env_var);
	execute_pipe(cmd_path, args1, args2, fd);
}

int	main(int ac, char **av, char **env_var)
{
	int	fd[2];
	int	i;

	if (ac != 5)
	{
		write (STDERR_FILENO, "ERROR\n\t Non valide args", 24);
		return (EXIT_FAILURE);
	}
	if (!av[1][0] || !av[4][0])
	{
		write (STDERR_FILENO, av[0], ft_strlen(av[0]));
		write (STDERR_FILENO, ": no such file or directory: ", 28);
		return (EXIT_FAILURE);
	}
	if (!av[2][0] || !av[3][0] || av[2][0] == ' ' || av[3][0] == ' ')
	{
		write (STDERR_FILENO, av[0], ft_strlen(av[0]));
		write (STDERR_FILENO, ": permission denied:", 19);
		return (EXIT_FAILURE);
	}
	errno = 0;
	i = 0;
	open_in_out_put(fd, (const char **)av);
	set_file_args(av, env_var, fd);
	return (EXIT_SUCCESS);
}
