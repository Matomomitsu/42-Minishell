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
			cmds->cmds[num_cmd] = ft_realloc(cmds->cmds[num_cmd], \
				ft_strlen(temp_char) + 1);
			ft_strlcpy(cmds->cmds[num_cmd], temp_char, ft_strlen(temp_char) + \
					1);
			free(temp_char);
		}
		if (cmds->cmds[num_cmd][i_data.i] == '\'')
			while (cmds->cmds[num_cmd][++i_data.i] != '\'')
				;
		if (cmds->cmds[num_cmd][i_data.i])
			i_data.i++;
	}
}

static void	init_pipe(t_commands *cmds, int num_cmd)
{
	cmds->cmd[num_cmd].pipe_fd = (int *)ft_calloc(sizeof(int), 3);
		if (!cmds->cmd[num_cmd].pipe_fd)
			exit(6);
		if (pipe(cmds->cmd[num_cmd].pipe_fd) == -1)
			exit (7);
}

char	**get_cmd_args()
{

}

void	init_cmd(t_data *data, t_commands *cmds)
{
	int	i;
	int	o;

	i = 0;
	while (i < cmds->num_cmds)
	{
		find_dollar_sign(data, cmds, i);
		cmds->cmd[i].args = parser(cmds->cmds[i], data);
		cmds->cmd[i].cmd_args = get_cmd_args(cmds);
		o = 0;
		while (cmds->cmd[i].args[o])
			printf("%s\n", cmds->cmd[i].args[o++]);
		init_pipe(cmds, i);
		i++;
	}
}
