/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlins <rlins@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 17:25:21 by rlins             #+#    #+#             */
/*   Updated: 2022/11/14 09:37:23 by rlins            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	reset_prompt(int signal);

void	signals_handler()
{
	signal(SIGINT, reset_prompt);
	// Ctrl+\ handler
	signal(SIGQUIT, SIG_IGN);
}

/** TODO: Falta colocar a variável global com o status code correto aqui.
 * TODO: Signal deverá ser construído para HereDoc e / ou Child / parent proc.
 * @brief Will reset the prompt. Ctrl+C handler action.
 * @param signal
 */
static void	reset_prompt(int signal)
{
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}
