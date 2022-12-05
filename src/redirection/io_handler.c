/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_handler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlins <rlins@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 08:05:58 by rlins             #+#    #+#             */
/*   Updated: 2022/12/05 09:28:25 by rlins            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	redirect_io(t_io *io)
{
	io->std_in_bkp = dup(STDIN_FILENO);
	if (io->std_in_bkp == -1)
		error_msg_cmd("dup", "std-in-bkp", strerror(errno), false);
	io->std_out_bkp = dup(STDOUT_FILENO);
	if (io->std_out_bkp == -1)
		error_msg_cmd("dup", "std-out-bkp", strerror(errno), false);
	if (io->fd_in != -1)
		if (dup2(io->fd_in, STDIN_FILENO) == -1)
			error_msg_cmd("dup2", io->in_file_name, strerror(errno),
				EXIT_FAILURE);
	if (io->fd_out != -1)
		if (dup2(io->fd_out, STDOUT_FILENO) == -1)
			error_msg_cmd("dup2", io->out_file_name, strerror(errno),
				EXIT_FAILURE);
}

void	restore_io(t_io *io)
{

}
