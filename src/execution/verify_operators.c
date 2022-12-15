/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_operators.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtomomit <mtomomit@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 10:04:17 by mtomomit          #+#    #+#             */
/*   Updated: 2022/12/15 13:56:46 by mtomomit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	verify_or(t_data *data, t_commands *cmds, int num_cmd)
{
	int	i;

	i = num_cmd;
	if (g_status_code == 0)
	{
		while (cmds->operators[i - 1] && cmds->operators[i - 1] == OR)
		{
			init_single_cmd(data, cmds, i);
			i++;
		}
		cmds->num_exec = i;
		printf("%i\n", cmds->num_exec);
		init_cmd(data, cmds, i);
	}
	else
		init_cmd(data, cmds, num_cmd);
}

static void	verify_and(t_data *data, t_commands *cmds, int num_cmd)
{
	int	i;

	i = num_cmd;
	if (g_status_code != 0)
	{
		while (cmds->operators[i - 1] && cmds->operators[i - 1] == AND)
		{
			init_single_cmd(data, cmds, i);
			i++;
		}
		cmds->num_exec = i;
		printf("%i\n", cmds->num_exec);
		init_cmd(data, cmds, i);
	}
	else
		init_cmd(data, cmds, num_cmd);
}

void	verify_operators(t_data *data, t_commands *cmds, int num_cmd)
{
	if (cmds->operators[num_cmd - 1] == OR)
		verify_or(data, cmds, num_cmd);
	if (cmds->operators[num_cmd - 1] == AND)
		verify_and(data, cmds, num_cmd);
}
