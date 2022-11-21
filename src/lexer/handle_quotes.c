/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotation_marks.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtomomit <mtomomit@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 23:11:04 by mtomomit          #+#    #+#             */
/*   Updated: 2022/11/20 23:11:04 by mtomomit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

typedef struct s_index_data
{
	size_t	i;
	size_t	malloc_size;
	size_t	j;
}	t_index_data;

void	handle_quotes(t_index_data *data, const char *s)
{
	if (s[data->i] == '\'')
	{
		data->i++;
		while (s[data->i] && s[data->i++] != '\'')
			data->malloc_size++;
	}
	else
	{
		data->i++;
		while (s[data->i] && s[data->i++] != '\"')
		{
			if (s[data->i] != '$')
				data->malloc_size++;
			else
				data->i++;
		}
	}
	// TODO error unclosed quotes
}
