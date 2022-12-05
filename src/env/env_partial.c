/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_partial.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtomomit <mtomomit@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 11:18:55 by rlins             #+#    #+#             */
/*   Updated: 2022/12/02 19:24:45 by mtomomit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_env_var_value(char **env, char *var)
{
	int		i;
	char	*tmp;
	char	*result;

	i = 0;
	tmp = ft_strjoin(var, "=");
	if (!tmp)
		return (NULL);
	while (env[i])
	{
		if (ft_strncmp(tmp, env[i], ft_strlen(tmp)) == 0)
		{
			free_ptr(tmp);
			result = ft_strchr(env[i], '=') + 1;
			return (result);
		}
		i++;
	}
	free_ptr(tmp);
	return (NULL);
}

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

char	**env_var_realloc(t_data *data, int size)
{
	char	**new_env_var;
	int		i;

	i = 0;
	new_env_var = ft_calloc((size + 1), sizeof * new_env_var);
	if (!new_env_var)
		return (NULL);
	while (data->env[i] && i < size)
	{
		new_env_var[i] = ft_strdup(data->env[i]);
		free_ptr(data->env[i]);
		i++;
	}
	free_ptr(data->env);
	return (new_env_var);
}
