/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtomomit <mtomomit@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 11:53:47 by rlins             #+#    #+#             */
/*   Updated: 2022/12/07 22:12:17 by mtomomit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*add_quotes(char *env)
{
	int		i;
	int		o;
	char	*temp_char;

	o = 0;
	while (env[o] && env[o++] != '=')
		;
	if (!env[o] && env[o - 1] != '=')
		return (NULL);
	temp_char = malloc(sizeof(char) * ft_strlen(env) + 3);
	temp_char[ft_strlen(env) + 2] = '\0';
	i = 0;
	o = 0;
	while (env[o] != '=')
		temp_char[i++] = env[o++];
	temp_char[i++] = env[o++];
	temp_char[i++] = '"';
	while (env[o])
		temp_char[i++] = env[o++];
	temp_char[i++] = '"';
	return (temp_char);
}

static int	print_env(t_data *data)
{
	char	*temp_char;
	int		i;

	i = 0;
	if (!data->env)
		return (EXIT_FAILURE);
	while (data->env[i])
	{
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
			temp_char = add_quotes(data->env[i]);
			if (temp_char)
				ft_putendl_fd(temp_char, STDOUT_FILENO);
			else
				ft_putendl_fd(data->env[i], STDOUT_FILENO);
			i++;
			free(temp_char);
	}
	return (EXIT_SUCCESS);
}

int	cmd_export(t_data *data, t_commands *cmds, int num_cmd)
{
	int		result;
	int		index;

	index = 1;
	result = EXIT_SUCCESS;
	if (!cmds->cmd[num_cmd].args[1])
		return (print_env(data));
	while (cmds->cmd[num_cmd].args[index])
	{
		if (is_valid_var_name(cmds->cmd[num_cmd].args[index]) == false)
		{
			error_msg_cmd("export", cmds->cmd[num_cmd].args[index],
				"not a valid identifier", EXIT_FAILURE);
			result = EXIT_FAILURE;
		}
		set_env_var(data, cmds->cmd[num_cmd].args[index], NULL);
		index++;
	}
	return (result);
}
