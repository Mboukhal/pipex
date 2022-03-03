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

void	exec_pid(int *fd, char **cmd, char ***arg, int mode)
{
	int	i;
	int ret;

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
		dprintf(2, "hi there\n");
		exit(EXIT_FAILURE);
	}
}

void	execute_pipe(char **cmd, char ***arg, int *file_fd)
{
	int	i;
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
	// pid[1] = fork();
	// if (pid[1] == -1)
	// 	exit(EXIT_FAILURE);
	// if (pid[1] == 0)
		exec_pid(fd, cmd, arg, 1);
	i = 0;
	while (i < 4)
		close(fd[i++]);
	// waitpid(pid[1], NULL, 0);
}

void	set_file_args(char **av, char **env_var, int *fd)
{
	char	**args[2];
	char	*cmd_path[2];
	// int		i;


	// printf("ok\n");
	args[0] = ft_split (av[2], ' ');
	args[1] = ft_split (av[3], ' ');
	cmd_path[0] = check_valid_path (env_var, args[0][0]);
	cmd_path[1] = check_valid_path (env_var, args[1][0]);
	execute_pipe(cmd_path, args, fd);
// 	i = 1;
// 	while (args[0][i] != NULL)
// 		free(args[0][i++]);
// 	i = 1;
// 	while (args[1][i] != NULL)
// 		free(args[1][i++]);
// 	free(args[0]);
// 	free(args[1]);
// 	free(args);
// 	free(cmd_path[0]);
// 	free(cmd_path[1]);
// 	free(cmd_path);
// 	printf("%p %p\n", cmd_path[0], cmd_path);
// 	printf("ok");
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
	errno = 0;
	i = 0;
	open_in_out_put(fd, (const char **)av);
	// open_files (&fd[0], &fd[1], av[1], av[4]);
	set_file_args(av, env_var, fd);
	return (EXIT_SUCCESS);
}
