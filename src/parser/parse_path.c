/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtomomit <mtomomit@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 12:34:21 by rlins             #+#    #+#             */
/*   Updated: 2022/11/30 23:34:28 by mtomomit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_cmd_path(t_data *data, t_commands *cmds, int num_cmd)
{
	int		i;
	char	*cmd_comp;
	char	*cmd;

	cmd = ft_strdup("/");
	cmd = join_strs(cmd, cmds->cmd[num_cmd].args[0]);
	i = 0;
	while (cmds->paths[i])
	{
		cmd_comp = ft_strjoin(cmds->paths[i], cmd);
		if (access(cmd_comp, F_OK | X_OK) == 0)
		{
			free_ptr(cmd);
			return (cmd_comp);
		}
		free_ptr(cmd_comp);
		i++;
	}
	free_ptr(cmd);
	return (NULL);
}
