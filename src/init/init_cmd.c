/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtomomit <mtomomit@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 16:26:01 by mtomomit          #+#    #+#             */
/*   Updated: 2022/11/25 16:26:01 by mtomomit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	find_dollar_sign(t_data *data, t_commands *cmds, int num_cmd)
{
	t_index_data	i_data;
	char			*temp_char;

	i_data.i = 0;
	while (cmds->cmds[num_cmd][i_data.i])
	{
		if (cmds->cmds[num_cmd][i_data.i] == '$')
		{
			temp_char = handle_env(&i_data, cmds->cmds[num_cmd], data);
			free(cmds->cmds[num_cmd]);
			cmds->cmds[num_cmd] = temp_char;
		}
		i_data.i++;
	}

}

void	init_cmd(t_data *data, t_commands *cmds)
{
	int	i;
	int	o;

	i = 0;
	cmds->cmd = ft_calloc(cmds->num_cmds, sizeof(t_cmd));
	while (i < cmds->num_cmds)
	{
		find_dollar_sign(data, cmds, i);
		cmds->cmd[i].args = parser(cmds->cmds[i], data);
		o = 0;
		while (cmds->cmd[i].args[o])
			printf("%s\n", cmds->cmd[i].args[o++]);
		i++;
	}
}
