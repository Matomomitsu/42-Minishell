/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlins <rlins@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:19:00 by rlins             #+#    #+#             */
/*   Updated: 2022/11/14 16:48:18 by rlins            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	is_builtin(char **argv)
{
	if (ft_strncmp(argv[0], "echo", 5) == 0)
		return (true);
}

void	call_builtin(char **argv)
{
	if (ft_strncmp(argv[0], "echo", 5) == 0)
		echo_cmd();

}
