/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlins <rlins@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 11:24:31 by rlins             #+#    #+#             */
/*   Updated: 2022/12/06 18:38:30 by rlins            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	is_redirection_command(t_commands *cmds)
{
	if (cmds->cmd[0].redirections[0])
		return (true);
	else
		return (false);
}

void	redirection_handler(t_data *data, t_commands *cmds)
{
	int	i;

	i = 0;
	while (cmds->cmd[0].redirections[i])
	{
		if (ft_strncmp(cmds->cmd[0].redirections[i], ">>", 2) == 0)
			rd_output_handler(cmds, cmds->cmd[0].redirections[i], false);
		else if (ft_strncmp(cmds->cmd[0].redirections[i], "<<", 2) == 0)
			rd_heredoc(cmds, cmds->cmd[0].redirections[i]);
		else if (ft_strncmp(cmds->cmd[0].redirections[i], "<", 1) == 0)
			rd_input_handler(cmds, cmds->cmd[0].redirections[i]);
		else if (ft_strncmp(cmds->cmd[0].redirections[i], ">", 1) == 0)
			rd_output_handler(cmds, cmds->cmd[0].redirections[i], true);

		i++;
	}
}
