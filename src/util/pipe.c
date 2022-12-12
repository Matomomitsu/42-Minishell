/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtomomit <mtomomit@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:21:30 by rlins             #+#    #+#             */
/*   Updated: 2022/12/12 13:36:36 by mtomomit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	set_pipe_fds(t_commands *cmds, int index)
{
	if (index == 0 && cmds->operators[index] == PIPE)
		dup2(cmds->cmd[index + 1].pipe_fd[1], STDOUT);
	else
	{
		if (cmds->operators[index] && cmds->operators[index] == PIPE)
			dup2(cmds->cmd[index + 1].pipe_fd[1], STDOUT);
		if (cmds->operators[index - 1] == PIPE)
			dup2(cmds->cmd[index].pipe_fd[0], STDIN);
	}
	close_pipe_fds(cmds);
}

void	close_pipe_fds(t_commands *cmds)
{
	int	i;

	i = 0;
	while (i < cmds->num_cmds)
	{
		if (cmds->cmd[i].pipe_fd)
		{
			close(cmds->cmd[i].pipe_fd[0]);
			close(cmds->cmd[i].pipe_fd[1]);
		}
		i++;
	}
}
