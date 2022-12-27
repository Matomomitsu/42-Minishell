/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_dollar_sign.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtomomit <mtomomit@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:31:18 by mtomomit          #+#    #+#             */
/*   Updated: 2022/11/28 16:31:18 by mtomomit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	check_type(char c)
{
	if (c != '?')
		return (ft_isalnum(c) || c == '_');
	else
		return (1);
}

static void	handle_dollar(t_index_data *i_data, t_commands *cmds, \
					int num_cmd, t_data *data)
{
	char	*temp;

	temp = handle_env(i_data, cmds->cmds[num_cmd], data);
	free(cmds->cmds[num_cmd]);
	cmds->cmds[num_cmd] = (char *)malloc(ft_strlen(temp) * \
						sizeof(char) + 1);
	cmds->cmds[num_cmd][ft_strlen(temp)] = '\0';
	ft_strlcpy(cmds->cmds[num_cmd], temp, ft_strlen(temp) + 1);
	free(temp);
}

static void	handle_quotes(t_index_data *aux, t_commands *cmds, \
					int n, t_data *data)
{
	if (cmds->cmds[n][aux->i++] == '\'')
		while (cmds->cmds[n][aux->i] != '\'')
			aux->i++;
	else
	{
		while (cmds->cmds[n][aux->i] != '\"')
		{
			if (cmds->cmds[n][aux->i] == '$' && cmds->cmds[n][aux->i + 1]
				&& check_type(cmds->cmds[n][aux->i + 1]))
				handle_dollar(aux, cmds, n, data);
			else
				aux->i++;
		}
	}
}

void	find_dollar_sign(t_data *data, t_commands *cmds, int n)
{
	t_index_data	aux;

	aux.i = 0;
	find_export_cmd(cmds, n);
	while (cmds->cmds[n][aux.i])
	{
		if (cmds->cmds[n][aux.i] == '$' && cmds->cmds[n][aux.i + 1]
			&& check_type(cmds->cmds[n][aux.i + 1]))
			handle_dollar(&aux, cmds, n, data);
		if (cmds->cmds[n][aux.i] == '\'' || \
			cmds->cmds[n][aux.i] == '\"')
			handle_quotes(&aux, cmds, n, data);
		if (cmds->cmds[n][aux.i] == '$')
		{
			if (cmds->cmds[n][aux.i + 1] &&
				!check_type(cmds->cmds[n][aux.i + 1]))
				aux.i++;
			if (!cmds->cmds[n][aux.i + 1])
				aux.i++;
		}
		else if (cmds->cmds[n][aux.i] && cmds->cmds[n][aux.i] != '$')
			aux.i++;
	}
}
