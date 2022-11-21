/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlins <rlins@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:14:03 by rlins             #+#    #+#             */
/*   Updated: 2022/11/21 12:41:45 by rlins            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/** TODO: Verificar se é necessário colocar msg de saída?
 * TODO: Verificar o código de saída que é necessário atribuir
 * @brief
 *
 */
void	cmd_exit(t_data *data)
{
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	free_data(data, true);
	exit(EXIT_SUCCESS);
}
