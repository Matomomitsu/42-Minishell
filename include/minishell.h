/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlins <rlins@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 08:51:11 by rlins             #+#    #+#             */
/*   Updated: 2022/11/27 09:35:08 by rlins            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
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
# include <stdio.h>
# include <errno.h> // errno

# include <readline/readline.h> // Readline
# include <readline/history.h> // History

# define INV_ARGS "Invalid Arguments\n"

# define OLD_PWD "OLDPWD"
# define PWD "PWD"

# define CMD_NOT_FOUND 127

// Color prompt
# define GREEN "\001\033[0;92m\002"
# define DEFAULT "\001\033[0;39m\002"
# define YELLOW "\001\033[0;93m\002"

typedef struct s_command
{
	char	*cmd;
	char	**args;
	int		args_count;
}	t_command;

typedef struct s_data
{
	char		*user_input;
	char		**env;
	char		*work_dir;
	char		*old_work_dir;
	t_command	*command;
}	t_data;

extern int	g_status_code;

/******************************************************************************/
/*Begin - Initialization*/
/******************************************************************************/
/**
 * @brief First method in project.
 * @param argc Arguments count
 * @param argv Arguments Vector
 * @param envp Environment pointer variable
 * @return int
 */
int		init(int argc, char **argv, char **envp);

/**
 * @brief Initialize the structure of minishell
 * @param data TypeDef in MiniShell
 * @param envp Pointer to Environment variables
 * @return true - Success
 * @return false - Problem
 */
bool	init_structure(t_data *data, char **envp);

/**
 * @brief Return the number of arguments passed in the command
 * @param args TypeDef in MiniShell
 * @return int - Count Number of arguments. The Command argument will be ignored
 * in this method. Return just arguments
 */
int		args_count(char **args);

/******************************************************************************/
/*End - Initialization*/
/******************************************************************************/

/**
 * @brief Responsible to exit / finish the shell.
 * @param status_code
 * @param data Data to clean up
 */
void	exit_shell(t_data *data, int status_code);

/**
 * @brief Manipulate Signals in MiniShell when the prompt is waiting for a
 * command.
 * 	(Ctrl+D) The Same - Terminate
 * 	(Ctrl+C) SIGINT: New line in clean prompt
 * 	(Ctrl+\) SIGQUIT: Ignored
 */
void	signals_wait_cmd(void);

/**
 * @brief Manipulate Signals in MiniShell when the prompt is executing some
 * command.
 * 	(Ctrl+D) The Same - Terminate
 * 	(Ctrl+C) SIGINT: New line
 * 	(Ctrl+\) SIGQUIT: New line
 *
 */
void	signals_run_cmd(void);

/**
 * @brief Get the prompt text of mini-shell
 * @param data Structure of MiniShell
 * @return char* Text of prompt
 */
char	*get_prompt(t_data *data);

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
 * @param data Structure of MiniShell
 * @return code of execution. Success or error
 */
int		call_builtin(t_data *data);

/**
 * @brief Builtins Echo - Represent the Echo command in shell (-n flag enabled)
 * @param data Structure of MiniShell
 */

int		cmd_echo(t_data *data);

/**
 * @brief Builtins Exit - Responsible to close the program.
 * @param data Structure of MiniShell
 * @return int - exit code
 */
int		cmd_exit(t_data *data);

/**
 * @brief Builtins - PWD Command - Print working directory
 * @return Integer - Result of command
 */
int		cmd_pwd(void);

/**
 * @brief Builtins - Env - Environment Variables
 * @param data Structure of MiniShell
 * @param exp_no_arg Export With no args - Show env with a pre-fix
 * @return integer - success or error
 */
int		cmd_env(t_data *data, bool exp_no_arg);

/**
 * @brief Builtins - Command Change Directory.
 * @param data Structure of MiniShell
 */
int		cmd_cd(t_data *data);

/**
 * @brief Builtins - Unset Variables
 * @param data Structure of MiniShell
 */
int		cmd_unset(t_data *data);

/**
 * @brief Verify if the name of variable is a valid name
 * @param name
 * @return true
 * @return false
 */
bool	is_valid_var_name(char *name);

/******************************************************************************/
/*End - Builtins*/
/******************************************************************************/

/******************************************************************************/
/*Begin - Utils*/
/******************************************************************************/

/**
 * @brief Deallocate memory from a pointer. Update the variable to NULL
 * (good pattern)
 * @param ptr Pointer to be free.
 */
void	free_ptr(void *ptr);

/**
 * @brief
 *
 * @param data
 * @param exit_shell
 */
void	free_data(t_data *data, bool exit_shell);

/**
 * @brief Temporary variable - Split the command with spaces
 * @param command
 * @return char**
 */
char	**split_args(char *command);

/**
 * @brief deallocate memory to pointer to pointer.
 * @param arr_str Pointer to pointer variable to be freed
 */
void	free_array_str(char **arr_str);

/**
 * @brief Handler error messages when commands will be applied.
 *
 * @param cmd Command applied
 * @param detail Details. Not required
 * @param msg Msg of error
 * @param status_code Will be the return, get in method called
 * @return int Code of error returned
 */
int		error_msg_cmd(char *cmd, char *detail, char *msg, int status_code);

/******************************************************************************/
/*End - Utils*/
/******************************************************************************/

/******************************************************************************/
/*Begin - Env*/
/******************************************************************************/
/**
 * @brief Will try to find the variable in environment variable
 * @param env All the environment variables
 * @param var Variable to search
 * @return Value of the variable
 */
char	*get_env_var_value(char **env, char *var);

/**
 * @brief Will try to find the variable in environment variable
 * @param env All the environment variables
 * @param var Variable to search
 * @return Index inside the environment variables (-1) if there is no variable
 * with this name
 */
int		get_env_var_index(char **env, char *var);

/**
 * @brief Count the number of environment variable
 * @param envp Pointer to Environment variables
 * @return int - Number or variables
 */
int		env_var_count(char **envp);

/**
 * @brief Update or insert a new environment variable. Value may be null if
 * the variable was not found.
 * If Index is positive, the variable exist! Otherwise, will be a new variable.
 * @param data Structure of MiniShell
 * @param key key of variable
 * @param value value of variable
 * @return true - Success
 * @return false - Failed
 */
bool	set_env_var(t_data *data, char *key, char *value);

/**
 * @brief Will remove a variable environment based on this index
 * @param data Structure of MiniShell
 * @param index Index to remove
 */
void	env_var_remove(t_data *data, int index);

/**
 * @brief Builtins Export - Just one argument, just export all variables.
 * Sortable and with 'declare -x'
 */
int		cmd_export(t_data *data);

/**
 * @brief Realloc memory to Environment variable
 * @param data Data structure
 * @param size Size / number of variables
 * @return char** -> New char
 */
char	**env_var_realloc(t_data *data, int size);

/******************************************************************************/
/*End - Env*/
/******************************************************************************/

#endif
