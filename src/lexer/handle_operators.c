/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_operators.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtomomit <mtomomit@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 15:16:03 by mtomomit          #+#    #+#             */
/*   Updated: 2022/12/01 15:53:19 by mtomomit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	handle_quotes(t_index_data *i_data, const char *s, t_commands *cmds)
{
	if (s[i_data->i++] == '\'')
	{
		while (s[i_data->i] && s[i_data->i] != '\'')
			i_data->i++;
	}
	else
	{
		while (s[i_data->i] && s[i_data->i] != '\"')
				i_data->i++;
	}
	if (s[i_data->i])
		i_data->i++;
}

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
