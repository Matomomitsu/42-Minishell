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

static void	init_pipe(t_commands *cmds, int num_cmd)
{
	cmds->cmd[num_cmd].pipe_fd = (int *)ft_calloc(sizeof(int), 3);
	if (!cmds->cmd[num_cmd].pipe_fd)
		exit(6);
	if (pipe(cmds->cmd[num_cmd].pipe_fd) == -1)
		exit (7);
}

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

void	init_cmd(t_data *data, t_commands *cmds)
{
	int	i;
	int	o;

	i = 0;
	printf("%i\n", cmds->num_cmds);
	while (i < cmds->num_cmds)
	{
		cmds->cmd[i].redirections = handle_redirection(cmds->cmds[i]);
		o = 0;
		while (cmds->cmd[i].redirections[o])
			printf("%s\n", cmds->cmd[i].redirections[o++]);
		change_cmd(cmds, i);
		printf("%s\n", cmds->cmds[i]);
		find_dollar_sign(data, cmds, i);
		cmds->cmd[i].args = parser(cmds->cmds[i]);
		o = 0;
		while (cmds->cmd[i].args[o])
			printf("%s\n", cmds->cmd[i].args[o++]);
		init_pipe(cmds, i);
		i++;
	}
}
