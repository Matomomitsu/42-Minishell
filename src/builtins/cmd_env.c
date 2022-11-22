/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlins <rlins@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 08:51:53 by rlins             #+#    #+#             */
/*   Updated: 2022/11/22 12:34:54 by rlins            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	cmd_env(t_data *data, bool exp_no_arg)
{
	int	i;

	if (data->command->args_count > 1)
		return (error_msg_cmd("env", NULL, "too many arguments", 2));

	if (!data->env)
		return (EXIT_FAILURE);

	i = 0;
	while (data->env[i])
	{
		if (exp_no_arg == true)
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putendl_fd(data->env[i], STDOUT_FILENO);
		i++;
	}
	return (EXIT_SUCCESS);
}
