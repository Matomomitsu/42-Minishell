<p align="center"><img src="https://i2.wp.com/www.aponia-dental-center.com/fachzahnarztliche-praxis/wp-content/uploads/2014/01/work-in-progress.png?fit=286%2C253" alt="Working Progress"> </p>

<div align="center">

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

## Todo's
* Prompt display
* Command history (up and down arrows)
* System executables available from the environment (`ls`, `cat`, `grep`, etc.)
* Builtin commands:
  * `echo` (and option `-n`)
  * `cd` (with only a relative or absolute path)
  * `pwd` (no options)
  * `export` (no options) - Export  variables in bash
  * `unset` (no options)
  * `env` (no options or arguments)
  * `exit` (with exit number but no other options)

* Pipes: `|` which redirect output from one command to input for the next

* Re-directions:
  * `>` redirects output
  * `>>` redirects output in append mode
  * `<` redirects input
  * `<< DELIMITER` displays a new prompt, reads user input until reaching
  	`DELIMITER`, redirects user input to command input (does not update history)


* Environment variables (`$USER` or `$VAR`) that expand to their values.
  * `$?` expands to the exit status of the most recently executed foreground pipeline.


* Signals:
  * `ctrl-c` displays a new prompt line. SIGINT: SIGINT resets the user input
  prompt to a new blank line.
  * `ctrl-d` exits minishell.
  * `ctrl-\` does nothing. SIGQUIT: is ignored.

* Global variable:

## Links
* <a href="https://www.makeuseof.com/shell-builtin-commands-in-linux/">How to Identify a Shell Builtin Command</a>
