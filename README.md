#  OS Experiment--MyShell

## Description

This experimental project is similar to the Linux shell terminal, named myshell, through C/C++ programming, design string parsing algorithm, combined with system calls, the system commands under Linux are implemented, so that users can use the command line to interact with the system.

## Background

Shell, commonly known as shell (used to distinguish from the core), refers to the software (command parser) that provides "user interface". At the same time, it is a programming language. As a command language, it interprets and executes commands entered by users interactively or automatically interprets and executes a series of preset commands.

In the basic course of operating system, we understand some system calls commonly used under Linux and UNIX systems through theoretical study and experimental practice. In order to better understand these abstract system call concepts, students in the class form a group for programming practice. In order to improve the programming ability, the team members use the system calls they have learned to design, write and implement a terminal command line execution program similar to shell, so as to master the relevant knowledge.


## Requirement Analysis

### Functional Requirements Analysis 

1. Myshell program needs to read the user's input command (exit exit).
2. Myshell program can save the input command line. Call the execution function and pass the processed command to the execution function.
3. Myshell handles the incoming commands and parameters correctly.
4. Myshell executes the processed commands and parameters, and outputs or saves the execution results to the file system.
5. Myshell gives an error prompt for the wrong command input.

### Non Functional Requirements Analysis

1. Reduce the complexity of the code as much as possible.
2. The code has good interactivity.

### Project expected implementation command

mv, ls, touch, mkdir, rmdir, cp, cd, pwd, grep, history, cat, rm, exit

### Function Description

- mv: move file or modify file name
- ls: display file list
- touch: create a new file
- mkdir: create a new folder (including recursive creation)
- rmdir: delete non empty directory
- cp: copy file
- cd: switch directory
- pwd: displays the absolute path of the current working path
- grep: find character (only for pipeline command)
- history: view history command
- cat: view file content
- rm: delete file
- exit: exit myshell

## Development and Operation Environment

Development environment of standard C language under Linux system environment (C99 standard)

