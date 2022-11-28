/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlins <rlins@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 10:08:27 by rlins             #+#    #+#             */
/*   Updated: 2022/11/27 10:47:03 by rlins            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	cmd_not_found(t_data *data, t_commands *cmds, char *cmd);
static void	debug_cmds(t_commands *cmds);
static int	execute_cmd(t_data *data, t_commands *cmds, char *cmd);
static int	exec_local_bin(t_data *data, t_commands *cmds, char *cmd);
static int	exec_path_var_bin(t_data *data, t_commands *cmds, char *cmd);
static bool	input_is_dir(char *cmd);

int	exec_handler(t_data *data) // TODO:Lins [create_children]
{
	t_commands	*cmds;

	//TODO:Lins: Freelá este cara aqui! (Talvez ele venha param.)
	cmds = (t_commands *)ft_calloc(1, sizeof(t_commands));

	// debug_cmds(cmds);
	cmds->num_cmds = 1; // TODO:Lins No loop da execução, calcular este valor

	int	i;

	i = 0;
	while (i < cmds->num_cmds)
	{
		/* TODO:Lins IMPORTANTE:
		 *-exec set follow-fork-mode child
		 */
		cmds->pid[0] = fork();
		if (cmds->pid[0] == -1)
			return (error_msg_cmd("fork", NULL, strerror(errno), EXIT_FAILURE));
		else if (cmds->pid == 0)
			// execute_cmd(data, cmds, "/bin/ls");
			execute_cmd(data, cmds, "./sh_test.sh");
		// TODO:Lins Harded code p/ teste
		i++;
	}

	return (1); // TODO
}

static int	execute_cmd(t_data *data, t_commands *cmds, char *cmd)
{
	int	status_code;

	// if (!cmds || !cmds->cmd)
	// 	exit_shell(data, error_msg_cmd("child", NULL,
	// 			"no command to execute", EXIT_FAILURE));
	// Commando com barra
	if (ft_strchr(cmd, '/') == NULL)
	{
		status_code = exec_path_var_bin(data, cmds, cmd);
		if (status_code != CMD_NOT_FOUND)
			exit_shell(data, status_code);
	}
	status_code = exec_local_bin(data, cmds, cmd);
	exit_shell(data, status_code);
	return (status_code);
}

static char	**apagar_parser_aqui(char **path)
{
	return (path);
}

/**
 * @brief Execute command with contain slash (/). So: Var binaries
 * @param data
 * @param cmds
 * @param cmd
 * @return int
 */
static int	exec_path_var_bin(t_data *data, t_commands *cmds, char *cmd)
{
	// TODO:Lins = Harded code p/ testes
	// char **teste = (char **)"/usr/bin/ls -l";
	// char **teste = (char **)"/usr/bin/ls -l";
	char **teste = (char **)"/usr/bin/ls -l";
	cmds->paths = apagar_parser_aqui(teste);
	if (!cmds->paths)
		return (CMD_NOT_FOUND);
	if (execve((char *)cmds->paths, data->command->args, data->env) == -1)
		error_msg_cmd("execve", NULL, strerror(errno), errno);
	return (EXIT_FAILURE);
}

// TODO:Lins - Remover este método daqui. Colocar em uma classe separada
static void	debug_cmds(t_commands *cmds)
{
	return;
	int	i;

	i = 0;
	while (cmds->cmds[i])
	{
		printf("Cmd %i: %s\n", i, cmds->cmds[i]);
		i++;
	}
	printf("\n\n");
	i = 0;
	while (cmds->paths[i])
	{
		printf("Paths %i: %s\n", i, cmds->paths[i]);
		i++;
	}
	printf("\n\n");
}

/** [OK] -  * TODO:Lins - Remover o char *cmd
 * @brief Responsible to handler the local executions. Local Directory,
 * file or in some path.
 * Ex: /bin/ls
 * @param data TypeDef in MiniShell
 * @param cmds TypeDef commands
 * @return int
 */
static int	exec_local_bin(t_data *data, t_commands *cmds, char *cmd)
{
	int	result_code;

	result_code = cmd_not_found(data, cmds, cmd);
	if (result_code != 0)
		return (result_code);
	if (execve(cmd, data->command->args, data->env) == -1)
		return (error_msg_cmd("execve", NULL, strerror(errno), errno));
	return (EXIT_FAILURE);
}

/** [OK] TODO:Lins - Remover o char *cmd.
 * @brief Verify if command is not found.
 * This will handler the possibles of the command was not found previously,
 * and return the msg and code of exit
 * @param data TypeDef in MiniShell
 * @param cmds
 * @return int
 */
static int	cmd_not_found(t_data *data, t_commands *cmds, char *cmd)
{
	if (ft_strchr(cmd, '/') == NULL
			&& get_env_var_index(data->env, "PATH") != -1)
		return (error_msg_cmd(cmd, NULL, "command not found", CMD_NOT_FOUND ));
	if (access(cmd, F_OK) != 0)
		return (error_msg_cmd(cmd, NULL, strerror(errno), CMD_NOT_FOUND ));
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
