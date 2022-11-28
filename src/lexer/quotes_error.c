/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtomomit <mtomomit@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 22:12:22 by mtomomit          #+#    #+#             */
/*   Updated: 2022/11/27 22:12:22 by mtomomit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	quotes_error(t_index_data *i_data, const char *s, t_commands *cmds)
{
	if (!s[i_data->i] && cmds->exit_value == 0)
	{
		cmds->exit_value = 2;
		ft_putstr_fd("-minishell: syntax error unclosed quotes\n", \
		STDERR);
	}
}
