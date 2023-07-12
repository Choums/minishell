# Minishell
Minishell is a simple shell implemented in C. It provides a command-line interface where users can enter commands to be executed.
The shell supports various features such as command execution, history, redirections, pipes, environment variables, and built-in commands.

## Usage
```
make all
./minishell
```

## Features
- **Prompt**: Minishell displays a prompt, waiting for a new command to be entered.

- **History**: The shell keeps track of the command history, allowing users to navigate through previously entered commands using the arrow keys.

- **Command Execution**: Minishell searches for and executes the appropriate executable based on the PATH environment variable or a relative/absolute path.

- **Single Quotes**: The shell handles single quotes (```'```) by preventing the interpretation of metacharacters within the quoted sequence.

- **Double Quotes**: Minishell handles double quotes (```"```) by preventing the interpretation of metacharacters within the quoted sequence, except for the ```$``` sign.

- **Redirections**: The shell supports input and output redirections using the following symbols:
  + ```<``` redirects input.
  + ```>``` redirects output.
  + ```<<``` reads input until a line containing a specified delimiter is encountered (history is not updated).
  + ```>>``` redirects output in append mode.

- **Pipes**: Minishell supports pipes (```|```) to connect the output of one command as the input to another command in a pipeline.

- **Environment Variables**: The shell handles environment variables (indicated by $ followed by a sequence of characters) by substituting them with their respective content.

- **$? Variable**: The shell substitutes $? with the exit status of the last foreground pipeline executed.

- The shell handles the following key combinations:
  + ```Ctrl-C``` displays a new prompt on a new line.
  + ```Ctrl-D``` exits the shell.
  + ```Ctrl-\``` does nothing.

- **Built-in Commands**:
  + ```echo``` with the -n option.
  + ```cd``` with a relative or absolute path, can also be used with ```-``` or ```~```.
  + ```pwd``` without any options.
  + ```export``` without any options.
  + ```unset``` without any options.
  + ```env``` without any options or arguments.
  + ```exit``` without any options.

  ## Examples
  - Redirect input/output: ```command < input.txt > output.txt```
  - Set environment variables: ```export VARIABLE_NAME=value```
  - Change directory: ```cd /path/to/directory```
  - Use the $? variable to display the exit status of the last command: ```echo $?```
  - ```env | grep "PATH" > output.txt```
  - ```ls -l | grep -v ".txt" >> files.txt```
  - ``` cat | ls | cat ```
