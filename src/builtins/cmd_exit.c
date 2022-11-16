/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlins <rlins@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:14:03 by rlins             #+#    #+#             */
/*   Updated: 2022/11/16 11:20:10 by rlins            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/** TODO: Verificar se é necessário colocar msg de saída?
 * TODO: Verificar o código de saída que é necessário atribuir
 * TODO: Necessário dar free em algo?
 * @brief
 *
 */
void	cmd_exit(void)
{
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	exit(EXIT_SUCCESS);
}
