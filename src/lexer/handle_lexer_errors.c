/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_lexer_errors.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtomomit <mtomomit@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 00:33:37 by mtomomit          #+#    #+#             */
/*   Updated: 2022/11/23 00:33:37 by mtomomit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	lexer_errors(t_index_data *i_data, const char *s, t_commands *cmds)
{
	if (!s[i_data->i] && (s[i_data->i - 1] == '|' || s[i_data->i - 1] == '&'))
	{
		cmds->exit_value = error_msg_cmd(NULL, NULL, \
		"-minishell: syntax error not expecting newline", 2);
	}
	while (s[i_data->i] && (s[i_data->i] == '|' || s[i_data->i] == '&' \
		|| s[i_data->i] == ' '))
	{
		if ((s[i_data->i] == '|' || s[i_data->i] == '&') && cmds->exit_value \
		== 0)
		{
			cmds->exit_value = 2;
			ft_putstr_fd("-minishell: syntax error near unexpected token `", \
			STDERR);
			while (s[i_data->i] && (s[i_data->i] == '|' || s[i_data->i] == '&'))
				ft_putchar_fd(s[i_data->i++], STDERR);
			ft_putstr_fd("'\n", STDERR);
		}
		i_data->i++;
		if (!s[i_data->i] && cmds->exit_value == 0)
		{
			cmds->exit_value = error_msg_cmd(NULL, NULL,
			"-minishell: syntax error not expecting newline", 2);
		}
	}
}
