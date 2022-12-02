/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtomomit <mtomomit@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 10:02:42 by rlins             #+#    #+#             */
/*   Updated: 2022/12/02 10:12:41 by mtomomit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	cmd_unset(t_data *data, t_commands *cmds, int num_cmd)
{
	int	i;
	int	index;
	int	status_code;

	status_code = EXIT_SUCCESS;
	i = 1;
	while (cmds->cmd[num_cmd].args[i])
	{
		if (is_valid_var_name(cmds->cmd[num_cmd].args[i]) == false)
		{
			status_code = error_msg_cmd("unset", cmds->cmd[num_cmd].args[i],
					"not a valid identifier", EXIT_FAILURE);
		}
		else
		{
			index = get_env_var_index(data->env, cmds->cmd[num_cmd].args[i]);
			if (index != -1)
				env_var_remove(data, index);
		}
		i++;
	}
	return (status_code);
}

bool	is_valid_var_name(char *name)
{
	int	i;

	i = 0;
	if (!ft_isalpha(name[i]) && name[i] != '_')
		return (false);
	while (name[i] && name[i] != '=')
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (false);
		i++;
	}
	return (true);
}
