
<div align="center">
TODO: nominette

TODO: teste do lucas

[![HitCount](https://hits.dwyl.com/rlinsdev/42-Minishell-aux.svg?style=flat-square&show=unique)](http://hits.dwyl.com/rlinsdev/42-Minishell-aux)

</div>

<p align="center"><img src="https://miro.medium.com/max/450/1*ZE2T9JllKfTOQ90oDwqGmQ.png" alt="Bash 1"> </p>


# MiniShell
Project to test and detail all the external functions allowed



## Definition
* One line definition: A shell is an interface that allows you to interact with the kernel of an operating system.
* Lexer: TODO
* Parser: TODO
* HereDoc: TODO

## External functs.
| function | Description |
|-						|-		 |
|`access` 				| check access (used in pipex)
|`execve` 				| exec cmd. (used in pipex)
|`fork` 				| divide process in 2. Child and parent
|`free` 				| free ptr
|`getpwd` 				| get pwd
|`malloc` 				| allocate memory space
|`open` 				| open file
|`opendir` 				| open specific directory
|`pipe` 				| Pipe (learned in pipex)
|`dup2` 				| duplicate FD and change (learned in pipex)
|`printf` 				| weird pdf allow this... But it's ok
|`read` 				| read from File Descriptor
|`readline` 			| waiting prompt
|`signal` 				| Change the process, by signal passed. Take other action
|`write` 				| write
|`rl_`					| handler with prompt
|`add_history`			| add cmd in history
|`waitpid`				| wait child exec
|`chdir`				| change directory
|`stat`					| get properties from path
|`unlink`				| drop a file
|`strerror`				| describes error
|`getenv`				| get environment variables



## Todo's
* Prompt display
* Command history (up and down arrows)
* System executables available from the environment (`ls`, `cat`, `grep`, etc.)
* Builtin commands:
  * `echo` Allow option `-n`
  * `cd` Relative or absolute path
  * `pwd` No args
  * `export`Export variables in bash
  * `unset` No args
  * `env` No options. No args
  * `exit` Allow exit number

* Pipes: `|` which redirect output from one command to input for the next

* Re-directions:
  * `>` redirects output
  * `>>` redirects output in append mode
  * `<` redirects input
  * `<< DELIMITER` displays a new prompt. HereDoc
  	`DELIMITER` redirects user input to command input


  * `$?` expands to the exit status of the most recently executed foreground pipeline.


* Signals:
  * `ctrl-c` displays a new prompt line. SIGINT: SIGINT resets the user input
  prompt to a new blank line.
  * `ctrl-d` exit.
  * `ctrl-\` does nothing.

## Tests:
xxxx

## Links
* <a href="https://www.makeuseof.com/shell-builtin-commands-in-linux/">How to Identify a Shell Builtin Command</a>

### Functions
* `stat`: https://codeforwin.org/2018/03/c-program-find-file-properties-using-stat-function.html#:~:text=stat()%20function%20in%20C&text=stat()%20function%20is%20used,h%20header%20file.
