/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlins <rlins@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 08:51:53 by rlins             #+#    #+#             */
/*   Updated: 2022/11/21 07:47:18 by rlins            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	cmd_env(t_data *data, bool exp_no_arg)
{
	int	i;

	i = 0;
	while (data->env[i])
	{
		if (exp_no_arg == true)
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(data->env[i], STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		i++;
	}
}
