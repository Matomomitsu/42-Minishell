/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtomomit <mtomomit@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 08:54:58 by rlins             #+#    #+#             */
/*   Updated: 2022/12/22 21:08:04 by mtomomit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void			init_prompt(t_data *data);
static int			exec_cmd(t_data *data);
static bool			input_handler(t_data *data);

int	init(int argc, char **argv, char **envp)
{
	t_data	data;

	if (valid_args(argc, argv) == false || init_structure(&data, envp) == false)
		exit_shell(NULL, EXIT_FAILURE);
	init_prompt(&data);
	return (0);
}

/**
 * @brief Initialize prompt. Will read a input from user and wait the command.
 * Add a History of execution too.
 * @param data
 */
static void	init_prompt(t_data *data)
{
	char	*prompt;

	while (true)
	{
		signals_wait_cmd();
		prompt = get_prompt(data);
		data->user_input = readline(prompt);
		signals_run_cmd();
		free_ptr(prompt);
		if (input_handler(data))
			g_status_code = exec_cmd(data);
		else
			g_status_code = 0;
		free_data(data, false);
	}
	exit_shell(data, g_status_code);
}

/**
 * @brief Verify what type of command is coming
 * @param data
 */
static int	exec_cmd(t_data *data)
{
	t_commands	*cmds;
	int			status_code;

	cmds = (t_commands *)ft_calloc(1, sizeof(t_commands));
	cmds->exit_value = 0;
	status_code = 0;
	init_cmds(data, cmds);
	if (cmds->exit_value == 0)
	{
		init_cmd(data, cmds, 0);
		cmds->exit_value = exec_handler(data, cmds);
	}
	if (status_code == 0 && cmds->exit_value != 0)
		status_code = cmds->exit_value;
	free_cmds(cmds);
	return (status_code);
}

/**
 * @brief Fill the user_input variable.
 * Verify if something was put in console, or just a null value. Space must
 * give prompt back.
 * If there is nothin in input, means (Ctrl+D) signal called
 * @param data Data Minishel structure
 * @return boolean
 */
static bool	input_handler(t_data *data)
{
	if (!data->user_input)
	{
		ft_putendl_fd("exit", STDOUT);
		exit_shell(data, 0);
	}
	else if (data->user_input == NULL
		|| ft_strncmp(data->user_input, "\0", 1) == 0)
		return (false);
	else if (just_space_string(data->user_input) == true)
		return (false);
	add_history(data->user_input);
	return (true);
}
