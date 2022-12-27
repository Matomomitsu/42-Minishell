
<div align="center">

[![HitCount](https://hits.dwyl.com/rlinsdev/42-Minishell-aux.svg?style=flat-square&show=unique)](http://hits.dwyl.com/rlinsdev/42-Minishell-aux)
![norminette](https://github.com/rlinsdev/42-Minishell/workflows/norminette/badge.svg?branch=main)

</div>

<!-- <p align="center"><img src="https://miro.medium.com/max/450/1*ZE2T9JllKfTOQ90oDwqGmQ.png" alt="Bash 1"> </p> -->
<p align="center"><img src="https://game.42sp.org.br/static/assets/achievements/minishellm.png" alt="Minishell"> </p>


# MiniShell
Minishell is a 42 school team project write in C language. It implements redirections, pipes, environment variable, expansions, builtin commands, etc.



## Definitions
* One line definition: A shell is an interface that allows you to interact with the kernel of an operating system.


## External functs.
| function | Description |
|-						|-		 |
|`access` 				| check access (used in pipex)
|`execve` 				| exec cmd (used in pipex)
|`fork` 				| divide process in 2. Child and parent
|`free` 				| free ptr
|`getpwd` 				| get pwd
|`malloc` 				| allocate memory space
|`open` 				| open file
|`opendir` 				| open specific directory
|`pipe` 				| Pipe (learned in pipex)
|`dup2` 				| duplicate FD and change (learned in pipex)
|`printf` 				| (weird pdf allow this... But it's ok)
|`read` 				| read from File Descriptor
|`readline` 			| waiting prompt
|`signal` 				| Change the process, by signal passed. Take other action
|`write` 				| write
|`rl_*`					| handler with prompt
|`add_history`			| add cmd in history
|`waitpid`				| wait child exec
|`chdir`				| change directory
|`stat`					| get properties from path
|`unlink`				| drop a file
|`strerror`				| describes error
|`getenv`				| get environment variables


## Commands
To run the program:
```shell
./minishell
```
Check Leaks:
```shell
make valgrind
```



## Implemented:
* Prompt display
* Command history (up and down arrows)
* System executables available from the environment (`ls`, `cat`, `grep`, etc.)
* Builtin commands:
  * `echo`: Allow option `-n`
  * `cd`: Relative or absolute path
  * `pwd`: No args
  * `export`: Export variables in bash
  * `unset`: No args
  * `env`: No options. No args
  * `exit`: Allow exit number

* Pipes: `|` which redirect output from one command to input for the next

* Re-directions:
  * `>` redirects output
  * `>>` redirects output in append mode
  * `<` redirects input
  * `<< DELIMITER` displays a new prompt. HereDoc
  	`DELIMITER` redirects user input to command input


  * `$?` expands to the exit status of the most recently executed foreground pipeline.


* Signals:
  * `ctrl-c`: displays a new prompt line. SIGINT: SIGINT resets the user input
  prompt to a new blank line.
  * `ctrl-d`: exit.
  * `ctrl-\`: does nothing.

* Priorities operator `||` and `&&`

* Lexer: It helps you to convert a sequence of characters into a sequence of tokens

* Parser: The parser will then check for invalid syntax and create a kind of command

## Bonus
* And, or (&&, ||)


## Tests:
* <a href="https://github.com/LucasKuhn/minishell_tester/">Minishell Tester - Lucas Kuhn</a>

## Links
* <a href="https://www.makeuseof.com/shell-builtin-commands-in-linux/">How to Identify a Shell Builtin Command</a>
* <a href="https://www.youtube.com/playlist?list=PLucm8g_ezqNrYgjXC8_CgbvHbvI7dDfhs">Course - Shell script (BOSON - pt-br)</a>
* <a href="https://www.youtube.com/playlist?list=PLFAC320731F539902">Unix terminals and shells</a>
* <a href="https://www.guru99.com/compiler-design-lexical-analysis.html">Lexer</a>


