/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtomomit <mtomomit@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 08:51:11 by rlins             #+#    #+#             */
/*   Updated: 2022/11/22 20:34:53 by mtomomit         ###   ########.fr       */
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
# include <stdbool.h>

# include <readline/readline.h> // Readline
# include <readline/history.h> // History

# define INV_ARGS "Invalid Arguments\n"

# define OLD_PWD "OLDPWD"
# define PWD "PWD"

# define STDOUT	STDOUT_FILENO
# define STDIN	STDIN_FILENO
# define STDERR	STDERR_FILENO

# define OR		1
# define AND	2
# define PIPE	3

// Color prompt
# define GREEN "\001\033[0;92m\002"
# define DEFAULT "\001\033[0;39m\002"
# define YELLOW "\001\033[0;93m\002"

typedef struct s_command
{
	char	*cmd;
	char	**args;
}	t_command;

typedef struct s_data
{
	char		*user_input;
	char		**env;
	char		*work_dir;
	char		*old_work_dir;
	int			old_exit_value;
	t_command	*command;
	int			exit_value;
}	t_data;

typedef struct s_cmd
{
	char		*cmd;
	char		*path;
	char		**args;
	char		*infile;
	char		*outfile;
}	t_cmd;

typedef struct s_commands
{
	pid_t		*pid;
	int			num_cmds;
	int			num_exec;
	char		**cmds;
	char		**paths;
	int			*operators;
	int			**pipe_fd;
	t_cmd		*cmd;
}	t_commands;

typedef struct s_index_data
{
	size_t	i;
	size_t	malloc_size;
	size_t	j;
}	t_index_data;

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

char	*get_prompt(t_data *data);

void	init_cmds(t_data *data, t_commands *cmds);

/******************************************************************************/
/*End - Initialization*/
/******************************************************************************/

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
void	signals_handler(void);

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
 */
void	call_builtin(t_data *data);

/**
 * @brief Builtins Echo - Represent the Echo command in shell (-n flag enabled)
 * @param data Structure of MiniShell
 */

void	cmd_echo(t_data *data);

/**
 * @brief Builtins Exit - Responsible to close the program.
 * @param data Structure of MiniShell
 */
void	cmd_exit(t_data *data);

/**
 * @brief Builtins - PWD Command - Print working directory
 * MaxSize:
 * https://serverfault.com/questions/9546/filename-length-limits-on-linux
 */
void	cmd_pwd(void);

/**
 * @brief Builtins - Env - Environment Variables
 * @param data Structure of MiniShell
 * @param exp_no_arg Export With no args - Show env with a pre-fix
 */
void	cmd_env(t_data *data, bool exp_no_arg);

/** TODO: Verificar se há mais possitilidades aqui (passar parâmetros que nao
 * foi atendido ainda)
 * @brief Builtins - Command Change Directory.
 * @param data Structure of MiniShell
 */
void	cmd_cd(t_data *data);

/**
 * @brief Builtins - Unset Variables
 * @param data Structure of MiniShell
 */
void	cmd_unset(t_data *data);

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

void	free_cmds(t_commands *cmds);

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
void	cmd_export(t_data *data);

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

/******************************************************************************/
/*Begin - Lexer*/
/******************************************************************************/

char	**lexer(char const *s, t_data *data);
void	putchar_lexer(char const *s, char **str, size_t countc);
void	lexer_errors(t_index_data *i_data, const char *s, t_data *data);

/******************************************************************************/
/*End - Lexer*/
/******************************************************************************/

/******************************************************************************/
/*Begin - Parser*/
/******************************************************************************/

void	putchar_parser(char const *s, char **str, size_t countc);

/******************************************************************************/
/*End - Parser*/
/******************************************************************************/

#endif
