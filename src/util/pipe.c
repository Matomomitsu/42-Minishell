/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtomomit <mtomomit@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:21:30 by rlins             #+#    #+#             */
/*   Updated: 2022/12/16 17:47:19 by mtomomit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

typedef struct s_num_parenthesis
{
	int	first_p;
	int	last_p;
}	t_num_parenthesis;

static void	init_variables(int *i, t_num_parenthesis *num_p)
{
	*i = 0;
	num_p->first_p = 0;
	num_p->last_p = 0;
}

static void	reset_num_parenthesis(t_num_parenthesis *num_p, t_commands *cmds, int index)
{
	if (cmds->operators[index] != PIPE)
		num_p->first_p = num_p->first_p - 1;
	else
		num_p->last_p++;
}

static int	checking_parenthesis(t_commands *cmds, int index)
{
	int	i;
	int	o;
	t_num_parenthesis	num_p;

	init_variables(&i, &num_p);
	while (i < cmds->num_cmds)
	{
		o = 0;
		while (cmds->cmds[i][o++] == '(')
			num_p.first_p++;
		while (cmds->cmds[i][o])
		{
			if (cmds->cmds[i][o] == ')')
				reset_num_parenthesis(&num_p, cmds, i);
			o++;
		}
		i++;
		if (num_p.first_p >= 1 && i > index && num_p.last_p >= 1)
			break;
	}
	if (i < index)
		return (0);
	else
		return (i - 1);
}

static void	checking_pipes(t_commands *cmds, int index)
{
	int	i;

	i = 0;
	if (cmds->operators[index] != PIPE)
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
