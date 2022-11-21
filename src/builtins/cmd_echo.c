/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlins <rlins@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 09:08:47 by rlins             #+#    #+#             */
/*   Updated: 2022/11/21 09:20:39 by rlins            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static bool	exist_n_option(t_data *data);

/**
 * TODO: Ainda imprimindo aspas (simpples e duplas). Tem que ser corrigido
 * quando implementar o parser
 */
void	cmd_echo(t_data *data)
{
	int		i;
	char	**echo_cmd;
	bool	option_n;

	option_n = exist_n_option(data);

	if (option_n == true)
		i = 2;
	else
		i = 1;
	while (data->command->args[i])
	{
		ft_putstr_fd(data->command->args[i], STDOUT_FILENO);
		if (data->command->args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (option_n == false)
		ft_putchar_fd('\n', STDOUT_FILENO);
}

/**
 * @brief Check if in the command, the param -n was used
 * @param data Structure of MiniShell
 * @return true (with option)
 * @return false (without option)
 */
static bool	exist_n_option(t_data *data)
{
	if (ft_strncmp(data->user_input,"echo -n", 7) == 0)
		return (true);
	return (false);
}
