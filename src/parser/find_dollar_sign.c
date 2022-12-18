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

static void	handle_quotes(t_index_data *i_data, t_commands *cmds, \
					int num_cmd, t_data *data)
{
	char	*temp;

	if (cmds->cmds[num_cmd][i_data->i++] == '\'')
		while (cmds->cmds[num_cmd][i_data->i] != '\'')
			i_data->i++;
	else
	{
		while (cmds->cmds[num_cmd][i_data->i] != '\"')
		{
			if (cmds->cmds[num_cmd][i_data->i] == '$')
			{
				temp = handle_env(i_data, cmds->cmds[num_cmd], data);
				free(cmds->cmds[num_cmd]);
				cmds->cmds[num_cmd] = (char *)malloc(ft_strlen(temp) * \
							sizeof(char) + 1);
				cmds->cmds[num_cmd][ft_strlen(temp)] = '\0';
				ft_strlcpy(cmds->cmds[num_cmd], temp, ft_strlen(temp) + 1);
				free(temp);
			}
			else
				i_data->i++;
		}
	}
}

void	find_dollar_sign(t_data *data, t_commands *cmds, int num_cmd)
{
	t_index_data	i_data;
	char			*temp;

	i_data.i = 0;
	find_export_cmd(cmds, num_cmd);
	while (cmds->cmds[num_cmd][i_data.i])
	{
		if (cmds->cmds[num_cmd][i_data.i] == '$')
		{
			temp = handle_env(&i_data, cmds->cmds[num_cmd], data);
			free(cmds->cmds[num_cmd]);
			cmds->cmds[num_cmd] = (char *)malloc(ft_strlen(temp) * \
						sizeof(char) + 1);
			cmds->cmds[num_cmd][ft_strlen(temp)] = '\0';
			ft_strlcpy(cmds->cmds[num_cmd], temp, ft_strlen(temp) + 1);
			free(temp);
		}
		if (cmds->cmds[num_cmd][i_data.i] == '\'' || \
			cmds->cmds[num_cmd][i_data.i] == '\"')
			handle_quotes(&i_data, cmds, num_cmd, data);
		if (cmds->cmds[num_cmd][i_data.i] && \
			cmds->cmds[num_cmd][i_data.i] != '$')
			i_data.i++;
	}
}
