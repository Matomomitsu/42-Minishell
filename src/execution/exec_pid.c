/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtomomit <mtomomit@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 03:06:05 by mtomomit          #+#    #+#             */
/*   Updated: 2022/12/07 03:14:01 by mtomomit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	exec_pid(t_data *data, t_commands *cmds, int num_cmd)
{
	while (num_cmd < cmds->num_cmds)
	{
		cmds->pid[num_cmd] = fork();
		if (cmds->pid[num_cmd] == -1)
			return (error_msg_cmd("fork", NULL, strerror(errno),
				EXIT_FAILURE));
		else if (cmds->pid[num_cmd] == 0)
			execute_cmd(data, cmds, num_cmd);
		cmds->num_exec++;
		if (cmds->operators[num_cmd] == PIPE)
			num_cmd++;
		else
			num_cmd = cmds->num_cmds;
	}
	return (0);
}
