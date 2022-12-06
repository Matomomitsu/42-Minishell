/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_input_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlins <rlins@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 12:59:15 by rlins             #+#    #+#             */
/*   Updated: 2022/12/06 07:18:00 by rlins            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	open_in_file(t_commands *cmds);

void	rd_input_handler(t_commands *cmds)
{
	init_io(cmds);
	open_in_file(cmds);
}

/**
 * @brief TODO:Lins
 *
 * @param cmds
 */
static void	open_in_file(t_commands *cmds)
{
	char **cmd_split;

	if (remove_old_file_ref(cmds->io, false) == false)
		return ;
	// TODO:Lins - Tirar index harded code.
	// Ver se ja nao tem este cara na estrutura.
	// Dar free nesta estrutura.
	cmd_split = split_args(cmds->cmd[0].redirections[0]);
	cmds->io->in_file = ft_strdup(cmd_split[1]);
	if (cmds->io->in_file && cmds->io->in_file[0] == '\0')
	{
		error_msg_cmd(cmd_split[1], NULL, "ambiguous redirect", false);
		return ;
	}
	cmds->io->fd_in = open(cmds->io->in_file, O_RDONLY);
	if (cmds->io->fd_in == -1)
		error_msg_cmd(cmds->io->in_file, NULL, strerror(errno), false);
	free_ptr(cmd_split);
}
