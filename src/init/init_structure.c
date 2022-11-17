/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structure.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlins <rlins@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:23:38 by rlins             #+#    #+#             */
/*   Updated: 2022/11/17 10:05:54 by rlins            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static bool	init_env(t_data *data, char **envp);

/** TODO: Podemos iniciar as demais variáveis da struct aqui também
 * @brief Initialize the structure of minishell
 * @param data TypeDef in MiniShell
 * @param envp Pointer to Environment variables
 * @return true - Success
 * @return false - Problem
 */
bool	init_structure(t_data *data, char **envp)
{
	if (!init_env(data, envp))
		return (false);
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
