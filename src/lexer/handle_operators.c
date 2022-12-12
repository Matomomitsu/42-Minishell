/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_operators.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlins <rlins@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 15:16:03 by mtomomit          #+#    #+#             */
/*   Updated: 2022/12/12 10:33:26 by rlins            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	operators_errors(const char *s, t_commands *cmds, t_index_data \
							*i_data)
{
	if (cmds->exit_value == 0 && s[i_data->i])
	{
		cmds->exit_value = 2;
		ft_putstr_fd("-minishell: syntax error near unexpected token `", \
		STDERR);
		ft_putchar_fd(s[i_data->i], STDERR);
		ft_putstr_fd("'\n", STDERR);
	}
	if (cmds->exit_value == 0 && !s[i_data->i])
	{
		cmds->exit_value = 2;
		ft_putstr_fd("-minishell: syntax error near unexpected token `", \
		STDERR);
		ft_putstr_fd("newline'\n", STDERR);
	}
}

void	lexer_operators(const char *s, t_commands *cmds)
{
	t_index_data	i_data;

	i_data.i = 0;
	while (s[i_data.i] && s[i_data.i] == ' ')
			i_data.i++;
	if (s[i_data.i] == '&' || s[i_data.i] == '|')
	{
		operators_errors(s, cmds, &i_data);
	}
	else
	{
		while (s[i_data.i])
		{
			if (s[i_data.i] && (s[i_data.i] == '&' || s[i_data.i] == '|'))
			{
				i_data.i++;
				while (s[i_data.i] && s[i_data.i] == ' ')
					i_data.i++;
				if (!s[i_data.i])
					operators_errors(s, cmds, &i_data);
			}
			else
				i_data.i++;
		}
	}
}
