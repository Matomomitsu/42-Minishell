/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtomomit <mtomomit@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 14:57:26 by mtomomit          #+#    #+#             */
/*   Updated: 2022/11/17 14:57:26 by mtomomit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

typedef struct s_index_data
{
	size_t	i;
	size_t	malloc_size;
	size_t	j;
}	t_index_data;

static void	get_size(t_index_data *i_data, const char *s)
{
	char	special_char;

	i_data->malloc_size = 0;
	while (s[i_data->i] && s[i_data->i] != '&' && s[i_data->i++] != '|')
	{
		if (s[i_data->i] == '\'' || s[i_data->i] == '\"')
			handle_quotes(i_data, s);
		if (s[i_data->i])
			i_data->malloc_size++;
	}
	if (s[i_data->i - 1] == '&' && s[i_data->i] == '&')
		i_data->i++;
	if (s[i_data->i - 1] == '|' && s[i_data->i] == '|')
		i_data->i++;
	if (s[i_data->i] == '|' || s[i_data->i] == '&')
		exit_value(1)
}

static size_t	ft_countstr(char const *s)
{
	t_index_data	i_data;
	size_t			counter;

	i_data.i = 0;
	counter = 0;
	while (s[i_data.i])
	{
		get_size(&i_data, s);
		if (i_data.malloc_size != 0)
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

char	**lexer(char const *s)
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
	putchar_str(s, str, countstr);
	return (str);
}
