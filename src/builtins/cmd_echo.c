/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlins <rlins@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 09:08:47 by rlins             #+#    #+#             */
/*   Updated: 2022/12/02 10:27:23 by rlins            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static bool	exist_n_option(t_commands *cmds, int num_cmd);

int	cmd_echo(t_data *data, t_commands *cmds, int num_cmd)
{
	int		i;
	char	**echo_cmd;
	bool	option_n;

	option_n = exist_n_option(cmds, num_cmd);
	if (option_n == true)
		i = 2;
	else
		i = 1;
	while (cmds->cmd[num_cmd].args[i])
	{
		ft_putstr_fd(cmds->cmd[num_cmd].args[i], STDOUT_FILENO);
		if (cmds->cmd[num_cmd].args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (option_n == false)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (EXIT_SUCCESS);
}

/**
 * @brief Check if in the command, the param -n was used
 * @param data Structure of MiniShell
 * @return true (with option)
 * @return false (without option)
 */
static bool	exist_n_option(t_commands *cmds, int num_cmd)
{
	if (cmds->cmd[num_cmd].args[1]
		&& ft_strncmp(cmds->cmd[num_cmd].args[1], "-n", 3) == 0)
		return (true);
	return (false);
}
