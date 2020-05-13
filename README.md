# Welcome to Stack Programming Language

Basic programming with few commands.


# Commands

push <number>  - push a number on to stack (e.g. push 23)
pop            - pop a number from stack (e.g. pop )
+              - add last two numbers in  stack (e.g. + )
-              - subract last two numbers in  stack (e.g. - )
*              - multiply last two numbers in  stack (e.g. * )
/              - divide last two numbers in  stack (e.g. / )
%              - modulo last two numbers in  stack (e.g. % )
>              - compare last two numbers in  stack (e.g. > )
<              - compare last two numbers in  stack (e.g. < )
>=             - compare last two numbers in  stack (e.g. >= )
<=             - compare last two numbers in  stack (e.g. <= )
!=             - compare last two numbers in  stack (e.g. != )
==             - compare last two numbers in  stack (e.g. == )
jmp <number>   - jump code to given line number (e.g. jmp 23 )
jmpt <number>  - jump code to given line number if last stack value is zero (e.g. jmpt 23 )
jmpf <number>  - jmp code to given line number if last stack value is not zero (e.g. jmpf 23 )
print          - prints last stack value (e.g. print )
get            - wait for user to enter value and push to stack (e.g. get )
dup            - duplicate last value in stack (e.g. dup )
exit           - exit the program (e.g. exit )


## How to build

Build with single file "stack.cpp".
Supports all platform.
No external dependency.
Check compile.sh file for reference.


## How to run

stack <input file name> <-p> <-d>
option -p print the complied code
option -d for debugging, execute each step on keypress.

