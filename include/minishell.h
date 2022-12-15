/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtomomit <mtomomit@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 08:51:11 by rlins             #+#    #+#             */
/*   Updated: 2022/12/15 09:32:57 by mtomomit         ###   ########.fr       */
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
# include <sys/stat.h> //S_ISDIR
# include <readline/readline.h> // Readline
# include <readline/history.h> // History

# define OLD_PWD "OLDPWD"
# define PWD "PWD"

# define STDOUT	STDOUT_FILENO
# define STDIN	STDIN_FILENO
# define STDERR	STDERR_FILENO

# define OR		1
# define AND	2
# define PIPE	3

# define CMD_NOT_FOUND 127
# define CMD_NOT_EXEC 126

// Color prompt
# define GREEN "\001\033[0;92m\002"
# define DEFAULT "\001\033[0;39m\002"
# define YELLOW "\001\033[0;93m\002"

typedef struct s_io
{
	int		fd_in;
	int		fd_out;
	int		std_in_bkp;
	int		std_out_bkp;
	char	*in_file;
	char	*out_file;
	char	*heredoc_delimiter;
	bool	error;
	int		cmd_index;

}	t_io;

typedef struct s_data
{
	char		*user_input;
	char		**env;
	char		*work_dir;
	char		*old_work_dir;
}	t_data;

typedef struct s_cmd
{
	char	*path;
	char	**args;
	char	**redirections;
}	t_cmd;

typedef struct s_pipe
{
	int	*fd;
}	t_pipe;

typedef struct s_special_pipe
{
	int	*fd;
}	t_special_pipe;

typedef struct s_commands
{
	pid_t			*pid;
	int				num_cmds;
	int				num_exec;
	char			**cmds;
	char			**paths;
	int				*operators;
	int				exit_value;
	t_special_pipe	*special_pipe;
	t_pipe			*pipe;
	t_io			*io;
	t_cmd			*cmd;
}	t_commands;

typedef struct s_index_data
{
	size_t	i;
	size_t	malloc_size;
	size_t	j;
}	t_index_data;

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
 * @brief Initialize IO structure (In File / out file). Redirect.
 * @param cmds Command structure
 */
void	init_io(t_commands *cmds);

/**
 * @brief Initialize the commands structure
 * @param data Structure of MiniShell
 * @param cmds Commands structure
 */
void	init_cmds(t_data *data, t_commands *cmds);

/**
 * @brief Initialize a command structure
 * @param data Structure of MiniShell
 * @param cmds Commands structure
 */
void	init_cmd(t_data *data, t_commands *cmds, int num_cmd);

void	init_single_cmd(t_data *data, t_commands *cmds, int num_cmd);

void	special_pipe(t_commands *cmds);

/**
 * @brief Validate number of arguments of Mini-shell
 * @param argc Argument Counts
 * @param argv Argument Vector
 * @return boolean. Valid / Failed
 */
bool	valid_args(int argc, char **argv);

/**
 * @brief Verify if all sentence is just space or similar char
 * @param str String / User Input
 * @return true
 * @return false
 */
bool	just_space_string(char *str);

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
/*Begin - Redirection*/
/******************************************************************************/

/**
 * @brief Responsible to manage output of redirection
 * Duplicates the input and output file descriptors.
 * Backup both to restore before. If the call is not necessary to manipulate IO
 * (no redirection) just return.
  * @param io - IO Data Structure
  * @sample: wc < arq.txt
 */
void	redirect_io(t_io *io, int index_cmd);

/**
 * @brief Restore the initial state of backups o standard input and output.
 * Without this, segmentation fault will happen. Must this to close anf
 * flag variables
 * @param io IO Data Structure
 */
void	restore_io(t_io *io);

/**
 * @brief Responsible to check if got some trouble with File descriptors and
 * files. Avoid errors like `cat <"1"
 * @param io
 * @return bool - true if it's OK with IO properties
 */
bool	check_in_out_file(t_io *io);

/**
 * @brief Will handler redirection to output file
 * will call initialization IO Structure and start process to handler file
 * @param cmds Command structure
 * @param red Redirection command
 * @param trunc truncate or append mode?
 * @sample: [ls > arq.txt] | [ls > 01 > 02] | [ls -l | wc -l >> 01]
 */
int		rd_output_handler(t_commands *cmds, char *red, bool trunc);

/**
 * @brief Will handle the type of redirection and call the right method
 * @param cmds Commands Structure
 * @param j Index of command in structure
 */
void	redirection_handler(t_commands *cmds, int j);

/**
 * @brief Verify if the command that is coming is a redirection format
 * @param cmds Commands structure
 * @param j Index of command in structure
 * @return boolean.
 */
bool	is_redirection_command(t_commands *cmds, int i);

