/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlins <rlins@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 08:51:11 by rlins             #+#    #+#             */
/*   Updated: 2022/11/15 12:01:24 by rlins            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
// # define BUFFER_SIZE 1024;
// # define TOK_BUFSIZE 64;
// # define TOK_DELIM " \t\r\n\a"
# define MAX_PATH 4096

# include "./libft.h"
# include <stdio.h> // Printf
# include <stdlib.h> // Malloc, Free, exit
# include <fcntl.h> // Open
# include <unistd.h> // read, execve, fork, pipe, getcwd
# include <sys/wait.h> // waitpid
# include <signal.h> // signal
# include <sys/types.h>
# include <dirent.h>
# include <stdio.h> // TODO: Allowed?
# include <stdbool.h>

# include <readline/readline.h> // Readline
# include <readline/history.h> // History

# define INV_ARGS "Invalid Arguments\n"

typedef struct s_data
{
	// bool		interactive;
	// t_token		*token;
	char		*user_input;
	char		**env;
	char		*working_dir;
	char		*old_working_dir;
	// t_command	*cmd;
	pid_t		pid;
}	t_data;

/**
 * @brief First method in project.
 * @param argc Arguments count
 * @param argv Arguments Vector
 * @return int
 */
int		init(int argc, char **argv, char **envp);

/**
 * @brief Responsible to exit / finish the shell.
 * @param status_code
 */
void	exit_shell(int status_code);

/**
 * @brief Manipulate Signals in MiniShell
 * 	(Ctrl+D) The Same - Terminate
 * 	(Ctrl+C) Change - Before: Stop process. Now: New line in clean prompt
 * 	(Ctrl+\) Change - Before: Terminate. Now: Ignore
 */
void	signals_handler();

/******************************************************************************/
/*Begin - Builtins*/
/******************************************************************************/
/**
 * @brief Verify if the command is a Builtin command. This is necessary to know
 * what is came from terminal
 * @param argv
 * @return true
 * @return false
 */
bool	is_builtin(char *argv);

/**
 * @brief Call correct function from Builtin command
 * @param argv
 */
void	call_builtin(char *argv);

/**
 * @brief Builtins Echo - Represent the Echo command in shell
 *
 */
void	cmd_echo(void);

/**
 * @brief Builtins Exit - Responsible to close the program.
  */
void	cmd_exit();

/**
 * @brief Builtins - PWD Command - Print working directory
 * MaxSize:
 * https://serverfault.com/questions/9546/filename-length-limits-on-linux
 */
void	cmd_pwd(void);
/******************************************************************************/
/*End - Builtins*/
/******************************************************************************/

#endif