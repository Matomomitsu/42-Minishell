/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlins <rlins@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 11:24:31 by rlins             #+#    #+#             */
/*   Updated: 2022/12/09 11:36:39 by rlins            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	is_redirection_command(t_commands *cmds, int i)
{
	if (cmds->cmd[i].redirections[0])
		return (true);
	else
		return (false);
}

void	redirection_handler(t_data *data, t_commands *cmds, int j)
{
	int	i;
	int status_code;

	i = 0;
	status_code = -1;
	while (cmds->cmd[j].redirections[i])
	{
		if (ft_strncmp(cmds->cmd[j].redirections[i], ">>", 2) == 0)
			rd_output_handler(cmds, cmds->cmd[j].redirections[i], false);
		else if (ft_strncmp(cmds->cmd[j].redirections[i], "<<", 2) == 0)
			rd_heredoc(cmds, cmds->cmd[j].redirections[i]);
		else if (ft_strncmp(cmds->cmd[j].redirections[i], "<", 1) == 0)
			status_code = rd_input_handler(cmds, cmds->cmd[j].redirections[i]);
		else if (ft_strncmp(cmds->cmd[j].redirections[i], ">", 1) == 0)
			status_code = rd_output_handler(cmds, cmds->cmd[j].redirections[i], true);
		if (status_code != -1)
			break ;
		i++;
	}
}
