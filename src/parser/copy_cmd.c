/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtomomit <mtomomit@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 05:41:45 by mtomomit          #+#    #+#             */
/*   Updated: 2022/11/29 06:03:01 by mtomomit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

typedef struct s_temp_index
{
	size_t	i;
	size_t	o;
	size_t	j;
}	t_temp_index;

static void	handle_quotes(t_temp_index *data, char *s, char special_char)
{
	data->i++;
	while (s[data->i] && s[data->i] != special_char)
		data->i++;
	data->i++;
}

static void	copy_quotes(char *s, char *new_str, t_temp_index *data)
{
	new_str[data->o++] = s[data->i++];
	if (s[data->i - 1] == '\'')
	{
		while (s[data->i] && s[data->i] != '\'')
			new_str[data->o++] = s[data->i++];
	}
	else
	{
		while (s[data->i] && s[data->i] != '\"')
			new_str[data->o++] = s[data->i++];
	}
	new_str[data->o++] = s[data->i++];
}

static void	ft_strcpy(char *s, char *new_str, t_temp_index *data)
{
	data->o = 0;
	while (s[data->i])
	{
		while (s[data->i] && (s[data->i] != '<' && s[data->i] != '>'))
		{
			if (s[data->i] == '\'' || s[data->i] == '\"')
				copy_quotes(s, new_str, data);
		else
			new_str[data->o++] = s[data->i++];
		}
		while (s[data->i] && (s[data->i] == '<' || s[data->i] == '>' || \
				s[data->i] == ' ' ))
			data->i++;
		while (s[data->i] && s[data->i] != ' ')
		{
			if (s[data->i] == '\'' || s[data->i] == '\"')
				handle_quotes(data, s, s[data->i]);
			else
				data->i++;
		}
	}
}

void	copy_cmd(char *s, char *new_str, size_t countc)
{
	t_temp_index	data;

	data.i = 0;
	data.j = 0;
	ft_strcpy(s, new_str, &data);
}
