/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlins <rlins@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 17:25:21 by rlins             #+#    #+#             */
/*   Updated: 2022/11/13 17:37:11 by rlins            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	ctrl_c(int signal);

void	signals_handler()
{
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}

/** TODO: Falta colocar a variável glogal com o status code correto aqui.
 * @brief Will reset the prompt
 * @param signal
 */
static void	ctrl_c(int signal)
{
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}
