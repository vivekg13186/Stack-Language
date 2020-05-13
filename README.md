# Welcome to Stack Programming Language

Basic programming with few commands.


# Commands

| Command     | Description | Example|
| ----------- | ----------- |----------- |
| push <number>      | push a number on to stack       | push 23|
| pop   | pop a number from stack        | pop|
| +   | add last two numbers in  stack        | +|
| -   | subract last two numbers in  stack        | -|
| *   | multiply last two numbers in  stack        | * |
| /   | divide last two numbers in  stack        | /|
| %   | modulo last two numbers in  stack        | %|
| >   | compare last two numbers in  stack        | >|
| <   | compare last two numbers in  stack       | <|
| >=   | compare last two numbers in  stack        | <= |
| <=   | compare last two numbers in  stack        | >=|
| !=   | compare last two numbers in  stack        | !=|
| ==   | compare last two numbers in  stack        | ==|
| jmp <number>   | jump code to given line number        | jmp 23|
| jmpt <number>   | jump code to given line number if last stack value is zero       | jmpt 23|
| jmpf <number>   | jmp code to given line number if last stack value is not zero        |  jmpf 23 |
| print   | prints last stack value       | print|
| get   | wait for user to enter value and push to stack       | get|
| dup   | duplicate last value in stack        | dup|
| exit   | exit the program        | exit|


## How to build

Build with single file "stack.cpp".
Supports all platform.
No external dependency.
Check compile.sh file for reference.


## How to run

stack <input file name> <-p> <-d>
- option -p print the complied code
- option -d for debugging, execute each step on keypress.

## Examples
Sample file in test folder

