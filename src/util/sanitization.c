/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanitization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlins <rlins@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 16:06:42 by rlins             #+#    #+#             */
/*   Updated: 2022/11/21 12:37:34 by rlins            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_ptr(void *ptr)
{
	free(ptr);
	ptr = NULL;
}

void	free_data(t_data *data, bool exit_shell)
{
	if (data)
	{
		if (data->user_input)
			free_ptr(data->user_input);
		if (data->command)
		{
			if (data->command->args)
				free_array_str(data->command->args);
			free_ptr(data->command);
		}
		if (exit_shell)
		{
			if (data->old_work_dir)
				free_ptr(data->old_work_dir);
			if (data->work_dir)
				free_ptr(data->work_dir);
			if (data->env)
				free_array_str(data->env);
			rl_clear_history();
		}
	}
}

void	free_array_str(char **arr_str)
{
	int	i;

	i = 0;
	if (arr_str)
	{
		while (arr_str[i])
		{
			if (arr_str[i])
			{
				free_ptr(arr_str[i]);
				arr_str[i] = NULL;
			}
			i++;
		}
		free(arr_str);
		arr_str = NULL;
	}
}

void	free_cmds(t_commands *cmds)
{
	int	i;

	i = 0;
	while (cmds->cmds[i])
		free(cmds->cmds[i++]);
	free(cmds->cmds[i]);
	free(cmds->cmds);
	i = 0;
	while (cmds->paths[i])
		free(cmds->paths[i++]);
	free(cmds->paths[i]);
	free(cmds->paths);
	free(cmds);
}
