/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlins <rlins@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 08:54:58 by rlins             #+#    #+#             */
/*   Updated: 2022/11/23 07:46:49 by rlins            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static bool			valid_args(int argc);
static void			init_prompt(t_data *data);
static int			exec_cmd(t_data *data);
static t_command	*init_cmd_args(t_data *data, char **args);

int	init(int argc, char **argv, char **envp)
{
	t_data	data;

	if (valid_args(argc) == false || init_structure(&data, envp) == false)
		exit_shell(NULL, EXIT_FAILURE);
	init_prompt(&data);
	return (0);
}

/**
 * @brief Validate number of arguments of Mini-shell
 * @param argc Argument Counts
 * @return true - Valid
 * @return false - Failed
 */
static bool	valid_args(int argc)
{
	if (argc > 1)
	{
		ft_putstr_fd(INV_ARGS, STDOUT_FILENO);
		return (false);
	}
	return (true);
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
		signals_handler();
		prompt = get_prompt(data);
		data->user_input = readline(prompt);
		free_ptr(prompt);
		if (data->user_input)
		{
			add_history(data->user_input);
		}
		else
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			exit(1);
		}
		g_status_code = exec_cmd(data);
		free_data(data, false);
	}
	exit_shell(data, g_status_code);
}

/** TODO: Provavelmente este método ficará em outra classe apartada
 * TODO: Provavelmente ele receberá outros métodos auiliares para as
 * diferentes execuções que teremos no minishell
 * @brief Verify what type of command is comming
 * @param data
 */

static int	exec_cmd(t_data *data)
{
	t_commands	*cmds;
	char		**args;
	int			status_code;

	cmds = (t_commands *)ft_calloc(1, sizeof(t_commands));
	cmds->exit_value = 0;
	init_cmds(data, cmds);
	if (cmds->exit_value == 0)
	{
		args = split_args(data->user_input);
		data->command = init_cmd_args(data, args);
		if (is_builtin(data->command->cmd))
			status_code = call_builtin(data);
	}
	status_code = cmds->exit_value;
	free_cmds(cmds);
	return (status_code);
}

/**
 * @brief Initialize object command. Will receive the command .
 * 'First token' will be the command. The others will be the args
 * @param command Object Structure Command
 * @param args All the token passed in command
 */
static t_command	*init_cmd_args(t_data *data, char **args)
{
	t_command	*cmd;

	cmd = (t_command *)malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	ft_memset(cmd, 0, sizeof(t_command));
	cmd->cmd = args[0];
	cmd->args = args;
	cmd->args_count = args_count(args);
	return (cmd);
}
