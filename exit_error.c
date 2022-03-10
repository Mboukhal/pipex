/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukhal <mboukhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 13:28:42 by mboukhal          #+#    #+#             */
/*   Updated: 2022/03/10 14:48:34 by mboukhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	cmd_not_found(char *cmd)
{
	write (STDERR_FILENO, "command not found: ", 20);
	write (STDERR_FILENO, cmd, ft_strlen(cmd));
	exit (EXIT_FAILURE);
}
