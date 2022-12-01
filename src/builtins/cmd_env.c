/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtomomit <mtomomit@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 08:51:53 by rlins             #+#    #+#             */
/*   Updated: 2022/12/01 02:54:15 by mtomomit         ###   ########.fr       */
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
	if (!env[o])
		return (NULL);
	temp_char = malloc(sizeof(char) * ft_strlen(env) + 3);
	temp_char[ft_strlen(env) + 2] = '\0';
	i = 0;
	o = 0;
	while (env[o] != '=')
		temp_char[i++] = env[o++];
	temp_char[i++] = env[o++];
	temp_char[i++] = '"';
	while (env[o] && env[o] != ' ')
		temp_char[i++] = env[o++];
	temp_char[i++] = '"';
	while (env[o])
		temp_char[i++] = env[o++];
	return (temp_char);
}

int	cmd_env(t_data *data, bool exp_no_arg, t_commands *cmds, int num_cmd)
{
	int		i;
	char	*temp_char;

	if (cmds->cmd[num_cmd].args[1])
		return (error_msg_cmd("env", NULL, "too many arguments", STDERR));
	if (!data->env)
		return (EXIT_FAILURE);
	i = 0;
	while (data->env[i])
	{
		if (exp_no_arg == true)
		{
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
			temp_char = add_quotes(data->env[i]);
			if (temp_char)
				ft_putendl_fd(temp_char, STDOUT_FILENO);
			else
				ft_putendl_fd(data->env[i], STDOUT_FILENO);
			free(temp_char);
		}
		else
			ft_putendl_fd(data->env[i], STDOUT_FILENO);
		i++;
	}
	return (EXIT_SUCCESS);
}
