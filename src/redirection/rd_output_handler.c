/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_output_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtomomit <mtomomit@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 09:21:51 by rlins             #+#    #+#             */
/*   Updated: 2022/12/12 08:51:10 by mtomomit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	open_out_file(t_commands *cmds, char *file, bool trunc);

int	rd_output_handler(t_commands *cmds, char *red, bool trunc)
{
	char	**red_split;
	char	*result;
	int		status_code;

	red_split = ft_split(red, '>');
	result = ft_strtrim(red_split[0], " ");
	init_io(cmds);
	status_code = open_out_file(cmds, result, trunc);
	free_array_str(red_split);
	if (status_code != -1)
		cmds->io->error = true;
	else
		cmds->io->error = false;
	return (status_code);
}

/**
 * @brief Open / create a output file.
* (Truncated/append to 0 if something exist in file),
* (if file does not exist, create)
* (read and write)
 * @param cmds Command Structure
 * @param file File name
 * @param trunc Truncate or append
 */
static int	open_out_file(t_commands *cmds, char *file, bool trunc)
{
	cmds->io->out_file = file;
	if (cmds->io->out_file && cmds->io->out_file[0] == '\0')
		return(error_msg_cmd(file, NULL, "ambiguous redirect", false));
	if (trunc == true)
		cmds->io->fd_out = open(cmds->io->out_file, O_WRONLY | O_CREAT
				| O_TRUNC, 0664);
	else
		cmds->io->fd_out = open(cmds->io->out_file, O_WRONLY | O_CREAT
				| O_APPEND, 0664);
	if (cmds->io->fd_out == -1)
		return (error_msg_cmd(cmds->io->out_file, NULL, strerror(errno), false));
	return (-1);
}
