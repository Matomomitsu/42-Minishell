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

void	find_dollar_sign(t_data *data, t_commands *cmds, int num_cmd)
{
	t_index_data	i_data;
	char			*temp_char;

	i_data.i = 0;
	find_export_cmd(cmds, num_cmd, data);
	while (cmds->cmds[num_cmd][i_data.i])
	{
		if (cmds->cmds[num_cmd][i_data.i] == '$')
		{
			temp_char = handle_env(&i_data, cmds->cmds[num_cmd], data);
			free(cmds->cmds[num_cmd]);
			cmds->cmds[num_cmd] = (char *)malloc(ft_strlen(temp_char) * \
						sizeof(char) + 1);
			cmds->cmds[num_cmd][ft_strlen(temp_char)] = '\0';
			ft_strlcpy(cmds->cmds[num_cmd], temp_char, ft_strlen(temp_char) + 1);
			free(temp_char);
		}
		if (cmds->cmds[num_cmd][i_data.i] == '\'')
			while (cmds->cmds[num_cmd][i_data.i++] != '\'')
				;
		if (cmds->cmds[num_cmd][i_data.i])
			i_data.i++;
	}
}
