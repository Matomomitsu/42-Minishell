/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complete_lexer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtomomit <mtomomit@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 12:40:13 by mtomomit          #+#    #+#             */
/*   Updated: 2022/11/18 12:40:13 by mtomomit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

typedef struct s_index_data
{
	size_t	i;
	size_t	o;
	size_t	j;
}	t_index_data;

static void	copy_quotes(char const *s, char **str, t_index_data *data)
{
	if (s[data->i++] == '\'')
	{
		while (s[data->i] && s[data->i] != '\'')
			str[data->j][data->o++] = s[data->i++];
	}
	else
	{
		while (s[data->i] && s[data->i] != '\"')
		{
			if (s[data->i] != '$')
				str[data->j][data->o++] = s[data->i++];
			else
				data->i++;
		}
	}
}

static void	ft_strcpy(char const *s, char **str, t_index_data *data)
{
	data->o = 0;
	while (s[data->i] && s[data->i] != '&' && s[data->i] != '|')
	{
		if (s[data->i] == '\'' || s[data->i] == '\"')
			copy_quotes(s, str, data);
		if (s[data->i])
			str[data->j][data->o++] = s[data->i++];
	}
	data->i++;
	if (s[data->i - 1] == '&' && s[data->i] == '&')
		data->i++;
	if (s[data->i - 1] == '|' && s[data->i] == '|')
		data->i++;
	while (s[data->i] == ' ')
		data->i++;
}

void	putchar_lexer(char const *s, char **str, size_t countc)
{
	t_index_data	data;

	data.i = 0;
	data.j = 0;
	while (data.j < countc)
	{
		ft_strcpy(s, str, &data);
		data.j++;
	}
	str[data.j] = NULL;
}
