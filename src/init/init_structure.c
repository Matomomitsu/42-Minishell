/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structure.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlins <rlins@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:23:38 by rlins             #+#    #+#             */
/*   Updated: 2022/12/05 09:11:36 by rlins            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static bool	init_env(t_data *data, char **envp);
static bool	init_pwd(t_data *data);

bool	init_structure(t_data *data, char **envp)
{
	if (!init_env(data, envp))
		return (false);
	if (!init_pwd(data))
		return (false);
	data->user_input = NULL;
	return (true);
}

/**
 * @brief Will initialize PWD and update OLDPWD in data structure.
 * Verify if OLDPWD exist in ENVP
 * @param data
 * @return true
 * @return false
 */
static bool	init_pwd(t_data *data)
{
	char	path[MAX_PATH];
	char	*cwd;

	cwd = getcwd(path, MAX_PATH);
	data->work_dir = ft_strdup(cwd);
	if (!data->work_dir)
		return (false);
	if (get_env_var_index(data->env, OLD_PWD) != -1)
		data->old_work_dir = ft_strdup(get_env_var_value(data->env, OLD_PWD));
	else
		data->old_work_dir = ft_strdup(cwd);
	return (true);
}

/**
 * @brief From To of environment variable to data structure.
 * @param data TypeDef in MiniShell
 * @param envp Pointer to Environment variables
 * @return true - Success
 * @return false - Problem
 */
static bool	init_env(t_data *data, char **envp)
{
	int	i;

	data->env = ft_calloc(env_var_count(envp) + 1, sizeof * data->env);
	if (!data->env)
		return (false);
	i = 0;
	while (envp[i])
	{
		data->env[i] = ft_strdup(envp[i]);
		i++;
	}
	return (true);
}

void	init_io(t_commands *cmds)
{
	if (!cmds->io)
	{
		cmds->io->in_file_name = NULL;
		cmds->io->out_file_name = NULL;
		cmds->io->fd_in = -1;
		cmds->io->fd_out = -1;
		cmds->io->std_in_bkp = -1;
		cmds->io->std_out_bkp = -1;
	}
}

// int	args_count(char **args)
// {
// 	int	i;

// 	i = 1;
// 	while (args[i])
// 	{
// 		i++;
// 	}
// 	return (i);
// }
