/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtomomit <mtomomit@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 12:34:21 by rlins             #+#    #+#             */
/*   Updated: 2022/12/20 14:46:20 by mtomomit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_cmd_path(t_commands *cmds, int index)
{
	int		i;
	char	*cmd_comp;
	char	*cmd;

	cmd = ft_strdup("/");
	cmd = join_strs(cmd, cmds->cmd[index].args[0]);
	i = 0;
	if (cmds->paths)
	{
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
	}
	free_ptr(cmd);
	return (NULL);
}
