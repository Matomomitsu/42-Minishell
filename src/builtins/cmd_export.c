/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtomomit <mtomomit@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 11:53:47 by rlins             #+#    #+#             */
/*   Updated: 2022/11/30 21:50:53 by mtomomit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	cmd_export(t_data *data, t_commands *cmds, int num_cmd)
{
	int		result;
	char	**key_value;
	int		index;

	index = 1;
	result = EXIT_SUCCESS;
	if (!cmds->cmd[num_cmd].args[1])
		return (cmd_env(data, true, cmds, num_cmd));
	while (cmds->cmd[num_cmd].args[index])
	{
		if (ft_strchr(cmds->cmd[num_cmd].args[index], '=') != NULL)
		{
			key_value = ft_split(cmds->cmd[num_cmd].args[index], '=');
			if (is_valid_var_name(key_value[0]) == false)
			{
				error_msg_cmd("export", cmds->cmd[num_cmd].args[index],
					"not a valid identifier", EXIT_FAILURE);
				result = EXIT_FAILURE;
			}
			set_env_var(data, key_value[0], key_value[1]);
			free_array_str(key_value);
		}
		index++;
	}
	return (result);
}