/**
 * @brief Responsible to identify the type of redirection, and call the
 * respective method
 * @param cmds Commands structure
 * @param file File name
 * @sample: [wc < arq.txt]
 */
int		rd_input_handler(t_commands *cmds, char *file);

/**
 * @brief Verify if the previous command do not throw a exception, and just
 * return this partner
 * @param io Io Structure
 * @param in_file Indicate if must verify in file or out file
 * @return boolean
 */
bool	remove_old_file_ref(t_io *io, bool in_file);

/**
 * @brief HereDoc handler
 * @param cmds Commands structure
 * @param red - Redirection
 */
void	rd_heredoc(t_commands *cmds, char *red);

/******************************************************************************/
/*end - Redirection*/
/******************************************************************************/

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

bool	is_builtin_without_output(t_commands *cmds);

/**
 * @brief Call correct function from Builtin command
 * @param data Structure of MiniShell
 * @param cmds Command Structure
 * @return code of execution. Success or error
 */
int		call_builtin(t_data *data, t_commands *cmds, int num_cmd);

/**
 * @brief Builtins Echo - Represent the Echo command in shell (-n flag enabled)
 * @param cmds Command Structure
 * @return int - Code of execution
 */
int		cmd_echo(t_commands *cmds, int num_cmd);

/**
 * @brief Builtins Exit - Responsible to close the program.
 * @param data Structure of MiniShell
 * @return int - exit code
 */
int		cmd_exit(t_data *data, t_commands *cmds, int num_cmd);

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
int		cmd_env(t_data *data, t_commands *cmds, int num_cmd);

/**
 * @brief Builtins - Command Change Directory.
 * @param data Structure of MiniShell
 */
int		cmd_cd(t_data *data, t_commands *cmds, int num_cmd);

/**
 * @brief Builtins - Unset Variables
 * @param data Structure of MiniShell
 */
int		cmd_unset(t_data *data, t_commands *cmds, int num_cmd);

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
 * @brief Set the pipe fds to the command. The index will be passed to in or out
 * base in index passed between commands
 * @param cmds - Data Object Command
 * @param index - Index of command executed in the current time
 */
void	set_pipe_fds(t_commands *cmds, int index);

/**
 * @brief Will close File Descriptors from command.
 * @param cmds Commands Structure
 * @param index Index to current cmd. -1 if is in all scope / all commands
 * @param close_both Flag to indicate to close both
 */
void	close_pipe_fds(t_commands *cmds);

/**
 * @brief Will return the value of the structures
 * @param cmds Structure of commands
 */
void	debug_structs(t_commands *cmds, bool show_path);

/**
 * @brief Deallocate memory from a pointer. Update the variable to NULL
 * (good pattern)
 * @param ptr Pointer to be free.
 */
void	free_ptr(void *ptr);

/**
 * @brief Close File descriptor, if opened.
 * @param cmds Structure of Commands
 * @param reset_io if true, will restore stdIn/stdOut Bkp
 */
void	close_fds(t_commands *cmds, bool reset_io);

/**
 * @brief Free IO structure.
 * Unlink used to drop temp file to heredoc
 * @param io IO Structure
*/
void	free_io(t_io *io);

/**
 * @brief Will free Data structure in mini-shell
 * @param data Data structure
 * @param Boolean - exit_shell. Indicate to terminate program
 */
void	free_data(t_data *data, bool exit_shell);

/**
 * @brief Temporary variable - Split the command with spaces
 * @param command
 * @return char**
 */
char	**split_args(char *command);

/**
 * @brief Will join strings
 * @param str Str original
 * @param add Text to add
 * @return string concatenated
 */
char	*join_strs(char *str, char *add);

/**
 * @brief Remove (by ref) the quotes from a string.
 * Will call recursively until return the new string without quotes
 * @param str
 */
void	remove_quotes(char *str);

/**
 * @brief deallocate memory to pointer to pointer.
 * @param arr_str Pointer to pointer variable to be freed
 */
void	free_array_str(char **arr_str);

/**
 * @brief Free all the terms of cmds
 * @param cmds Commands structure
 */
void	free_cmds(t_commands *cmds);

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
/*Begin - Execute*/
/******************************************************************************/

/**
 * @brief Responsible to manage the execution. Will call the method to call
 * local bins or path bins.
 * @param data Data structure Minishell
 * @param cmds Cmds structure
 * @return int
 */
int		exec_handler(t_data *data, t_commands *cmds);

/**
 * @brief Verify if the command passed is a directory. Necessary to throw the
 * correct message
 * @param cmd Command to check
 * @return true - Input passed is a dir
 * @return false - Itś not a dir
 */
bool	input_is_dir(char *cmd);

