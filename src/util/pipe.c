/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtomomit <mtomomit@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:21:30 by rlins             #+#    #+#             */
/*   Updated: 2022/12/14 15:26:05 by mtomomit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	checking_parenthesis(t_commands *cmds, int index)
{
	while (index < cmds->num_cmds && !ft_strchr(cmds->cmds[index], ')'))
		index++;
	if (index < cmds->num_cmds)
		return (index);
	else
		return (0);
}

static void	checking_pipes(t_commands *cmds, int index)
{
	int	i;

	i = checking_parenthesis(cmds, index);
	if (i == 0)
		i = index;
	if (cmds->operators[i] == PIPE)
		dup2(cmds->pipe[i + 1].fd[1], STDOUT);
}

void	set_pipe_fds(t_commands *cmds, int index)
{
	if (index == 0)
		checking_pipes(cmds, index);
	else
	{
		if (cmds->operators[index])
			checking_pipes(cmds, index);
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
