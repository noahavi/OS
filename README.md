Unix command shell program that supports the following commands:

changedir directory

Short for change directory. It is used to change the current directory (which must be an internal variable) to the specified one. If the specified directory does not exist, it should keep the old directory and write an error message. 

whereami

Prints the current directory.

lastcommands [-c]

Without the parameter, prints out the recently typed commands (with their arguments). If “-c” is passed, it clears the list of recently typed commands 

quit

terminates the mysh shell

run program[parameters]

The argument “program” is the program to execute. If the argument starts with a “/” (such as /usr/bin/xterm, the shell should interpret it as a full path. Otherwise, the program will be interpreted as a relative path starting from the current directory. 

The program will be executed with the optional “parameters”. It uses fork() + exec() to start the program with the corresponding parameters, and waits until the program terminates (use the waitpid() call). 

background program [parameters]

It is similar to the run command, but it immediately prints the PID of the program it started, and returns the prompt.

exterminate PID

Immediately terminate the program with the specific PID (presumably started from this command line interpreter). Use the kill() function call to send a SIGKILL signal to the program.

exterminateall

Which immediately terminates all the programs previously started by the mysh shell which had not been previously terminated by it, or by exterminate. 
