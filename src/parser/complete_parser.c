/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complete_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtomomit <mtomomit@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:52:07 by mtomomit          #+#    #+#             */
/*   Updated: 2022/11/22 15:52:07 by mtomomit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_index_data
{
	size_t	i;
	size_t	o;
	size_t	j;
}	t_index_data;

static void	ft_strcpy(char const *s, char **str, t_index_data *data)
{
	char	special_char;

	data->o = 0;
	while (s[data->i] && s[data->i] == ' ')
		data->i++;
	while (s[data->i] && s[data->i] != ' ')
	{
		if (s[data->i] == '\'' || s[data->i] == '\"')
		{
			special_char = s[data->i++];
			while (s[data->i] && s[data->i] != special_char)
				str[data->j][data->o++] = s[data->i++];
			data->i++;
		}
		else
			str[data->j][data->o++] = s[data->i++];
	}
}

void	putchar_str(char const *s, char **str, size_t countc)
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
