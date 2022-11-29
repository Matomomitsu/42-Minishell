/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlins <rlins@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 10:08:27 by rlins             #+#    #+#             */
/*   Updated: 2022/11/29 19:14:47 by rlins            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	validate_cmd_not_found(t_data *data, t_commands *cmds, char *cmd);
static int	execute_cmd(t_data *data, t_commands *cmds, char *cmd);
static int	exec_local_bin(t_data *data, t_commands *cmds, char *cmd);
static int	exec_path_var_bin(t_data *data, t_commands *cmds, char *cmd);
static bool	input_is_dir(char *cmd);
static int	wait_child(t_data *t_data, t_commands *cmds);

/* Debug Fork - -exec set follow-fork-mode child
*/
int	exec_handler(t_data *data, t_commands *cmds)
{
	int	i;

	// debug_structs(data, cmds);
	i = 0;
	while (i < cmds->num_cmds)
	{
		*cmds->pid = fork();
		if (*cmds->pid == -1)
			return (error_msg_cmd("fork", NULL, strerror(errno), EXIT_FAILURE));
		else if (*cmds->pid == 0)
			execute_cmd(data, cmds, *cmds->cmds);
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
	else if (WISIGNALED(save_status))
		status = WTERMSIG(save_status);
	else
		status = save_status;
	return (status);
}

/** [OK]
 * @brief Check if command must be execute by variable path or if is a
 * local binary to execute
 * @param data
 * @param cmds
 * @param cmd
 * @return int
 */
static int	execute_cmd(t_data *data, t_commands *cmds, char *cmd)
{
	int	status_code;

	if (ft_strchr(cmd, '/') == NULL)
	{
		status_code = exec_path_var_bin(data, cmds, cmd);
		if (status_code != CMD_NOT_FOUND)
			exit_shell(data, status_code);
	}
	status_code = exec_local_bin(data, cmds, data->command->cmd);
	exit_shell(data, status_code);
	return (status_code);
}

/** [OK]
 * @brief Execute command with no slash (/). So: Var binaries.
 * Sample: ls -l.
 * This method will get the full path of the command, and execute it.
 * Sample: Change ls to '/usr/bin/ls'
 * @param data TypeDef in MiniShell
 * @param cmds TypeDef commands
 * @param cmd First Arg. Simple the command
 * @return int - exit code
 */
static int	exec_path_var_bin(t_data *data, t_commands *cmds, char *cmd)
{
	cmds->cmd[0].path = get_cmd_path(data, cmds);
	if (!cmds->cmd[0].path)
		return (CMD_NOT_FOUND);
	if (execve(cmds->cmd[0].path, data->command->args, data->env) == -1)
		error_msg_cmd("execve", NULL, strerror(errno), errno);
	return (EXIT_FAILURE);
}

/** [OK]
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

/** [OK]
 * @brief Verify if command is not found.
 * This will handler the possibles of the command was not found previously,
 * and return the msg and code of exit
 * @param data TypeDef in MiniShell
 * @param cmds
 * @return int
 */
static int	validate_cmd_not_found(t_data *data, t_commands *cmds, char *cmd)
{
	if (ft_strchr(cmd, '/') == NULL
		&& get_env_var_index(data->env, "PATH") != -1)
		return (error_msg_cmd(cmd, NULL, "command not found", CMD_NOT_FOUND));
	if (access(cmd, F_OK) != 0)
		return (error_msg_cmd(cmd, NULL, strerror(errno), CMD_NOT_FOUND));
	else if (input_is_dir(cmd))
		return (error_msg_cmd(cmd, NULL, "is a directory", CMD_NOT_EXEC));
	else if (access(cmd, X_OK) != 0)
		return (error_msg_cmd(cmd, NULL, strerror(errno), CMD_NOT_EXEC));
}

/** [OK]
 * @brief Verify if the command passed is a directory. Necessary to throw the
 * correct message
 * @param cmd Command to check
 * @return true - Input passed is a dir
 * @return false - Itś not a dir
 */
static bool	input_is_dir(char *cmd)
{
	struct stat	stat_buf;

	stat(cmd, &stat_buf);
	return (S_ISDIR(stat_buf.st_mode));
}
