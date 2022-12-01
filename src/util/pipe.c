/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlins <rlins@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:21:30 by rlins             #+#    #+#             */
/*   Updated: 2022/12/01 11:16:10 by rlins            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	set_pipe_fds(t_commands *cmds, int index)
{
	if (index == 0)
		dup2(cmds->cmd[index].pipe_fd[1], STDOUT_FILENO);
	else
		dup2(cmds->cmd[index - 1].pipe_fd[0], STDIN_FILENO);
	close_pipe_fds(cmds, index, false);
}

void	close_pipe_fds(t_commands *cmds, int index, bool close_both)
{
	int	i;

	i = 0;
	while (i < cmds->num_cmds)
	{
		if (cmds->cmd[i].pipe_fd && (i != index || close_both == true))
		{
			close(cmds->cmd[i].pipe_fd[0]);
			close(cmds->cmd[i].pipe_fd[1]);
		}
		i++;
	}
}
