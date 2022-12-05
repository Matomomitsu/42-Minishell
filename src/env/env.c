/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtomomit <mtomomit@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 08:36:33 by rlins             #+#    #+#             */
/*   Updated: 2022/12/02 22:57:05 by mtomomit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*check_equal(char *var)
{
	char	*tmp;
	int		i;

	i = 0;
	if (!ft_strchr(var, '='))
		tmp = ft_strjoin(var, "=");
	else
	{
		while (var[i++] != '=')
			;
		tmp = (char *)malloc(sizeof(char) * i + 2);
		tmp[i] = '\0';
		ft_strlcpy(tmp, var, i + 1);
	}
	return (tmp);
}

int	get_env_var_index(char **env, char *var)
{
	int		index;
	char	*tmp;
	char	*temp_env;

	index = 0;
	tmp = check_equal(var);
	if (!tmp)
		return (-1);
	while (env[index])
	{
		temp_env = check_equal(env[index]);
		if (ft_strncmp(tmp, temp_env, ft_strlen(temp_env)) == 0)
		{
			free(temp_env);
			free_ptr(tmp);
			return (index);
		}
		index++;
		free(temp_env);
	}
	free_ptr(tmp);
	return (-1);
}

bool	set_env_var(t_data *data, char *key, char *value)
{
	char	*temp;
	int		index;

	index = get_env_var_index(data->env, key);
	if ((value != NULL && !ft_strchr(key, '=')) || \
		(index != -1 && !ft_strchr(data->env[index], '=')))
		temp = ft_strjoin("=", value);
	else
		temp = ft_strdup("\0");
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
