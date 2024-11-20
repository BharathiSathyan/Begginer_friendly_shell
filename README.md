# My Shell

## Overview
My Shell is a simple command-line shell program written in C. It provides a basic interface for executing commands, managing files and directories, and accessing system functionalities. The shell supports a variety of commands and features, including command history, built-in commands, and file manipulation.

## Features
- Execute built-in commands like `cd`, `exit`, `help`, and more.
- Create, remove, and list files and directories.
- Display the current date and time.
- Append content to files and create new files.
- Count files and directories within a specified path.
- Display the first and last `n` lines of a file.
- Sort and compare files.
- Install and update packages using Homebrew (macOS only).
- Maintain a history of executed commands and display frequently used commands.

## Commands Supported
The following commands are supported by My Shell:

- `help`: Displays the help information.
- `exit`: Exits the shell.
- `cd [path]`: Changes the current directory.
- `date`: Prints the current date and time.
- `man [command]`: Displays the manual for a specific command.
- `ls`: Lists files in the current directory.
- `mkdir [directory]`: Creates a new directory.
- `rmdir [directory]`: Removes a specified directory.
- `ls -a`: Lists all files, including hidden files.
- `ls -R`: Lists files recursively.
- `create_file [file]`: Creates a new file.
- `append_to_file [file]`: Appends content to the specified file.
- `word_count [directory]`: Prints the total number of files and directories in the specified directory.
- `count_file [file_extension]`: Counts the number of files with the specified extension.
- `count_nullfile`: Counts all null files.
- `numbered_cat [file]`: Prints the content of a file with line numbers.
- `move [source] [destination]`: Moves a file to a new destination.
- `remove [file]`: Removes the specified file.
- `copy [source] [destination]`: Copies a file from source to destination.
- `list_with_inode`: Lists files with their inode numbers.
- `echo [content]`: Displays the specified content.
- `head [n] [file]`: Prints the first `n` lines of the specified file.
- `tail [n] [file]`: Prints the last `n` lines of the specified file.
- `install [package]`: Installs a package using Homebrew.
- `update`: Updates all installed packages using Homebrew.
- `frequent_command [n]`: Displays the top `n` frequently used commands.
- `first_n_lines [file] [number]`: Prints the first `number` of lines of the specified file.
- `last_n_lines [file] [number]`: Prints the last `number` of lines of the specified file.

## Installation
1. Clone the repository or download the source code.
2. Navigate to the project directory.
3. Compile the program using the following command:
   ```bash
   gcc -o my_shell my_shell.c -lreadline
4. Run the shell:
    ```bash
    ./my_shell
**Usage :**

* Once the shell is running, you can type commands as you would in a regular terminal.
 * Use help to see the list of available commands. 
* To exit the shell, type exit.
