/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlins <rlins@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 16:54:30 by rlins             #+#    #+#             */
/*   Updated: 2022/11/13 17:02:52 by rlins            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/** TODO: Exit na pasta de init. Rever isso
 * TODO: Este cara vai receber provavelmente o free de varios objetos tb
 * Este cara tb receberá como param a variável global - status de exec do último
 * commando */
void	exit_shell(int status_code)
{
	exit(status_code);
}
