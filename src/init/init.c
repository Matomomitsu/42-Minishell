/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlins <rlins@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 08:54:58 by rlins             #+#    #+#             */
/*   Updated: 2022/11/18 09:36:41 by rlins            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static bool			valid_args(int argc);
static void			init_prompt(t_data *data);
static void			exec_cmd(t_data *data);
static t_command	*init_cmd_args(t_data *data, char **args);

int	init(int argc, char **argv, char **envp)
{
	t_data	data;

	if (valid_args(argc) == false || init_structure(&data, envp) == false)
		exit_shell(EXIT_FAILURE);
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
 * TODO: Melhorar o Free que estou dando só no userinput. Tem que ter 1 método
 * 'clean all'
 */
static void	init_prompt(t_data *data)
{
	while (true)
	{
		signals_handler();
		data->user_input = readline("@MINI-SHELL>$");
		if (data->user_input)
		{
			add_history(data->user_input);
		}
		else
		{
			ft_putstr_fd("exit\n", STDOUT_FILENO);
			exit(1);
		}
		exec_cmd(data);
		free (data->user_input);
	}
	rl_clear_history();
}

/** TODO: Provavelmente este método ficará em outra classe apartada
 * TODO: Provavelmente ele receberá outros métodos auiliares para as
 * diferentes execuções que teremos no minishell
 * @brief Verify what type of command is comming
 * @param data
 */
static void	exec_cmd(t_data *data)
{
	t_commands	*cmds;
	char		**args;

	data->old_exit_value = data->exit_value;
	data->exit_value = 0;
	cmds = ft_calloc(1 , sizeof(cmds));
	cmds->cmds = lexer(data->user_input, data);
	if (data->exit_value == 0)
	{
		args = split_args(data->user_input);
		data->command = init_cmd_args(data, args);
		if (is_builtin(data->command->cmd))
			call_builtin(data);
	}
	free(cmds);
}

/**
 * @brief Initialize object command. Will receive the command .
 * 'First token' will be the command. The others will be the args
 * @param command Object Structure Command
 * @param args All the token passed in command
 * TODO: Must free the variable cmd
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
	return (cmd);
}
