/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlins <rlins@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 10:49:23 by rlins             #+#    #+#             */
/*   Updated: 2022/11/23 07:43:02 by rlins            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	change_dir(t_data *data, char *path);
static void	update_work_dir_var(t_data *data, char *path);

/**
 * 1) Verify more than 1 param
 * 2) cd / cd [space] / cd -- / cd $HOME => Redirect to home
 * 3) cd - => Redirect to old path. Error when start prompt and do this cmd.
 * TODO: cd $HOME Is NOT Working yet
 */
int	cmd_cd(t_data *data)
{
	char	*path;

	if (data->command->args_count > 2)
		return (error_msg_cmd("cd", NULL, "too many arguments", EXIT_FAILURE));
	else if (!data->command->args[1] || ft_isspace(data->command->args[1][0])
		|| data->command->args[1][0] == '\0'
		|| (ft_strncmp(data->command->args[1], "--", 2) == 0
		|| ft_strncmp(data->command->args[1], " ", 1)) == 0)
	{
		path = get_env_var_value(data->env, "HOME");
		if (!path || *path == '\0' || ft_isspace(*path))
			return (error_msg_cmd("cd", NULL, "HOME not set", EXIT_FAILURE));
		return (change_dir(data, path));
	}
	else if (ft_strncmp(data->command->args[1], "-", 1) == 0)
	{
		path = get_env_var_value(data->env, OLD_PWD);
		if (!path)
			return (error_msg_cmd("cd", NULL, "OLDPWD not set", EXIT_FAILURE));
		return (change_dir(data, path));
	}
	else
		return (change_dir(data, data->command->args[1]));
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
