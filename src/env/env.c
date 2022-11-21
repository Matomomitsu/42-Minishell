/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlins <rlins@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 08:36:33 by rlins             #+#    #+#             */
/*   Updated: 2022/11/21 12:34:45 by rlins            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * TODO: Variable tmp free - OK
 */
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
		if (ft_strncmp(tmp, env[index], ft_strlen(tmp)) == 0)
		{
			free_ptr(tmp);
			return (index);
		}
		index++;
	}
	free_ptr(tmp);
	return (-1);
}

bool	set_env_var(t_data *data, char *key, char *value)
{
	char	*temp;
	int		index;

	index = get_env_var_index(data->env, key);
	if (value == NULL)
		value = "";
	temp = ft_strjoin("=", value);
	if (index != -1 && data->env[index])
	{
		free_ptr(data->env[index]);
		data->env[index] = ft_strjoin(key, temp);
	}
	else
	{
		index = env_var_count(data->env);
		data->env = env_var_realloc(data, (index + 1));
		if (!data->env)
			return (false);
		data->env[index] = ft_strjoin(key, temp);
	}
	free_ptr(temp);
	return (true);
}

int	env_var_count(char **envp)
{
	int	count;

	count = 0;
	while (envp && envp[count])
		count++;
	return (count);
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
