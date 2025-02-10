<h1 align="center">minishell</h1>
<h3 align="center">42Paris School Project</h3>

<p align="center">
  <img src="https://img.shields.io/badge/Language-C-blue.svg" alt="Language">
  <img src="https://img.shields.io/badge/Status-Completed-brightgreen.svg" alt="Status">
  <img src="https://img.shields.io/badge/Score-101%25-brightgreen.svg" alt="Score">
</p>

  
## About the Project

`minishell` is a custom shell implementation in C, developed as part of the 42Paris curriculum. This project helped me appreciate the work done by the older generation of developers, gain a better understanding of how the shell works, and solidify my knowledge and skills in C and shell programming.

## Features

- Display a prompt when waiting for a new command.
- Working command history.
- Execute commands based on the PATH variable or using relative/absolute paths.
- Handle single and double quotes.
- Implement redirections (`<`, `>`, `<<`, `>>`).
- Implement pipes (`|`).
- Handle environment variables (`$`).
- Handle special variables (`$?`).
- Handle `ctrl-C`, `ctrl-D`, and `ctrl-\` like in bash.
- Built-in commands: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`.

## Technical Details

- **Language**: C
- **External Libraries**: `readline`
- **System Calls**: `fork`, `execve`, `pipe`, `dup2`, `signal`, etc.

## Getting Started

### Prerequisites

- GCC or any C compiler
- GNU Make

### Installation

1. Clone the repository:
   ```sh
   git clone https://github.com/Agrippa2023/minishell.git
   cd minishell
   ```

2. Build the project:
   ```sh
   make
   ```

### Usage

Run the shell:
```sh
./minishell
```

## Project Structure

- `src/`: Source files
- `include/`: Header files
- `libft/`: Custom C library used throughout the 42Paris curriculum
  - Contains various utility functions like `ft_atoi`, `ft_strlen`, `ft_split`, etc.
- `Makefile`: Build script

## Screenshots

<p align="center">
  <img src="media/prompt.gif" alt="minishell Prompt">
  <img src="media/commands.gif" alt="minishell Commands">
</p>

## Acknowledgements

This project was developed as part of the 42Paris curriculum. Special thanks to the 42 community for their support and resources.

## License

Distributed under the MIT License. See `LICENSE` for more information.

## Connect with Me

<p align="left">
  <a href="https://www.linkedin.com/in/amine-ouichou-168236345" target="blank"><img align="center" src="https://raw.githubusercontent.com/rahuldkjain/github-profile-readme-generator/master/src/images/icons/Social/linked-in-alt.svg" alt="amine ouichou" height="30" width="40" />
</p>

