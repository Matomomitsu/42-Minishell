/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlins <rlins@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:19:00 by rlins             #+#    #+#             */
/*   Updated: 2022/11/17 15:07:52 by rlins            ###   ########.fr       */
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
	else
	{
		ft_putstr_fd("TODO: Must Implement!!!!\n", STDOUT_FILENO);
		exit(EXIT_SUCCESS);
	}
}

void	call_builtin(t_data *data)
{
	if (ft_strncmp(data->command->cmd, "echo", 4) == 0)
		cmd_echo();
	else if (ft_strncmp(data->command->cmd, "exit", 4) == 0)
		cmd_exit();
	else if (ft_strncmp(data->command->cmd, "pwd", 3) == 0)
		cmd_pwd();
	else if (ft_strncmp(data->command->cmd, "env", 3) == 0)
		cmd_env(data);
	else if (ft_strncmp(data->command->cmd, "cd", 2) == 0)
		cmd_cd(data);
	else
	{
		ft_putstr_fd("TODO: Must Implement!!!!\n", STDOUT_FILENO);
		exit(EXIT_SUCCESS);
	}
}
