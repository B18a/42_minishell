<p align="center">
  <img src="https://github.com/B18a/42-project-badges/blob/main/badges/minishelle.png">
</p>

<h1 align="center">
  Project - minishell
</h1>

The "Minishell" project focuses on creating a simple shell, similar to Bash, allowing interaction with the operating system through commands. You’ll learn about processes, file descriptors, and implementing features like command history, input/output redirection, and handling environment variables.

- **Shell Features:**
  - Display a prompt for user input.
  - Maintain a command history.
  - Search and execute commands based on the PATH variable.
  - Handle single and double quotes for quoting.
  - Implement input/output redirection (`<`, `>`, `<<`, `>>`).
  - Support pipes (`|`) for connecting command outputs.
  - Expand environment variables and the exit status of the last command.
  - Handle control signals (Ctrl-C, Ctrl-D, Ctrl-\).
- **Built-in Commands:** Implement `echo`, `cd`, `pwd`, `export`, `unset`, `env`, and `exit`.

You’ll need to follow strict coding guidelines, avoid global variables (except for a signal handler), and manage memory efficiently while implementing these features.
*Summary generated with chatgpt
