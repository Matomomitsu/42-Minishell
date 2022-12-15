/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_special_pipe.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtomomit <mtomomit@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 08:49:25 by mtomomit          #+#    #+#             */
/*   Updated: 2022/12/15 10:56:52 by mtomomit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	check_parenthesis(t_commands *cmds)
{
	int	i;
	int	o;
	int	num_parenthesis;

	i = 0;
	num_parenthesis = 0;
	while (cmds->cmds[i])
	{
		printf("%s\n", cmds->cmds[i]);
		o = 0;
		while (cmds->cmds[i][o] && cmds->cmds[i][o] == ' ')
			o++;
		while (cmds->cmds[i][o++] == '(')
			num_parenthesis++;
		while (cmds->cmds[i][o])
		{
			if (cmds->cmds[i][o] == ')')
				num_parenthesis++;
			o++;
		}
		i++;
		printf("%i\n", num_parenthesis);
	}
	printf("%i\n", num_parenthesis);
	if (num_parenthesis % 2 == 0)
		return (num_parenthesis / 2);
	else
		return (0);
}

void	special_pipe(t_commands *cmds)
{
	int	num_special_pipes;
	int	i;

	num_special_pipes = 0;
	num_special_pipes = check_parenthesis(cmds) + 1;
	cmds->special_pipe = (t_special_pipe *)ft_calloc(num_special_pipes, \
					sizeof(t_commands));
	i = 0;
	while (i < num_special_pipes)
	{
		cmds->special_pipe[i].fd = (int *)ft_calloc(sizeof(int), 3);
		if (!cmds->special_pipe[i].fd)
			exit(6);
		if (pipe(cmds->special_pipe[i].fd) == -1)
			exit (7);
		i++;
	}
}