/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtomomit <mtomomit@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 01:56:42 by mtomomit          #+#    #+#             */
/*   Updated: 2022/11/28 01:56:42 by mtomomit         ###   ########.fr       */
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

static void	redirections_erros(const char *s, t_commands *cmds, t_index_data \
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

static void	handle_redirections(const char *s, t_commands *cmds, t_index_data \
			*i_data)
{
	i_data->i++;
	if (s[i_data->i] && (s[i_data->i] == '<' || s[i_data->i] == '>'))
		i_data->i++;
	while (s[i_data->i] && s[i_data->i] == ' ')
		i_data->i++;
	if (s[i_data->i] && (s[i_data->i] == '&' || s[i_data->i] == '|'))
		redirections_erros(s, cmds, i_data);
	if (s[i_data->i] && (s[i_data->i] == '<' || s[i_data->i] == '>'))
		redirections_erros(s, cmds, i_data);
	if (!s[i_data->i])
		redirections_erros(s, cmds, i_data);
}

void	lexer_redirections(const char *s, t_commands *cmds)
{
	t_index_data	i_data;

	i_data.i = 0;
	while (s[i_data.i])
	{
		if (s[i_data.i] == '<' || s[i_data.i] == '>')
			handle_redirections(s, cmds, &i_data);
		if (s[i_data.i] == '\'' || s[i_data.i] == '\"')
			handle_quotes(&i_data, s, cmds);
		if (s[i_data.i])
			i_data.i++;
	}
}
