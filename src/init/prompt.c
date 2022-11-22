/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlins <rlins@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 07:15:31 by rlins             #+#    #+#             */
/*   Updated: 2022/11/22 09:14:16 by rlins            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*make_color(char *str, char *color, bool first_call);

char	*get_prompt(t_data *data)
{
	char	*temp;
	char	*temp2;
	char	*color;

	temp = get_env_var_value(data->env, "USERNAME");
	if (!temp)
		temp = "Gest";
	color = make_color(temp, GREEN, true);
	temp2 = ft_strjoin(color, "@");
	temp = NULL;
	free_ptr(color);
	temp = ft_strjoin(temp2, "Mini-shell");
	free_ptr(temp2);
	temp2 = ft_strjoin(temp, ":~");
	free_ptr(temp);
	color = make_color(temp2, YELLOW, false);
	temp = ft_strjoin(color, data->work_dir);
	free_ptr(temp2);
	free_ptr(color);
	color = make_color(temp, DEFAULT, false);
	temp2 = ft_strjoin(color, "$> ");
	free_ptr(temp);
	free_ptr(color);
	return (temp2);
}

/**
 * @brief Make color in Prompt.
 * @param str Str to join with color
 * @param color What color put in string
 * @param first_call In the first call, colorize after call
 * @return char* - string colorized
 */
static char	*make_color(char *str, char *color, bool first_call)
{
	char	*new_str;

	if (first_call == true)
		new_str = ft_strjoin(color, str);
	else
		new_str = ft_strjoin(str, color);
	return (new_str);
}
