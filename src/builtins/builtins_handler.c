/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlins <rlins@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:19:00 by rlins             #+#    #+#             */
/*   Updated: 2022/11/22 12:36:31 by rlins            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	is_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 4) == 0)
		return (true);
	else if (ft_strncmp(cmd, "exit", 4) == 0)
		return (true);
	else if (ft_strncmp(cmd, "pwd", 3) == 0)
		return (true);
	else if (ft_strncmp(cmd, "env", 3) == 0)
		return (true);
	else if (ft_strncmp(cmd, "cd", 2) == 0)
		return (true);
	else if (ft_strncmp(cmd, "unset", 5) == 0)
		return (true);
	else if (ft_strncmp(cmd, "export", 6) == 0)
		return (true);
	else
	{
		ft_putstr_fd("TODO: Must Implement!!!!\n", STDOUT_FILENO);
		exit(EXIT_SUCCESS);
	}
}

int	call_builtin(t_data *data)
{
	//TODO:Lins - Todos métodos precisam de retorno
	int cmd_code;

	cmd_code = CMD_NOT_FOUND;
	if (ft_strncmp(data->command->cmd, "echo", 4) == 0)
		cmd_echo(data);
	else if (ft_strncmp(data->command->cmd, "exit", 4) == 0)
		cmd_exit(data);
	else if (ft_strncmp(data->command->cmd, "pwd", 3) == 0)
		cmd_code = cmd_pwd();
	else if (ft_strncmp(data->command->cmd, "env", 3) == 0)
		cmd_code = cmd_env(data, false);
	else if (ft_strncmp(data->command->cmd, "cd", 2) == 0)
		cmd_cd(data);
	else if (ft_strncmp(data->command->cmd, "unset", 5) == 0)
		cmd_code = cmd_unset(data);
	else if (ft_strncmp(data->command->cmd, "export", 6) == 0)
		cmd_export(data);
	else
	{
		ft_putstr_fd("TODO: Must Implement!!!!\n", STDOUT_FILENO);
		exit(EXIT_SUCCESS);
	}
	return (cmd_code);
}
