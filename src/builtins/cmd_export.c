/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlins <rlins@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 11:53:47 by rlins             #+#    #+#             */
/*   Updated: 2022/11/23 07:36:09 by rlins            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	cmd_export(t_data *data)
{
	int		result;
	char	**key_value;
	int		index;

	index = 1;
	result = EXIT_SUCCESS;
	if (!data->command->args[1])
		return (cmd_env(data, true));
	while (data->command->args[index])
	{
		if (ft_strchr(data->command->args[index], '=') != NULL)
		{
			key_value = ft_split(data->command->args[index], '=');
			if (is_valid_var_name(key_value[0]) == false)
			{
				error_msg_cmd("export", data->command->args[index],
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
