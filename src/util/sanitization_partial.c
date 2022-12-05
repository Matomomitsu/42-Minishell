/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanitization_partial.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlins <rlins@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 09:23:18 by rlins             #+#    #+#             */
/*   Updated: 2022/12/05 09:45:20 by rlins            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	close_fds(t_commands *cmds, bool reset_io)
{
	if (cmds->io)
	{
		if (cmds->io->fd_in != -1)
			close(cmds->io->fd_in);
		if (cmds->io->fd_out != -1)
			close(cmds->io->fd_out);
		if (reset_io == true)
			restore_io(cmds->io);
	}
	close_pipe_fds(cmds, -1, true);
}

void	free_io(t_io *io)
{
	restore_io(io);
	if (io->in_file_name)
		free_ptr(io->in_file_name);
	if (io->out_file_name)
		free_ptr(io->out_file_name);
	if (io)
		free_ptr(io);
}
