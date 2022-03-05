/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukhal <mboukhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 16:40:11 by mboukhal          #+#    #+#             */
/*   Updated: 2022/03/02 16:28:10 by mboukhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	exec_pid(int *fd, char **cmd, char ***arg, int mode)
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
	ret = execve(cmd[mode], arg[mode], NULL);
	if (ret == -1)
	{
		write (STDERR_FILENO, arg[mode], ft_strlen(cmd[mode]));
		exit (EXIT_FAILURE);
	}
}

static void	execute_pipe(char **cmd, char ***arg, int *file_fd)
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
		exec_pid(fd, cmd, arg, 0);
	waitpid(pid[0], NULL, 0);
	exec_pid(fd, cmd, arg, 1);
}

static void	set_file_args(char **av, char **env_var, int *fd)
{
	char	**args[2];
	char	*cmd_path[2];

	args[0] = ft_split (av[2], ' ');
	args[1] = ft_split (av[3], ' ');
	cmd_path[0] = check_valid_path (env_var, args[0][0]);
	cmd_path[1] = check_valid_path (env_var, args[1][0]);
	execute_pipe(cmd_path, args, fd);
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
	if (!av[2][0] || !av[3][0])
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
