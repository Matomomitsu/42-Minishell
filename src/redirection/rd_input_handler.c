/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_input_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlins <rlins@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 12:59:15 by rlins             #+#    #+#             */
/*   Updated: 2022/12/07 13:02:56 by rlins            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	open_in_file(t_commands *cmds, char *file);

void	rd_input_handler(t_commands *cmds, char *red)
{
	char	**red_split;
	char	*result;

	remove_quotes(red);
	red_split = ft_split(red, '<');
	result = ft_strtrim(red_split[0], " ");
	init_io(cmds);
	open_in_file(cmds, result);
	free_array_str(red_split);
}

/**
 * @brief Open infile, update the file descriptor. Verify errors to open the
 * file
 * @param cmds Commands structure
 */
static void	open_in_file(t_commands *cmds, char *file)
{
	cmds->io->in_file = file;
	if (cmds->io->in_file && cmds->io->in_file[0] == '\0')
	{
		error_msg_cmd(file, NULL, "ambiguous redirect", false);
		return ;
	}
	cmds->io->fd_in = open(cmds->io->in_file, O_RDONLY);
	if (cmds->io->fd_in == -1)
		error_msg_cmd(cmds->io->in_file, NULL, strerror(errno), false);
}
