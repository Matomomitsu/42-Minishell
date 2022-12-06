/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_truncate_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlins <rlins@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 11:42:36 by rlins             #+#    #+#             */
/*   Updated: 2022/12/06 07:18:14 by rlins            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	open_out_file(t_commands *cmds);

void	rd_truncate_handler(t_commands *cmds)
{
	init_io(cmds);
	open_out_file(cmds);
}

/**
 * @brief Open / create a output file.
* (Truncated to 0 if something exist in file),
* (if file does not exist, create)
* (read and write)
 * @param cmds Command STructure
 */
static void	open_out_file(t_commands *cmds)
{
	char **cmd_split;

	if(remove_old_file_ref(cmds->io, false) == false)
		return ;
	// TODO:Lins - Tirar index harded code.
	// Ver se ja nao tem este cara na estrutura.
	// Dar free nesta estrutura.
	cmd_split = split_args(cmds->cmd[0].redirections[0]);
	cmds->io->out_file = ft_strdup(cmd_split[1]);
	if (cmds->io->out_file && cmds->io->out_file[0] == '\0')
	{
		error_msg_cmd(cmd_split[1], NULL, "ambiguous redirect", false);
		return ;
	}
	cmds->io->fd_out = open(cmds->io->out_file, O_WRONLY | O_CREAT |
		O_TRUNC, 0664);
	if (cmds->io->fd_out == -1)
		error_msg_cmd(cmds->io->out_file, NULL, strerror(errno), false);
	free_ptr(cmd_split);
}
