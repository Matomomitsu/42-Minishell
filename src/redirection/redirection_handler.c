/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlins <rlins@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 11:24:31 by rlins             #+#    #+#             */
/*   Updated: 2022/12/06 08:49:06 by rlins            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	is_redirection_command(t_commands *cmds)
{
	if (cmds->cmd[0].redirections[0])
		return (true);
	else
		return (false);
}

void	redirection_handler(t_data *data, t_commands *cmds)
{
	int	i;

	i = 0;
	while (cmds->cmd[0].redirections[i])
	{
		if (ft_strncmp(cmds->cmd[0].redirections[i], ">", 1) == 0)
			rd_truncate_handler(cmds, cmds->cmd[0].redirections[i]);
		else if (ft_strncmp(cmds->cmd[0].redirections[i], "<", 1) == 0)
			rd_input_handler(cmds, cmds->cmd[0].redirections[i]);
		i++;
	}
}

bool	remove_old_file_ref(t_io *io, bool in_file)
{
	if (in_file == true && io->in_file)
	{
		if (io->fd_in == -1 || (io->out_file && io->fd_out == -1))
			return (false);
		//TODO:Lins
		// if (io->heredoc_delimiter != NULL)
		// {
		// 	free_ptr(io->heredoc_delimiter);
		// 	io->heredoc_delimiter = NULL;
		// 	unlink(io->infile);
		// }
		free_ptr(io->in_file);
		close(io->fd_in);
	}
	else if (in_file == false && io->out_file)
	{
		if (io->fd_out == -1 || (io->in_file && io->fd_in == -1))
			return (false);
		free_ptr(io->out_file);
		close(io->fd_out);
	}
	return (true);
}
