/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtomomit <mtomomit@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 20:12:44 by mtomomit          #+#    #+#             */
/*   Updated: 2022/11/30 16:30:41 by mtomomit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	check_type(char ch)
{
	if (ch >= '0' && ch <= '9')
		return (1);
	if (ch >= 'a' && ch <= 'z')
		return (1);
	if (ch >= 'A' && ch <= 'Z')
		return (1);
	if (ch == '_')
		return (1);
	return (0);
}

static int	get_env_variable_size(char *s, t_index_data *i_data)
{
	int		i;
	int		o;
	char	*exit_value;

	i = i_data->i + 1;
	while (s[i] && check_type(s[i]))
		i++;
	return (i - i_data->i);
}

static char	*get_env_value(char *s, t_index_data *i_data, t_data *data)
{
	int		variable_size;
	int		i;
	char	*env_variable;
	char	*env_value;

	variable_size = get_env_variable_size(s, i_data) - 1;
	if (s[i_data->i + 1] != '?')
	{
		env_variable = (char *)malloc(sizeof(char) * (variable_size + 1));
		env_variable[variable_size] = '\0';
		i = 1;
		while (i <= variable_size)
		{
			env_variable[i - 1] = s[i_data->i + i];
			i++;
		}
		env_value = get_env_var_value(data->env, env_variable);
		free(env_variable);
	}
	else
		env_value = ft_itoa(g_status_code);
	return (env_value);
}

static void	copy_to_new_str(char *new_str, char *s, char *env_value, \
		t_index_data *i_data)
{
	size_t	i;
	size_t	o;
	size_t	j;

	i = 0;
	o = 0;
	j = 0;
	while (s[i] && s[i] != '$')
		new_str[o++] = s[i++];
	if (env_value)
	{
		i++;
		while (env_value[j])
		{
			new_str[o++] = env_value[j++];
			i_data->i++;
		}
	}
	if (s[i] == '?')
		i++;
	else
		while (s[i] && check_type(s[i]))
			i++;
	while (s[i])
		new_str[o++] = s[i++];
	new_str[o] = s[i];
}

char	*handle_env(t_index_data *i_data, char *s, t_data *data)
{
	char	*new_str;
	int		variable_size;
	char	*env_value;
	int		env_value_size;

	env_value = get_env_value(s, i_data, data);
	variable_size = get_env_variable_size(s, i_data);
	if (env_value)
		env_value_size = ft_strlen(env_value) - 1;
	else
		env_value_size = 0;
	new_str = (char *)malloc(sizeof(char) * (ft_strlen(s) - variable_size + \
			env_value_size) + 2);
	new_str[ft_strlen(s) - variable_size + env_value_size + 1] = '\0';
	copy_to_new_str(new_str, s, env_value, i_data);
	return (new_str);
}
