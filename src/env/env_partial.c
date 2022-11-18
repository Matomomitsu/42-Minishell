/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_partial.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlins <rlins@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 11:18:55 by rlins             #+#    #+#             */
/*   Updated: 2022/11/18 16:02:17 by rlins            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <minishell.h>

void	env_var_remove(t_data *data, int index)
{
	int	i;
	int	j;

	free_ptr(data->env[index]);
	i = index;
	j = index;
	while (data->env[i + 1])
	{
		data->env[i] = ft_strdup(data->env[i + 1]);
		free_ptr(data->env[i + 1]);
		j++;
		i++;
	}
	data->env = env_var_realloc(data, j);
}