/**
 * @brief Verify if command is not found.
 * This will handler the possibles of the command was not found previously,
 * and return the msg and code of exit
 * @param data TypeDef in MiniShell
 * @param cmds
 * @return int
 */
int		validate_cmd_not_found(t_data *data, char *cmd);

/**
 * @brief Exit free cmd - refactoring execute class
 * @param data Data Structure
 * @param cmds Commands Structuree
 * @param status_code Status code
 */
void	free_exit_cmd(t_data *data, t_commands *cmds, int status_code);

int	exec_child(t_data *data, t_commands *cmds, int num_cmd);

void	verify_operators(t_data *data, t_commands *cmds, int num_cmd);

/**
 * @brief Check if command must be execute by variable path or if is a
 * local binary to execute
 * @param data Data Structure
 * @param cmds Cmds Structure
 * @param i - Index of command in execution this time
 * @return int
 */
int	execute_cmd(t_data *data, t_commands *cmds, int num_cmd);

/******************************************************************************/
/*End - Execute*/
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
 * @return bool - Success / Failed
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
int		cmd_export(t_data *data, t_commands *cmds, int num_cmd);

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

/**
 * @brief Tokenize the string based on parenthesis and operators
 * @param s User input
 * @param cmds Structure of commands
 * @return char** -> Tokenizer string
 */
char	**lexer(char const *s, t_commands *cmds);

/**
 * @brief Copy the user input into the tokenize string
 * @param s User input
 * @param str Tokenized string
 * @param countc Number of divisions of user input
 */
void	putchar_lexer(char const *s, char **str, size_t countc);

/**
 * @brief Handle the errors that could be present in the user input
 * @param i_data Index variable
 * @param s User input
 * @param cmds Structure of commands
 */
void	lexer_errors(t_index_data *i_data, const char *s, t_commands *cmds);

/**
 * @brief Handle the parenthesis present in the user input
 * @param s User input
 * @param cmds Structure of commands
 */
void	lexer_parenthesis(const char *s, t_commands *cmds);

/**
 * @brief Handle errors that may be present in user input
 * @param i_data Index variable
 * @param s User input
 * @param cmds Structure of commands
 */
void	quotes_error(t_index_data *i_data, const char *s, t_commands *cmds);

/**
 * @brief Handle the redirections present in the user input
 * @param s User input
 * @param cmds Structure of commands
 */
void	lexer_redirections(const char *s, t_commands *cmds);

void	lexer_operators(const char *s, t_commands *cmds);

/******************************************************************************/
/*End - Lexer*/
/******************************************************************************/

/******************************************************************************/
/*Begin - Parser*/
/******************************************************************************/

/**
 * @brief Get the cmd path object. Will pass the name of the command, and this
 * will be responsible to return all path of the command
 * @param data
 * @param cmds
 * @param index - Index of command in cmds Structure
 * @return char*
 */
char	*get_cmd_path(t_commands *cmds, int index);

/**
 * @brief Tokenize command based on their arguments
 * @param s Command
 * @return char** -> Command split in arguments
 */
char	**parser(char *s);

/**
 * @brief Copy the command into the tokenize string
 * @param s Command of user input
 * @param str Split command
 * @param countc Number of arguments
 */
void	putchar_parser(char *s, char **str, size_t countc);

/**
 * @brief Swap the '$' in input for environment variable value
 * @param i_data index variable
 * @param s Command of user input
 * @param data Data structure
 */
char	*handle_env(t_index_data *i_data, char *s, t_data *data);

/**
 * @brief Search the existence of '$' in that part of the input
 * @param data Data structure
 * @param cmds Structure of commands
 * @param num_cmd The number of the command
 */
void	find_dollar_sign(t_data *data, t_commands *cmds, int num_cmd);

/**
 * @brief Search if exists redirection in the command
 * @param s Command
 */
char	**handle_redirection(char *s);

/**
 * @brief Copy the redirection in a new object
 * @param s Command
 * @param str An array that contains all the redirections
 * @param countc Number of redirections
 */
void	putchar_redirection(char *s, char **str, size_t countc);

/**
 * @brief Remove the redirection from the command
 * @param s Command
 */
char	*rm_redirection(char *s);

/**
 * @brief Copy the command now without the redirection in a new object
 * @param s Command
 * @param str An array that contain the new command
 */
void	copy_cmd(char *s, char *new_str);

/**
 * @brief Copy the command now without the redirection in a new object
 * @param s Command
 * @param str An array that contain the new command
 */
void	find_export_cmd(t_commands *cmds, int num_cmd);

char	**rm_spaces(char const *s);
void	putchar_split(char const *s, char **str, size_t countc);

/******************************************************************************/
/*End - Parser*/
/******************************************************************************/

#endif
