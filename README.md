# Pipex

A project from the 42 curriculum that recreates the behavior of the Unix pipeline, allowing the output of one command to be passed as input to another. This project builds skills in
forking, redirection, and file handling in C.

## **Overview**

`pipex` emulates the shell’s pipeline functionality. Given two commands and two files, the program reads from the first file, pipes the output through the first command, and then passes it to the second command before writing the final output to the second file.

## **Features**

- Replicates basic shell piping for two commands.
- Demonstrates use of `fork`, `pipe`, `dup2`, and `execve` system calls.
- Handles error cases, such as command or file access issues.

## **Usage**

### 1. Cloning the Repository

To begin, clone the repository:
```bash
git clone https://github.com/koodikommando/pipex.git
cd pipex
```

### 2. Compilation

Compile `pipex` using the provided Makefile:
```bash
make
```

### 3. Running Pipex

```bash
./pipex file1 cmd1 cmd2 file2
```

- `file1`: Input file
- `cmd1`: First command to process the input
- `cmd2`: Second command to process the output of `cmd1`
- `file2`: Output file

### 4. Example Usage

```bash
./pipex infile "grep foo" "wc -l" outfile
```

This command takes `infile`, processes lines containing "foo" with `grep`, counts them with `wc -l`, and writes the result to `outfile`.

