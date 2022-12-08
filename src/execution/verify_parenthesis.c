/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_parenthesis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtomomit <mtomomit@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 10:04:17 by mtomomit          #+#    #+#             */
/*   Updated: 2022/12/08 19:17:52 by mtomomit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	verify_parenthesis_or(t_data *data, t_commands *cmds, int num_cmd)
{
	int	i;

	i = num_cmd;
	init_single_cmd(data, cmds, i);
	if (ft_strchr(cmds->cmds[i], '('))
		while (!ft_strchr(cmds->cmds[i], ')'))
		{
			i++;
			init_single_cmd(data, cmds, i);
		}
	i++;
	if (g_status_code == 0)
	{
		cmds->num_exec = i;
		init_cmd(data, cmds, i);
	}
}

static void	verify_parenthesis_and(t_data *data, t_commands *cmds, int num_cmd)
{
	int	i;

	i = num_cmd;
	init_single_cmd(data, cmds, num_cmd);
	if (ft_strchr(cmds->cmds[i], '('))
		while (!ft_strchr(cmds->cmds[i], ')'))
		{
			i++;
			init_single_cmd(data, cmds, i);
		}
	i++;
	if (g_status_code != 0)
	{
		cmds->num_exec = i;
		init_cmd(data, cmds, i);
	}
}

void	verify_operators(t_data *data, t_commands *cmds, int num_cmd)
{
	int	i;

	if (cmds->operators[num_cmd - 1] == OR)
		verify_parenthesis_or(data, cmds, num_cmd);
	if (cmds->operators[num_cmd - 1] == AND)
		verify_parenthesis_and(data, cmds, num_cmd);
}
