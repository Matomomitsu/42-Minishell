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

static void	change_cmd(t_commands *cmds, int num_cmd)
{
	char			*temp_char;

	temp_char = rm_redirection(cmds->cmds[num_cmd]);
	free(cmds->cmds[num_cmd]);
	cmds->cmds[num_cmd] = (char *)malloc(ft_strlen(temp_char) * \
						sizeof(char) + 1);
	cmds->cmds[num_cmd][ft_strlen(temp_char)] = '\0';
	ft_strlcpy(cmds->cmds[num_cmd], temp_char, ft_strlen(temp_char) + 1);
	free(temp_char);
}

void	init_cmd(t_data *data, t_commands *cmds, int num_cmd)
{
	int	i;

	i = num_cmd;
	while (i < cmds->num_cmds)
	{
		cmds->cmd[i].redirections = handle_redirection(cmds->cmds[i]);
		change_cmd(cmds, i);
		if (cmds->cmds[i][0] && cmds->cmds[i][0] != ' ')
			find_dollar_sign(data, cmds, i);
		cmds->cmd[i].args = parser(cmds->cmds[i]);
		if (cmds->operators[i] && cmds->operators[i] == PIPE)
			i++;
		else
			i = cmds->num_cmds;
	}
}

void	init_single_cmd(t_data *data, t_commands *cmds, int num_cmd)
{
	int	i;

	i = 0;
	i = num_cmd;
	if (i < cmds->num_cmds)
	{
		cmds->cmd[i].redirections = handle_redirection(cmds->cmds[i]);
		change_cmd(cmds, i);
		if (cmds->cmds[i][0] && cmds->cmds[i][0] != ' ')
			find_dollar_sign(data, cmds, i);
		cmds->cmd[i].args = parser(cmds->cmds[i]);
	}
}
