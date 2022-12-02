/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtomomit <mtomomit@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:19:00 by rlins             #+#    #+#             */
/*   Updated: 2022/12/02 10:39:00 by mtomomit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	is_builtin_without_output(t_commands *cmds)
{
	if (ft_strncmp(cmds->cmd[0].args[0], "cd", 3) == 0)
		return (true);
	else if (ft_strncmp(cmds->cmd[0].args[0], "exit", 5) == 0)
		return (true);
	else if (ft_strncmp(cmds->cmd[0].args[0], "unset", 6) == 0)
		return (true);
	else if (ft_strncmp(cmds->cmd[0].args[0], "export", 7) == 0 && \
			cmds->cmd[0].args[1])
		return (true);
	else
		return (false);
}

bool	is_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (true);
	else if (ft_strncmp(cmd, "exit", 5) == 0)
		return (true);
	else if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (true);
	else if (ft_strncmp(cmd, "env", 4) == 0)
		return (true);
	else if (ft_strncmp(cmd, "export", 7) == 0)
		return (true);
	else if (ft_strncmp(cmd, "cd", 3) == 0)
		return (true);
	else if (ft_strncmp(cmd, "unset", 6) == 0)
		return (true);
	else
		return (false);
}

int	call_builtin(t_data *data, t_commands *cmds, int num_cmd)
{
	int	cmd_code;

	cmd_code = CMD_NOT_FOUND;
	if (ft_strncmp(cmds->cmd[num_cmd].args[0], "echo", 5) == 0)
		cmd_code = cmd_echo(data, cmds, num_cmd);
	else if (ft_strncmp(cmds->cmd[num_cmd].args[0], "exit", 5) == 0)
		cmd_code = cmd_exit(data, cmds, num_cmd);
	else if (ft_strncmp(cmds->cmd[num_cmd].args[0], "pwd", 4) == 0)
		cmd_code = cmd_pwd();
	else if (ft_strncmp(cmds->cmd[num_cmd].args[0], "env", 4) == 0)
		cmd_code = cmd_env(data, false, cmds, num_cmd);
	else if (ft_strncmp(cmds->cmd[num_cmd].args[0], "cd", 3) == 0)
		cmd_code = cmd_cd(data, cmds, num_cmd);
	else if (ft_strncmp(cmds->cmd[num_cmd].args[0], "unset", 6) == 0)
		cmd_code = cmd_unset(data, cmds, num_cmd);
	else if (ft_strncmp(cmds->cmd[num_cmd].args[0], "export", 7) == 0)
		cmd_code = cmd_export(data, cmds, num_cmd);
	else
		exit(EXIT_SUCCESS);
	return (cmd_code);
}
