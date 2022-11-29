/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_export_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtomomit <mtomomit@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 05:35:57 by mtomomit          #+#    #+#             */
/*   Updated: 2022/11/29 05:35:57 by mtomomit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	check_type(char ch)
{
	if (ch >= '0' && ch <= '9')
		return (1);
	if (ch >= 'a' && ch <= 'z')
		return (1);
	if (ch >= 'A' && ch <= 'Z')
		return (1);
	if (ch == '_')
		return (1);
	return (0);
}

static void	handle_quotes(t_index_data *i_data, char *s, t_data *data)
{
	if (s[i_data->i++] == '\'')
	{
		while (s[i_data->i] && s[i_data->i++] != '\'')
			;
	}
	else
	{
		while (s[i_data->i] && s[i_data->i++] != '\"')
				;
	}
}

static void	verify_redirections(t_commands *cmds, int num_cmd, t_data *data, \
		char **temp_parser)
{
	int	i;

	i = 0;
	while (temp_parser[i])
	{

	}
}

void	find_export_cmd(t_commands *cmds, int num_cmd, t_data *data)
{
	char			**temp_parser;
	int				o;
	int				i;

	temp_parser = parser(cmds->cmds[num_cmd]);
	i = 0;
	o = 0;
	while (temp_parser[o])
		o++;
	while (i < o)
	{
		if (!ft_strncmp("export\0", temp_parser[i], 7))
			break ;
		i = i + 2;
	}
	if (i < o)
		verify_redirections(cmds, num_cmd, data, temp_parser);
	i = 0;
	while (temp_parser[i])
		free(temp_parser[i++]);
	free(temp_parser[i]);
	free(temp_parser);
}
