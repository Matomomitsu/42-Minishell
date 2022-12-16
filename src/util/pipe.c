/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtomomit <mtomomit@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:21:30 by rlins             #+#    #+#             */
/*   Updated: 2022/12/16 13:59:25 by mtomomit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	checking_parenthesis(t_commands *cmds, int index)
{
	int	i;
	int	o;
	int	num_parenthesis;

	i = 0;
	num_parenthesis = 0;
	while (i < cmds->num_cmds && num_parenthesis < 2)
	{
		o = 0;
		while (cmds->cmds[i][o] && cmds->cmds[i][o] == ' ')
			o++;
		while (cmds->cmds[i][o++] == '(')
			num_parenthesis++;
		while (cmds->cmds[i][o])
		{
			if (cmds->cmds[i][o] == ')')
				num_parenthesis++;
			if (cmds->operators[i] != PIPE && cmds->cmds[i][o] == ')')
				num_parenthesis = num_parenthesis - 2;
			o++;
		}
		i++;
	}
	if (i < index)
		return (0);
	else
		return (i - 1);
}

static void	checking_pipes(t_commands *cmds, int index)
{
	int	i;

	i = checking_parenthesis(cmds, index);
	if (i == 0)
		i = index;
	if (cmds->operators[i] == PIPE)
	{
		dup2(cmds->pipe[i + 1].fd[1], STDOUT);
	}
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
	close_pipe_fds(cmds);
}
