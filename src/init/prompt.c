/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlins <rlins@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 07:15:31 by rlins             #+#    #+#             */
/*   Updated: 2022/11/22 08:15:30 by rlins            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char *get_prompt(t_data *data)
{
	char	*temp;
	char	*temp2;

	//[USER_NAME]@[NAME_OF_SYSTEM]:~$>
	//[USER_NAME]@[minishell]:~[] $>
	temp = get_env_var_value(data->env, "USERNAME");
	if (!temp)
		temp = "Gest";
	temp2 = ft_strjoin(temp, "@");
	temp = NULL;

	temp = ft_strjoin(temp2, "Mini-shell");
	free_ptr(temp2);
	// return (temp);

	temp2 = ft_strjoin(temp, ":~");
	free_ptr(temp);
	// return (temp2);

	temp = ft_strjoin(temp2, data->work_dir);
	free_ptr(temp2);
	// return (temp);

	temp2 = ft_strjoin(temp, " $> ");
	free(temp);
	return (temp2);
}
