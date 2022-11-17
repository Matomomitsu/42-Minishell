/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structure.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlins <rlins@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:23:38 by rlins             #+#    #+#             */
/*   Updated: 2022/11/17 10:39:42 by rlins            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static bool	init_env(t_data *data, char **envp);
static bool	init_pwd(t_data *data);

/** TODO: Podemos iniciar as demais variáveis da struct aqui também
 */
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
 * Verify fi OLDPWD exist in ENVP
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
	{
		data->old_work_dir = ft_strdup(get_env_var_value(data->env, OLD_PWD));
	}
	else
	{
		data->old_work_dir = ft_strdup(cwd);
	}
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

	// TODO: Tem q dar free neste maluco aqui
	// +1 pq senão vai dar segment fault
	data->env = ft_calloc(env_var_count(envp) + 1, sizeof * data->env);
	if (!data->env)
		return (false);
	i = 0;
	while (envp[i])
	{
		data->env[i] = ft_strdup(envp[i]); // TODO: Dar free aqui tb!
		i++;
	}
	return (true);
}
