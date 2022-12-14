/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtomomit <mtomomit@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:21:30 by rlins             #+#    #+#             */
/*   Updated: 2022/12/14 15:04:32 by mtomomit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	set_pipe_fds(t_commands *cmds, int index)
{
	if (index == 0 && cmds->operators[index] == PIPE)
		dup2(cmds->pipe[index + 1].fd[1], STDOUT);
	else
	{
		if (cmds->operators[index] && cmds->operators[index] == PIPE)
			dup2(cmds->pipe[index + 1].fd[1], STDOUT);
		if (cmds->operators[index - 1] == PIPE)
			dup2(cmds->pipe[index].fd[0], STDIN);
	}
}

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
