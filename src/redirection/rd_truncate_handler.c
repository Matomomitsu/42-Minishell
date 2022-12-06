/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_truncate_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlins <rlins@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 11:42:36 by rlins             #+#    #+#             */
/*   Updated: 2022/12/06 08:22:49 by rlins            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	open_out_file(t_commands *cmds, char *file);

void	rd_truncate_handler(t_commands *cmds, char *red)
{
	char **red_split;

	red_split = split_args(red);

	init_io(cmds);
	open_out_file(cmds, red_split[1]);

	free_ptr(red_split);
}

/**
 * @brief Open / create a output file.
* (Truncated to 0 if something exist in file),
* (if file does not exist, create)
* (read and write)
 * @param cmds Command Structure
 */
static void	open_out_file(t_commands *cmds, char *file)
{
	if(remove_old_file_ref(cmds->io, false) == false)
		return ;
	cmds->io->out_file = ft_strdup(file);
	if (cmds->io->out_file && cmds->io->out_file[0] == '\0')
	{
		error_msg_cmd(file, NULL, "ambiguous redirect", false);
		return ;
	}
	cmds->io->fd_out = open(cmds->io->out_file, O_WRONLY | O_CREAT |
		O_TRUNC, 0664);
	if (cmds->io->fd_out == -1)
		error_msg_cmd(cmds->io->out_file, NULL, strerror(errno), false);
}
