/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtomomit <mtomomit@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 10:49:23 by rlins             #+#    #+#             */
/*   Updated: 2022/12/02 09:53:05 by mtomomit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	change_dir(t_data *data, char *path);
static void	update_work_dir_var(t_data *data, char *path);

/**
 * 1) Verify more than 1 param
 * 2) cd / cd [space] / cd -- / cd $HOME => Redirect to home
 * 3) cd - => Redirect to old path. Error when start prompt and do this cmd.
 */
int	cmd_cd(t_data *data, t_commands *cmds, int num_cmd)
{
	char	*path;

	if (cmds->cmd[num_cmd].args[2])
		return (error_msg_cmd("cd", NULL, "too many arguments", EXIT_FAILURE));
	else if (!cmds->cmd[num_cmd].args[1] || ft_isspace(cmds->cmd[num_cmd].args[1][0])
		|| cmds->cmd[num_cmd].args[1][0] == '\0'
		|| (ft_strncmp(cmds->cmd[num_cmd].args[1], "--", 3) == 0
		|| ft_strncmp(cmds->cmd[num_cmd].args[1], " ", 2)) == 0)
	{
		path = get_env_var_value(data->env, "HOME");
		if (!path || *path == '\0' || ft_isspace(*path))
			return (error_msg_cmd("cd", NULL, "HOME not set", EXIT_FAILURE));
		return (change_dir(data, path));
	}
	else if (ft_strncmp(cmds->cmd[num_cmd].args[1], "-", 2) == 0)
	{
		path = get_env_var_value(data->env, OLD_PWD);
		if (!path)
			return (error_msg_cmd("cd", NULL, "OLDPWD not set", EXIT_FAILURE));
		return (change_dir(data, path));
	}
	else
		return (change_dir(data, cmds->cmd[num_cmd].args[1]));
}

/**
 * @brief Change Current directory.
 * Update the OLDPWD variable too
 * @param data Data Structure MiniShell
 * @param path This must be necessary because some times the path will be
 * different from data structure (Shortcuts).
 */
static int	change_dir(t_data *data, char *path)
{
	char	*path_pwd;
	char	buff[MAX_PATH];

	if (chdir(path) != 0)
		return (error_msg_cmd("cd", path, strerror(errno), errno));
	getcwd(buff, MAX_PATH);
	path_pwd = ft_strdup(buff);
	update_work_dir_var(data, path_pwd);
	return (EXIT_SUCCESS);
}

/**
 * @brief Update PWD and OLDPWD variables. Update the variables in data
 * structure too.
 * @param data
 * @param path
 */
static void	update_work_dir_var(t_data *data, char *path)
{
	set_env_var(data, OLD_PWD, get_env_var_value(data->env, PWD));
	set_env_var(data, PWD, path);
	if (data->old_work_dir)
	{
		free_ptr(data->old_work_dir);
		data->old_work_dir = ft_strdup(data->work_dir);
	}
	if (data->work_dir)
	{
		free_ptr(data->work_dir);
		data->work_dir = ft_strdup(path);
	}
	free(path);
}
