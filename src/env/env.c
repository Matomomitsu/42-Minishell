/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlins <rlins@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 08:36:33 by rlins             #+#    #+#             */
/*   Updated: 2022/11/17 09:14:44 by rlins            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_env_var_value(char **env, char *var)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = ft_strjoin(var, "=");
	if (!tmp)
		return (NULL);
	while (env[i])
	{
		if (ft_strncmp(tmp, env[i], ft_strlen(tmp) == 0))
		{
			free_ptr(tmp);
			return (ft_strchr(env[i], '=') + 1);
		}
		i++;
	}
	free_ptr(tmp);
	return (NULL);
}

int	get_env_var_index(char **env, char *var)
{
	int		index;
	char	*tmp;

	index = 0;
	tmp = ft_strjoin(var, "=");
	if (!tmp)
		return (-1);
	while (env[index])
	{
		if (ft_strncmp(tmp, env[index], ft_strlen(tmp) == 0))
		{
			free_ptr(tmp);
			return (index);
		}
		index++;
	}
	free_ptr(tmp);
	return (-1);
}
