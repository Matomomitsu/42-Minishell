/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlins <rlins@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 10:34:07 by rlins             #+#    #+#             */
/*   Updated: 2022/12/22 11:58:30 by rlins            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	get_delimiter(char *red, t_io *io);
static bool	exit_heredoc_prompt(char **user_input, t_io *io);
static bool	heredoc_prompt(t_io *io);

void	rd_heredoc(t_commands *cmds, char *red)
{
	t_io	*io;

	init_io(cmds);
	io = cmds->io;
	io->in_file = ".tmp_heredoc";
	get_delimiter(red, io);
	if (heredoc_prompt(io))
		io->fd_in = open(io->in_file, O_RDONLY);
	else
		io->fd_in = -1;
}

/**
 * @brief Will update Heredoc_delimiter, accord passed in prompt, before <<
 * @param red Redirection input. Ex: << EOF
 * @param io IO Structure
 */
static void	get_delimiter(char *red, t_io *io)
{
	char	**red_split;
	char	*result;

	red_split = ft_split(red, '<');
	result = ft_strtrim(red_split[0], " ");
	io->heredoc_delimiter = result;
	free_array_str(red_split);
}

/**
 * @brief Responsible to open a temp file and start to work with the new
 * prompt with user input
 * @param io structure
 * @return false
 */
static bool	heredoc_prompt(t_io *io)
{
	int		fd;
	char	*user_input;

	fd = open(io->in_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	user_input = NULL;
	while (true)
	{
		signals_wait_cmd();
		user_input = readline("heredoc> ");
		signals_run_cmd();
		if (exit_heredoc_prompt(&user_input, io) == true)
			break ;
		ft_putendl_fd(user_input, fd);
		free_ptr(user_input);
	}
	close(fd);
	free_ptr(user_input);
	return (true);
}

/**
 * @brief Handle the exit of prompt. Try found some gaps in user input (first
 * verification) and identify the delimiter input to exit the Heredoc. Otherwise
 * keep in loop
 * @param user_input User input
 * @param io IO structure
 * @return bool. true = Exit heredoc. False - Keep in loop
 */
static bool	exit_heredoc_prompt(char **user_input, t_io *io)
{
	if (*user_input == NULL)
	{
		error_msg_cmd("here-doc", "end-of-file: expected",
			io->heredoc_delimiter, true);
		return (true);
	}
	if (ft_strncmp(*user_input, io->heredoc_delimiter,
			ft_strlen(io->heredoc_delimiter)) == 0)
	{
		return (true);
	}
	return (false);
}
