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

static char	*verify_existing_quotes(t_commands *cmds, int num_cmd)
{
	int		i;
	int		o;
	char	*temp_char;

	o = 0;
	while (cmds->cmds[num_cmd][o++] != '=')
		;
	if (cmds->cmds[num_cmd][o] == '\"' || cmds->cmds[num_cmd][o] == '\'')
		return (NULL);
	temp_char = malloc(sizeof(char) * ft_strlen(cmds->cmds[num_cmd]) + 3);
	temp_char[ft_strlen(cmds->cmds[num_cmd]) + 2] = '\0';
	i = 0;
	o = 0;
	while (cmds->cmds[num_cmd][o] != '=')
		temp_char[i++] = cmds->cmds[num_cmd][o++];
	temp_char[i++] = cmds->cmds[num_cmd][o++];
	temp_char[i++] = '"';
	while (cmds->cmds[num_cmd][o] && cmds->cmds[num_cmd][o] != ' ')
		temp_char[i++] = cmds->cmds[num_cmd][o++];
	temp_char[i++] = '"';
	while (cmds->cmds[num_cmd][o])
		temp_char[i++] = cmds->cmds[num_cmd][o++];
	return (temp_char);
}

static void	add_quotes(t_commands *cmds, int num_cmd)
{
	char	*temp_char;

	temp_char = verify_existing_quotes(cmds, num_cmd);
	if (temp_char)
	{
		cmds->cmds[num_cmd] = ft_realloc(cmds->cmds[num_cmd], \
				ft_strlen(temp_char) + 1);
		ft_strlcpy(cmds->cmds[num_cmd], temp_char, ft_strlen(temp_char) + \
			1);
	}
	free(temp_char);
}

void	find_export_cmd(t_commands *cmds, int num_cmd, t_data *data)
{
	char	**temp_parser;
	int		o;
	int		i;

	temp_parser = parser(cmds->cmds[num_cmd]);
	i = 0;
	o = 0;
	if (!ft_strncmp("export\0", temp_parser[0], 7))
		add_quotes(cmds, num_cmd);
	i = 0;
	while (temp_parser[i])
		free(temp_parser[i++]);
	free(temp_parser[i]);
	free(temp_parser);
}
