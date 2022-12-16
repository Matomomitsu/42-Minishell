/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtomomit <mtomomit@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 10:08:27 by rlins             #+#    #+#             */
/*   Updated: 2022/12/16 12:37:35 by mtomomit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	exec_local_bin(t_data *data, t_commands *cmds, int num_cmd);
static int	exec_path_var_bin(t_data *data, t_commands *cmds, int num_cmd);
static int	wait_child(t_commands *cmds);

/* Debug Fork - -exec set follow-fork-mode child
*/
int	exec_handler(t_data *data, t_commands *cmds)
{
	int status_code;

	status_code = 0;
	while (cmds->num_exec < cmds->num_cmds)
	{
		if (cmds->cmd[cmds->num_exec].args[0] && \
			cmds->operators[cmds->num_exec] \
			!= PIPE && is_builtin_without_output(cmds))
		{
			g_status_code = call_builtin(data, cmds, 0);
			cmds->num_exec++;
		}
		else
		{
			status_code = exec_child(data, cmds, cmds->num_exec);
			g_status_code = wait_child(cmds);
			if (status_code != 0)
				g_status_code = status_code;
			if (cmds->num_exec < cmds->num_cmds)
				verify_operators(data, cmds, cmds->num_exec);
		}
	}
	return (g_status_code);
}

/**
 * @brief Wait the child process finish.
 * ECHILD - The process specified by the pid parameter does not exist.
 * WIFEXITED - Query status to see if a child process ended normally
 * WEXITSTATUS - Obtain exit status of a child process
 * @param t_data
 * @return int - Returns Child status.
 */
static int	wait_child(t_commands *cmds)
{
	int	i;
	int	status;
	int	save_status;

	close_exec_pipe_fds(cmds);
	i = -1;
	status = 0;
	save_status = 0;
	while (++i < cmds->num_exec - 1)
		waitpid(cmds->pid[i], NULL, 0);
	waitpid(cmds->pid[i], &save_status, 0);
	if (WIFEXITED(save_status))
		status = WEXITSTATUS(save_status);
	else if (WIFSIGNALED(save_status))
		status = WTERMSIG(save_status);
	else
		status = cmds->exit_value;
	return (status);
}

/**
 * @brief Check if command must be execute by variable path or if is a
 * local binary to execute
 * @param data Data Structure
 * @param cmds Cmds Structure
 * @param i - Index of command in execution this time
 * @return int
 */
int	execute_cmd(t_data *data, t_commands *cmds, int num_cmd)
{
	int	status_code;

	if (cmds->operators[0])
		set_pipe_fds(cmds, num_cmd);
	if (is_redirection_command(cmds, num_cmd)
		&& check_in_out_file(cmds->io) == false)
		exit_shell(data, EXIT_FAILURE);
	redirect_io(cmds->io, num_cmd);
	close_fds(cmds, false);
	if (is_builtin(cmds->cmd[num_cmd].args[0]))
		status_code = call_builtin(data, cmds, num_cmd);
	else
	{
		if (ft_strchr(cmds->cmd[num_cmd].args[0], '/') == NULL)
		{
			status_code = exec_path_var_bin(data, cmds, num_cmd);
			if (status_code != CMD_NOT_FOUND)
				free_exit_cmd(data, cmds, status_code);
		}
		status_code = exec_local_bin(data, cmds, num_cmd);
	}
	free_cmds(cmds);
	exit_shell(data, status_code);
	return (status_code);
}

/**
 * @brief Execute command with no slash (/). So: Var binaries.
 * Sample: ls -l.
 * This method will get the full path of the command, and execute it.
 * Sample: Change ls to '/usr/bin/ls'
 * @param data TypeDef in MiniShell
 * @param cmds TypeDef commands
 * @param cmd First Arg. Simple the command
 * @param i Index of cmd coming from structure
 * @return int - exit code
 */
static int	exec_path_var_bin(t_data *data, t_commands *cmds, int num_cmd)
{
	cmds->cmd[num_cmd].path = get_cmd_path(cmds, num_cmd);
	if (!cmds->cmd[num_cmd].path)
		return (CMD_NOT_FOUND);
	if (execve(cmds->cmd[num_cmd].path, cmds->cmd[num_cmd].args, data->env)
		== -1)
		error_msg_cmd("execve", NULL, strerror(errno), errno);
	return (EXIT_FAILURE);
}

/**
 * @brief Responsible to handler the local executions. Local Directory,
 * file or in some path.
 * Ex: /bin/ls or ./sh_test.sh
 * @param data TypeDef in MiniShell
 * @param cmds TypeDef commands
 * @return int - Result of execution
 */
static int	exec_local_bin(t_data *data, t_commands *cmds, int num_cmd)
{
	int	result_code;

	result_code = validate_cmd_not_found(data, cmds->cmd[num_cmd].args[0]);
	if (result_code != 0)
		return (result_code);
	if (execve(cmds->cmd[num_cmd].args[0], cmds->cmd[num_cmd].args, data->env)
		== -1)
		return (error_msg_cmd("execve", NULL, strerror(errno), errno));
	return (EXIT_FAILURE);
}
