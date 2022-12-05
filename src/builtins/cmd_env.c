/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtomomit <mtomomit@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 08:51:53 by rlins             #+#    #+#             */
/*   Updated: 2022/12/02 16:55:10 by mtomomit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	cmd_env(t_data *data, t_commands *cmds, int num_cmd)
{
	int		i;
	char	*temp_char;

	if (cmds->cmd[num_cmd].args[1])
		return (error_msg_cmd("env", NULL, "too many arguments", STDERR));
	if (!data->env)
		return (EXIT_FAILURE);
	i = 0;
	while (data->env[i])
	{
		if (ft_strchr(data->env[i], '='))
			ft_putendl_fd(data->env[i], STDOUT_FILENO);
		i++;
	}
	return (EXIT_SUCCESS);
}
