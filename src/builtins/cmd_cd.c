/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlins <rlins@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 10:49:23 by rlins             #+#    #+#             */
/*   Updated: 2022/11/17 19:37:15 by rlins            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void change_dir(t_data *data, char *path);
static void	update_work_dir_var(t_data *data, char *path);

/**
 * 1) Verify more than 1 param
 * 2) cd / cd [space] / cd -- / cd $HOME => Redirect to home
 * 3) cd - => Redirect to old path
 */
void	cmd_cd(t_data *data)
{
	char *path;

	if (data->command->args[2])
	{
		ft_putstr_fd("Minishell: cd: too manyargments\n", STDOUT_FILENO);
		exit(EXIT_FAILURE);
	}
	else if (!data->command->args[1]
			|| (ft_strncmp(data->command->args[1], "--", 2) == 0
			|| ft_strncmp(data->command->args[1], " ", 1)) == 0)
	{
		path = get_env_var_value(data->env, "HOME");
		change_dir(data, path);
	}
	else if (ft_strncmp(data->command->args[1], "-", 1) == 0)
	{
		path = get_env_var_value(data->env, OLD_PWD);
		change_dir(data, path);
	}
	else
	{
		change_dir(data, data->command->args[1]);
	}
}

/**
 * @brief Change Current directory.
 * Update the OLDPWD variable too
 * @param data Data Structure MiniShell
 * @param path This must be necessary because some times the path will be
 * different from data structure (Shortcuts).
 */
static void change_dir(t_data *data, char *path)
{
	char	*path_pwd;
	char	buff[MAX_PATH];

	if (chdir(path) != 0)
	{
		// TODO: Msg incompleta. Tem que ter o path passado
		ft_putstr_fd("Minishell: cd: No such file or directory\n", STDOUT_FILENO);
		exit(EXIT_FAILURE);
	}
	getcwd(buff, MAX_PATH);
	path_pwd = ft_strdup(buff); // Free OK!
	update_work_dir_var(data, path_pwd);
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
		data->old_work_dir = ft_strdup(data->work_dir); // TODO: Pending to free
	}
	if (data->work_dir)
	{
		free_ptr(data->work_dir);
		data->work_dir = ft_strdup(path); // TODO: Pending to free
	}
	free(path);
}
