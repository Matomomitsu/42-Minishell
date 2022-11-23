/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtomomit <mtomomit@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 17:52:56 by mtomomit          #+#    #+#             */
/*   Updated: 2022/11/21 17:52:56 by mtomomit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	get_size(t_index_data *data, const char *s)
{
	char	special_char;

	data->malloc_size = 0;
	while (s[data->i] && s[data->i] == ' ')
		data->i++;
	while (s[data->i] && s[data->i] != ' ')
	{
		if (s[data->i] == '\'' || s[data->i] == '\"')
		{
			special_char = s[data->i++];
			while (s[data->i] && s[data->i++] != special_char)
				data->malloc_size++;
		}
		else
		{
			data->malloc_size++;
			data->i++;
		}
	}
}

static size_t	ft_countstr(char const *s)
{
	t_index_data	data;
	size_t			counter;

	data.i = 0;
	counter = 0;
	while (s[data.i])
	{
		get_size(&data, s);
		if (data.malloc_size != 0)
			counter++;
	}
	return (counter);
}

static void	splitstr(char **str, char const *s, size_t countc)
{
	t_index_data	data;

	data.i = 0;
	data.j = 0;
	while (data.j < countc)
	{
		get_size(&data, s);
		str[data.j] = (char *)malloc((data.malloc_size + 1) * sizeof(char));
		str[data.j][data.malloc_size] = '\0';
		if (str[data.j++] == NULL)
		{
			str = NULL;
			break ;
		}
	}
}

char	**argument_parser(char const *s)
{
	char	**str;
	size_t	countstr;

	if (!s)
		return (NULL);
	countstr = ft_countstr(s);
	str = (char **)malloc((countstr + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	splitstr(str, s, countstr);
	if (str == NULL)
		return (NULL);
	putchar_parser(s, str, countstr);
	return (str);
}
