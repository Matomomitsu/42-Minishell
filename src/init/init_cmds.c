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

static char	**get_paths(char **env)
{
	size_t	i;
	char	**paths;
	char	*trim_path;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5))
		i++;
	if (env[i])
	{
		trim_path = ft_substr(env[i], 5, ft_strlen(env[i]));
		paths = ft_split(trim_path, ':');
		free(trim_path);
		return (paths);
	}
	else
		return (NULL);
}

static void	handle_operators(t_data *data, t_commands *cmds, size_t *o, \
			size_t *i)
{
	if (data->user_input[*i] == '&' || data->user_input[*i + 1] == '&')
		cmds->operators[*o] = AND;
	if (data->user_input[*i] == '|' && data->user_input[*i + 1] == '|')
		cmds->operators[*o] = OR;
	if (data->user_input[*i] == '|' && data->user_input[*i + 1] != '|')
		cmds->operators[*o] = PIPE;
	*o = *o + 1;
	*i = *i + 1;
	if (data->user_input[*i] == '|' || data->user_input[*i] == '&')
		*i = *i + 1;
}

static void	get_operators(t_data *data, t_commands *cmds)
{
	size_t		i;
	size_t		o;
	char		special_char;

	i = 0;
	o = 0;
	cmds->operators = ft_calloc(cmds->num_cmds, sizeof(int));
	while (data->user_input[i])
	{
		if (data->user_input[i] == '\'' || data->user_input[i] == '\"')
		{
			special_char = data->user_input[i++];
			while (data->user_input[i] && data->user_input[i] != special_char)
				i++;
		}
		if (data->user_input[i] == '&' || data->user_input[i] == '|')
			handle_operators(data, cmds, &o, &i);
		i++;
	}
}

static void	init_pipe(t_commands *cmds)
{
	int	i;

	i = 0;
	cmds->pipe = (t_pipe *)ft_calloc(cmds->num_cmds, sizeof(t_pipe));
	while (i < cmds->num_cmds)
	{
		cmds->pipe[i].fd = (int *)ft_calloc(sizeof(int), 3);
		if (!cmds->pipe[i].fd)
			exit(6);
		if (pipe(cmds->pipe[i].fd) == -1)
			exit (7);
		i++;
	}
}

void	init_cmds(t_data *data, t_commands *cmds)
{
	int		i;

	cmds->cmds = lexer(data->user_input, cmds);
	i = 0;
	if (cmds->exit_value == 0)
	{
		while (cmds->cmds[i])
			i++;
		cmds->num_cmds = i;
		cmds->paths = get_paths(data->env);
		if (cmds->num_cmds > 0)
			get_operators(data, cmds);
		init_pipe(cmds);
		cmds->pid = (pid_t *)ft_calloc(sizeof(pid_t), cmds->num_cmds + 1);
		cmds->cmd = ft_calloc(cmds->num_cmds, sizeof(t_cmd));
	}
}
