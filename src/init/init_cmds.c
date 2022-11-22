/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtomomit <mtomomit@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 17:53:02 by mtomomit          #+#    #+#             */
/*   Updated: 2022/11/21 17:53:02 by mtomomit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**get_paths(char **env)
{
	size_t	i;
	char	**paths;
	char	*trim_path;

	i = 0;
	while (ft_strncmp(env[i], "PATH=", 5))
		i++;
	trim_path = ft_substr(env[i], 5, ft_strlen(env[i]));
	paths = ft_split(trim_path, ':');
	free(trim_path);
	return (paths);
}

void	init_cmds(t_data *data, t_commands *cmds)
{
	cmds->cmds = lexer(data->user_input, data);
	cmds->paths = get_paths(data->env);
}
