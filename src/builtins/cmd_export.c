/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlins <rlins@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 11:53:47 by rlins             #+#    #+#             */
/*   Updated: 2022/11/18 15:33:04 by rlins            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	cmd_export(t_data *data)
{
	char **key_value;
	int	index;

	index = 1;
	if (!data->command->args[1])
		cmd_env(data, true);
	while (data->command->args[index])
	{
		if (ft_strchr(data->command->args[index], '=') != NULL)
		{
			key_value = ft_split(data->command->args[index], '=');
			if (is_valid_var_name(key_value[0]) == false)
			{
				ft_putstr_fd("Minishell: export: not a valid identifier\n",
					STDOUT_FILENO);
				// exit(EXIT_FAILURE);
			}
			set_env_var(data, key_value[0], key_value[1]);
			//  TODO: JÁ FAZER O FREE LOGO NA SEQUENCIA
		}
		index++;
	}
}
