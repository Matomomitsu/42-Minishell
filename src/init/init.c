/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlins <rlins@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 08:54:58 by rlins             #+#    #+#             */
/*   Updated: 2022/11/13 17:11:45 by rlins            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static bool	valid_args(int argc);
static void	init_prompt(t_data *data);

int	init(int argc, char **argv, char **envp)
{
	t_data data;
	// TODO: Inicializar estrutura aqui também
	if (!valid_args(argc))
		exit_shell(EXIT_FAILURE);
	init_prompt(&data);
	return (0);
}

/**
 * @brief Validate number of arguments of Mini-shell
 * @param argc Argument Counts
 * @return true - Valid
 * @return false - Failed
 */
static bool	valid_args(int argc)
{
	if (argc > 1)
	{
		ft_putstr_fd(INV_ARGS, STDOUT_FILENO);
		return (false);
	}
	return (true);
}

/** TODO: Signal handler here?. History handler here?
 * @brief Initialize prompt.
 *
 * @param data
 */
static void	init_prompt(t_data *data)
{
	while (1)
	{
		data->user_input = readline(">$");
	}
}
