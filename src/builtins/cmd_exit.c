/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtomomit <mtomomit@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:14:03 by rlins             #+#    #+#             */
/*   Updated: 2022/12/23 02:02:18 by mtomomit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	exit_code_handler(char *arg, bool *error);

int	cmd_exit(t_data *data, t_commands *cmds, int num_cmd)
{
	int		exit_code;
	bool	error;

	error = false;
	if (!cmds || !cmds->cmd[num_cmd].args[1])
		exit_code = g_status_code;
	else
	{
		exit_code = exit_code_handler(cmds->cmd[num_cmd].args[1], &error);
		if (error)
			exit_code = error_msg_cmd("exit", cmds->cmd[num_cmd].args[1],
					"numeric argument required", STDERR_FILENO);
		else if (cmds->cmd[num_cmd].args[2])
			return (error_msg_cmd("exit", NULL, "too many arguments",
					EXIT_FAILURE));
	}
	close_fds(cmds, false);
	free_cmds(cmds);
	ft_putendl_fd("exit", STDOUT);
	exit_shell(data, exit_code);
	return (STDERR_FILENO);
}

/**
 * @brief Handler with exit code .
 *	Returns 0 if no arguments were provided.
 *	Returns 2 in case argument is not digits.
 *	Returns the numeric exit code on success.
 * 256 - Look for "256 on exit status" in stack overflow
 * @param arg
 * @param error
 * @return int
 */
static int	exit_code_handler(char *arg, bool *error)
{
	unsigned long long	i;

	if (!arg)
		return (g_status_code);
	i = 0;
	while (ft_isspace(arg[i]))
		i++;
	if (arg[i] == '\0')
		*error = true;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	if (!ft_isdigit(arg[i]))
		*error = true;
	while (arg[i])
	{
		if (!isdigit(arg[i]) && !ft_isspace(arg[i]))
			*error = true;
		i++;
	}
	i = ft_ato_long(arg, error);
	return (i % 256);
}
