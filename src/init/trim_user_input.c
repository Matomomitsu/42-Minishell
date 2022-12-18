/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_user_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtomomit <mtomomit@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 15:53:17 by mtomomit          #+#    #+#             */
/*   Updated: 2022/12/17 21:41:34 by mtomomit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*trim_user_imput(char *user_input)
{
	int		aux;
	int		start_string;
	int		finish_string;
	int		i;
	char	*new_user_input;

	i = 0;
	aux = ft_strlen(user_input) - 1;
	while (user_input[aux] == ' ')
		aux--;
	finish_string = aux;
	aux = 0;
	while (user_input[aux] && user_input[aux] == ' ')
		aux++;
	start_string = aux;
	new_user_input = (char *)ft_calloc(finish_string - start_string + 3, 1);
	while (aux <= finish_string)
		new_user_input[i++] = user_input[aux++];
	new_user_input[i] = '\0';
	return (new_user_input);
}
