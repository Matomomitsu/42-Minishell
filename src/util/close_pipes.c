/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtomomit <mtomomit@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 13:54:40 by mtomomit          #+#    #+#             */
/*   Updated: 2022/12/16 13:55:00 by mtomomit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	close_pipe_fds(t_commands *cmds)
{
	int	i;

	i = 0;
	while (i < cmds->num_cmds)
	{
		if (cmds->pipe[i].fd)
		{
			close(cmds->pipe[i].fd[0]);
			close(cmds->pipe[i].fd[1]);
		}
		i++;
	}
}

void	close_exec_pipe_fds(t_commands *cmds)
{
	int	i;

	i = 0;
	while (i < cmds->num_exec)
	{
		if (cmds->pipe[i].fd)
		{
			close(cmds->pipe[i].fd[0]);
			close(cmds->pipe[i].fd[1]);
		}
		i++;
	}
}
