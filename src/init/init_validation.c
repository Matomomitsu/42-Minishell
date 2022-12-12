/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlins <rlins@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 11:03:35 by rlins             #+#    #+#             */
/*   Updated: 2022/12/12 10:05:11 by rlins            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	valid_args(int argc, char **argv)
{
	if (argc > 1 || !argv)
	{
		ft_putendl_fd("Invalid Arguments", STDOUT_FILENO);
		return (false);
	}
	return (true);
}

bool	just_space_string(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isspace(str[i]))
			return (false);
		i++;
	}
	return (true);
}
