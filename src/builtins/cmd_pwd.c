/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlins <rlins@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 11:37:20 by rlins             #+#    #+#             */
/*   Updated: 2022/11/23 07:34:54 by rlins            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	cmd_pwd(void)
{
	char	*pwd;
	char	path[MAX_PATH];

	pwd = getcwd(path, MAX_PATH);
	if (pwd)
	{
		ft_putendl_fd(path, STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
	error_msg_cmd("pwd", NULL, strerror(errno), errno);
	return (EXIT_FAILURE);
}
