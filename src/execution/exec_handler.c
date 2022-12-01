/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlins <rlins@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 10:08:27 by rlins             #+#    #+#             */
/*   Updated: 2022/12/01 11:11:59 by rlins            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	execute_cmd(t_data *data, t_commands *cmds, char *cmd, int i);
static int	exec_local_bin(t_data *data, t_commands *cmds, char *cmd);
static int	exec_path_var_bin(t_data *data, t_commands *cmds, char *cmd, int i);
static int	wait_child(t_data *t_data, t_commands *cmds);

/* Debug Fork - -exec set follow-fork-mode child
*/
int	exec_handler(t_data *data, t_commands *cmds)
{
	int	i;

	i = 0;
	while (i < cmds->num_cmds)
	{
		*cmds->pid = fork();
		if (*cmds->pid == -1)
			return (error_msg_cmd("fork", NULL, strerror(errno), EXIT_FAILURE));
		else if (*cmds->pid == 0)
			execute_cmd(data, cmds, *cmds->cmds, i);
		i++;
	}
	return (wait_child(data, cmds));
}

/**
 * @brief Wait the child process finish.
 * ECHILD - The process specified by the pid parameter does not exist.
 * WIFEXITED - Query status to see if a child process ended normally
 * WEXITSTATUS - Obtain exit status of a child process
 * @param t_data
 * @return int - Returns Child status.
 */
static int	wait_child(t_data *t_data, t_commands *cmds)
{
	pid_t	pid;
	int		status;
	int		save_status;

	close_pipe_fds(cmds, -1, true);
	pid = 0;
	status = 0;
	while (pid != -1 || errno != ECHILD)
	{
		pid = waitpid(-1, &status, 0);
		if (pid == *cmds->pid)
			save_status = status;
		continue ;
	}
	if (WIFEXITED(save_status))
		status = WEXITSTATUS(save_status);
	else if (WIFSIGNALED(save_status))
		status = WTERMSIG(save_status);
	else
		status = save_status;
	return (status);
}

/**
 * @brief Check if command must be execute by variable path or if is a
 * local binary to execute
 * @param data Data Structure
 * @param cmds Cmds Structure
 * @param cmd TODO: Provavelmente será descontinuado.
 * @param i - Index of command in execution this time
 * @return int
 */
static int	execute_cmd(t_data *data, t_commands *cmds, char *cmd, int i)
{
	int	status_code;

	if (*cmds->operators == PIPE)
	{
		set_pipe_fds(cmds, i);
		close_pipe_fds(cmds, i, true);
	}
	if (ft_strchr(cmd, '/') == NULL)
	{
		status_code = exec_path_var_bin(data, cmds, cmd, i);
		if (status_code != CMD_NOT_FOUND)
			exit_shell(data, status_code);
	}
	status_code = exec_local_bin(data, cmds, data->command->cmd);
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
static int	exec_path_var_bin(t_data *data, t_commands *cmds, char *cmd, int i)
{
	cmds->cmd[i].path = get_cmd_path(data, cmds, i);
	if (!cmds->cmd[i].path)
		return (CMD_NOT_FOUND);
	if (execve(cmds->cmd[i].path, cmds->cmd[i].args, data->env) == -1)
		error_msg_cmd("execve", NULL, strerror(errno), errno);
	return (EXIT_FAILURE);
}

/** TODO: Verificar se será necessário fazer a execução deste cara por index tb.
 * @brief Responsible to handler the local executions. Local Directory,
 * file or in some path.
 * Ex: /bin/ls or ./sh_test.sh
 * @param data TypeDef in MiniShell
 * @param cmds TypeDef commands
 * @return int - Result of execution
 */
static int	exec_local_bin(t_data *data, t_commands *cmds, char *cmd)
{
	int	result_code;

	result_code = validate_cmd_not_found(data, cmds, cmd);
	if (result_code != 0)
		return (result_code);
	if (execve(cmd, data->command->args, data->env) == -1)
		return (error_msg_cmd("execve", NULL, strerror(errno), errno));
	return (EXIT_FAILURE);
}
