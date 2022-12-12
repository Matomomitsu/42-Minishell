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

static char	*verify_existing_quotes(char **temp_p, int num_arg)
{
	int		i;
	int		o;
	char	*temp_char;

	o = 0;
	while (temp_p[num_arg][o] && temp_p[num_arg][o++] != '=')
		;
	if (!temp_p[num_arg][o] || temp_p[num_arg][o] == '\"' || \
		temp_p[num_arg][o] == '\'')
		return (NULL);
	temp_char = malloc(sizeof(char) * ft_strlen(temp_p[num_arg]) + 3);
	temp_char[ft_strlen(temp_p[num_arg]) + 2] = '\0';
	i = 0;
	o = 0;
	while (temp_p[num_arg][o] != '=')
		temp_char[i++] = temp_p[num_arg][o++];
	temp_char[i++] = temp_p[num_arg][o++];
	temp_char[i++] = '"';
	while (temp_p[num_arg][o] && temp_p[num_arg][o] != ' ')
		temp_char[i++] = temp_p[num_arg][o++];
	temp_char[i++] = '"';
	while (temp_p[num_arg][o])
		temp_char[i++] = temp_p[num_arg][o++];
	return (temp_char);
}

static void	add_quotes(t_commands *cmds, int num_cmd, char **temp_parser)
{
	char	*temp_char;
	char	*temp_char2;
	int		i;
	char	*new_str;

	i = 1;
	new_str = ft_strjoin(temp_parser[0], " ");
	while (temp_parser[i])
	{
		temp_char2 = ft_strjoin(new_str, " ");
		temp_char = verify_existing_quotes(temp_parser, i);
		free(new_str);
		if (temp_char != NULL)
			new_str = ft_strjoin(temp_char2, temp_char);
		else
			new_str = ft_strjoin(temp_char2, temp_parser[i]);
		i++;
		free(temp_char2);
		free(temp_char);
	}
	cmds->cmds[num_cmd] = ft_realloc(cmds->cmds[num_cmd], \
			ft_strlen(new_str) + 1);
	ft_strlcpy(cmds->cmds[num_cmd], new_str, ft_strlen(new_str) + 1);
	free(new_str);
}

void	find_export_cmd(t_commands *cmds, int num_cmd)
{
	char	**temp_parser;
	int		i;

	temp_parser = rm_spaces(cmds->cmds[num_cmd]);
	i = 0;
	if (!ft_strncmp("export\0", temp_parser[0], 7))
		add_quotes(cmds, num_cmd, temp_parser);
	i = 0;
	while (temp_parser[i])
		free(temp_parser[i++]);
	free(temp_parser[i]);
	free(temp_parser);
}
