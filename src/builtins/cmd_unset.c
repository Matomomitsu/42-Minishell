/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlins <rlins@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 10:02:42 by rlins             #+#    #+#             */
/*   Updated: 2022/11/22 12:08:53 by rlins            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	cmd_unset(t_data *data)
{
	int	i;
	int	index;
	int	status_code;

	status_code = EXIT_SUCCESS;
	i = 1;
	while (data->command->args[i])
	{
		if (is_valid_var_name(data->command->args[i]) == false)
		{
			status_code = error_msg_cmd("unset", data->command->args[i],
					"not a valid identifier", EXIT_FAILURE);
		}
		else
		{
			index = get_env_var_index(data->env, data->command->args[i]);
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
