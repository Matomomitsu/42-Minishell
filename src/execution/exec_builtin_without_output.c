/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_without_output.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtomomit <mtomomit@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 01:11:22 by mtomomit          #+#    #+#             */
/*   Updated: 2022/12/23 09:02:04 by mtomomit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	cd_special_case(t_commands *cmds, t_data *data)
{
	char	*path;

	cmds->pid[0] = fork();
	if (cmds->pid[0] == -1)
		error_msg_cmd("fork", NULL, strerror(errno), EXIT_FAILURE);
	else if (cmds->pid[0] == 0)
	{
		if (is_redirection_command(cmds, 0)
			&& check_in_out_file(cmds->io, cmds, true) == false)
				exit_shell(data, EXIT_FAILURE);
		redirect_io(cmds->io, 0);
		close_fds(cmds, false);
		path = get_env_var_value(data->env, PWD);
		if (!path)
			;
		else
			ft_putendl_fd(path, STDOUT);
		free(path);
		free_cmds(cmds);
		exit_shell(data, 0);
	}
}

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
		status = 128 + WTERMSIG(save_status);
	else
		status = cmds->exit_value;
	return (status);
}

void	exec_builtin_without_output(t_commands *cmds, t_data *data)
{
	if (is_redirection_command(cmds, cmds->num_exec))
		redirection_handler(cmds, cmds->num_exec);
	cmds->num_exec++;
	if (is_redirection_command(cmds, 0)
		&& check_in_out_file(cmds->io, cmds, false) == false)
		g_status_code = 1;
	else
	{
		g_status_code = call_builtin(data, cmds, 0);
		if (ft_strncmp(cmds->cmd[0].args[0], "cd", 3) == 0 &&
			ft_strncmp(cmds->cmd[0].args[1], "-", 2) == 0 &&
			g_status_code == 0)
			{
				cd_special_case(cmds, data);
				g_status_code = wait_child(cmds);
			}
	}
}
