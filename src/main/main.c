/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlins <rlins@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 09:16:27 by rlins             #+#    #+#             */
/*   Updated: 2022/11/13 16:16:23 by rlins            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief Main Class of program
 * @param argc Arguments Count
 * @param argv Arguments Vector
 * @param envp Environment variables
 * @return int
 */
int	main(int argc, char **argv, char **envp)
{
	if (argc > 1)
	{
		ft_putstr_fd(INV_ARGS, STDOUT_FILENO);
		//INV_ARGS
		return (EXIT_FAILURE);
	}
	init(argc, argv, envp);
	return (0);
}
