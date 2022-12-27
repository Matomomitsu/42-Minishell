/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtomomit <mtomomit@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 06:02:22 by mtomomit          #+#    #+#             */
/*   Updated: 2022/11/29 06:02:22 by mtomomit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	handle_quotes(t_index_data *i_data, char *s, int add_malloc, \
				char special_char)
{
	if (add_malloc == 1)
	{
		i_data->i++;
		while (s[i_data->i] && s[i_data->i++] != special_char)
			i_data->malloc_size++;
		i_data->malloc_size++;
	}
	else
	{
		i_data->i++;
		while (s[i_data->i] && s[i_data->i++] != special_char)
			;
	}
}

static void	get_size(t_index_data *i_data, char *s)
{
	i_data->malloc_size = 0;
	while (s[i_data->i] && s[i_data->i] != '<' && s[i_data->i] != '>')
	{
		if (s[i_data->i] == '\'' || s[i_data->i] == '\"')
			handle_quotes(i_data, s, 0, s[i_data->i]);
		else
			i_data->i++;
	}
	while (s[i_data->i] && (s[i_data->i] == '<' || s[i_data->i] == '>' || \
			s[i_data->i] == ' ' ))
	{
		i_data->i++;
		i_data->malloc_size++;
	}
	while (s[i_data->i] && s[i_data->i] != ' ')
	{
		if (s[i_data->i] == '\'' || s[i_data->i] == '\"')
			handle_quotes(i_data, s, 1, s[i_data->i]);
		else
		{
			i_data->malloc_size++;
			i_data->i++;
		}
	}
}

static size_t	ft_countstr(char *s)
{
	t_index_data	i_data;
	size_t			counter;

	i_data.i = 0;
	counter = 0;
	while (s[i_data.i])
	{
		get_size(&i_data, s);
		if (i_data.malloc_size != 0)
			counter = counter + i_data.malloc_size;
	}
	return (counter);
}

char	*rm_redirection(char *s)
{
	char	*new_str;
	size_t	countstr;

	if (!s)
		return (NULL);
	countstr = ft_countstr(s);
	new_str = (char *)ft_calloc((ft_strlen(s) - countstr) + 1, sizeof(char *));
	new_str[ft_strlen(s) - countstr] = '\0';
	if (!new_str)
		return (NULL);
	copy_cmd(s, new_str);
	return (new_str);
}
