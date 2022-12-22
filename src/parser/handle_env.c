/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtomomit <mtomomit@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 20:12:44 by mtomomit          #+#    #+#             */
/*   Updated: 2022/12/21 20:03:32 by mtomomit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	copy_start(char *new_str, char *s, t_index_data *aux)
{
	while (s[aux->i])
	{
		if (s[aux->i] == '$' && s[aux->i + 1] && \
			(ft_isalnum(s[aux->i + 1]) || \
			s[aux->i + 1] == '_' || s[aux->i + 1] == '?'))
			break ;
		else
			new_str[aux->malloc_size++] = s[aux->i++];
	}
}

static int	get_env_variable_size(char *s, t_index_data *i_data)
{
	int		i;

	i = i_data->i + 1;
	while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
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
	if (variable_size == 0 && s[i_data->i + 1] != '?')
		env_value = ft_strdup("$");
	else if (s[i_data->i + 1] != '?')
	{
		env_variable = (char *)malloc(sizeof(char) * (variable_size + 1));
		env_variable[variable_size] = '\0';
		i = 1;
		while (i <= variable_size)
		{
			env_variable[i - 1] = s[i_data->i + i];
			i++;
		}
		env_value = ft_strdup(get_env_var_value(data->env, env_variable));
		free(env_variable);
	}
	else
		env_value = ft_itoa(g_status_code);
	return (env_value);
}

static void	copy_to_new_str(char *new_str, char *s, char *env_value, \
		t_index_data *i_data)
{
	t_index_data	aux;

	aux.i = 0;
	aux.j = 0;
	aux.malloc_size = 0;
	copy_start(new_str, s, &aux);
	if (s[aux.i])
		aux.i++;
	if (env_value)
	{
		while (env_value[aux.j])
			new_str[aux.malloc_size++] = env_value[aux.j++];
		i_data->i = i_data->i + aux.j;
	}
	if (s[aux.i] == '?')
		aux.i++;
	else
		while (s[aux.i] && (ft_isalnum(s[aux.i]) || s[aux.i] == '_'))
			aux.i++;
	while (s[aux.i])
		new_str[aux.malloc_size++] = s[aux.i++];
	new_str[aux.malloc_size] = s[aux.i];
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
	free(env_value);
	return (new_str);
}
