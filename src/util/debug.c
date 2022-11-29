/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlins <rlins@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 09:57:56 by rlins             #+#    #+#             */
/*   Updated: 2022/11/29 11:17:59 by rlins            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	print_cmds(t_commands *cmds);
static void	print_operators(int operator);

/**
 * @brief Auxiliary method to expose all values of the structure
 * @param data
 * @param cmds
 */
void	debug_structs(t_data *data, t_commands *cmds)
{
	int	i;
	int	j;

	i = 0;
	printf("----Begin Debug (state Obj)----\n");
	printf("Nro num_cmds	: %i\n", cmds->num_cmds);
	print_operators(*cmds->operators);
	printf("Nro num_exec	: %i\n", cmds->num_exec);
	while (cmds->paths[i])
	{
		printf("Paths:	%s\n", cmds->paths[i]);
		i++;
	}
	i = 0;
	while (cmds->cmds[i])
	{
		printf("Cmds:	%s\n", cmds->cmds[i]);
		i++;
	}
	print_cmds(cmds);
	printf("----End Debug (state Obj)----\n");
}

static void	print_operators(int operator)
{
	if (operator == 1)
		printf("Operators		: OR\n");
	else if (operator == 2)
		printf("Operators		: AND\n");
	else if (operator == 3)
		printf("Operators		: PIPE\n");
}

/**
 * @brief Print array of commands
 * @param cmds
 */
static void	print_cmds(t_commands *cmds)
{
	int	i;
	int	j;

	i = 0;
	while (i < cmds->num_cmds)
	{
		printf("	cmd - cmd: %s\n", cmds->cmd[i].cmd);
		printf("	cmd - path: %s\n", cmds->cmd[i].path);
		printf("	cmd - exit_value: %i\n", cmds->exit_value);
		j = 0;
		while (cmds->cmd[i].redirections[j])
		{
			printf("	cmd - redirection: %s\n", cmds->cmd[i].redirections[j]);
			j++;
		}
		j = 0;
		while (cmds->cmd[i].args[j])
		{
			printf("	cmd - args: %s\n", cmds->cmd[i].args[j]);
			j++;
		}
	i++;
	}
}
