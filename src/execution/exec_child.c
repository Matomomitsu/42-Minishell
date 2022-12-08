/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtomomit <mtomomit@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 03:06:05 by mtomomit          #+#    #+#             */
/*   Updated: 2022/12/08 20:10:05 by mtomomit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	count_pipes(t_commands *cmds, int num_cmd)
{
	int	num_pipes;

	num_pipes = 0;
	while (cmds->operators[num_cmd] && cmds->operators[num_cmd] == PIPE)
	{
		num_cmd = num_cmd + 1;
		num_pipes++;
	}
	return(num_pipes + 1);
}

int	exec_child(t_data *data, t_commands *cmds, int num_cmd)
{
	cmds->num_exec = cmds->num_exec + count_pipes(cmds, num_cmd);
	while (num_cmd < cmds->num_cmds)
	{
		if (cmds->cmd[num_cmd].args[0])
		{
			if (is_redirection_command(cmds, num_cmd))
				redirection_handler(data, cmds, num_cmd);
			cmds->pid[num_cmd] = fork();
			if (cmds->pid[num_cmd] == -1)
				return (error_msg_cmd("fork", NULL, strerror(errno),
					EXIT_FAILURE));
			else if (cmds->pid[num_cmd] == 0)
				execute_cmd(data, cmds, num_cmd);
		}
		if (cmds->operators[num_cmd] && cmds->operators[num_cmd] == PIPE)
			num_cmd++;
		else
			num_cmd = cmds->num_cmds;
	}
	return (0);
}
