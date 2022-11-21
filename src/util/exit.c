/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlins <rlins@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 16:54:30 by rlins             #+#    #+#             */
/*   Updated: 2022/11/21 12:44:01 by rlins            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/** TODO: Estou usando o sair do buitins. Rever se este cara será necessário mesmo.*/
void	exit_shell(int status_code)
{
	exit(status_code);
}
