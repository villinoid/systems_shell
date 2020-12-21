## FVY
by Francesco Siniscalco, Vladislav Vostrikov and Yulin Zheng

Team FVY

### Features:
- Can fork and execute commands 
    - Allows for changing of work directory (cd) and exiting (exit)
    - Allows for putting multiple spaces between arguments
    - Will trim \n 
    - If there is no input and that is entered, the process will restart and prompt for input again
- Can run multiple commands on the same line using ";" as a separator
- Redirects input and output using > and <
- The < is not bound by position
    - “tr a-z < file.txt A-Z” has the same output as “tr a-z A-Z < file.txt”
- Supports the use of > and < at the same time
	- Only works with two >,< total in the order “cmd -args < read_file > write_file”
- Allows for passing of output from one process to another using |
	- Supports only one pipe in a line

---

### Attempted:

- Attempted to parse input in strings (ex: echo “Hello World”)
- Attempted to parse escape characters
- Attempted to support two pipes in a line, but had issues with forking
- Attempted to support use of pipes and redirection in the same line, but had output issues

---

### Bugs:

- When redirecting, a space must be put between the > or < and the file name, otherwise
- Combining pipes and redirection operators will not work
- Will not work if order of redirection is switched: > then < 
- Putting two ";" separators next to each other will break the program

---

### Files & Function Headers:
#### exec.c
* Handles the parsing and execution of input
```
/*======== char **parse_args()==========
Inputs: char **return_args
	char *line
char separator
Returns: a pointer array containing the parts of a separated string

Uses strsep to separate a string into an array of pointers given a certain separator value and returns the array.
 ====================*/

/*========int main_exec()==========
Inputs: char ** args
char * in_string
Returns:  0 or 1 if parent function, meaning no errors and -1 if child function to signal to parent function to end; main purpose of this function is to execute all the input commands and fork when necessary; also is where a lot of the redirection components are put together.

If redirection or piping is detected, the function moves on to use stdin_redirect() and stdout_redirect() as well as pipe_redirect_and_fork() among others to execute commands or fork if necessary (also detects if multiple redirection operators are used and parses that as required). Otherwise if a simple command or an exit or a change in directory is requested, that is executed in an else statement and the necessary forks are performed.
====================*/

/*========void format_whitespace()==========
Inputs: char *line
Returns:  string with all whitespace converted ‘ ‘

Converts all whitespace to ‘ ‘ using the assignment operator.
 ====================*/

/*========char *trim_spaces()==========
Inputs: char *line
Returns:a modified string without whitespace on either end

Puts nulls at terminating whitespaces and moves the pointer forward for whitespaces at the beginning.
 ====================*/

```
#### redirect.c
* Handles all redirection and piping 
```
/*========char **redir_parse()==========
Inputs: char **original_args
Returns: An array of pointers that has all redirection and piping operators removed, the locations of which are saved using char **count_sep()

Runs a loop through an array of pointers of commands, their arguments and redirection operators. If the pointer is not a redirection operator, it is added to a malloced array and then the array is returned.
====================*/

/*========char **count_sep()==========
Inputs: char **args
Returns: An array of arrays containing redirection operators and their position in the input.

Runs a while loop through an array of pointers and checks if each element is a redirection operator. If it is, the position in the input, along with the operator is stored and added to an array which is returned.
 ====================*/

/*========int pos_length()==========
Inputs: char **pos
Returns: how many redirection operators there are

Runs a loop through the array in which position of redirection operator is stored and returns how many of them there are.
 ====================*/

/*========char **stdin_arr()==========
Inputs: char **args
        int pos
Returns: an array of pointers removing the file in input direction and containing only commands and arguments 

Runs a loop through the array of commands, arguments and files and since the position of files are known, they are removed in the loop.
 ====================*/

/*========int redir_check()==========
Inputs: char* command
Returns: an integer (1) if redirection is involved in input and (0) if not

Runs a loop through the input to check if >, < or | is involved.
 ====================*/

/*========void stdout_redirect()==========
Inputs: char *file_name
        char **command
Returns: does not return anything; executes a command and redirects its output into an output file

Uses dup and dup2 (with backups created) to swap stdout and an output file, opened by the function, on the file table so that the output of a command is redirected to the output file.
 ====================*/

/*========void stdin_redirect()==========
Inputs: char *file_name 
        char **command
Returns: does not return anything; redirects the contents of an input file into the command

Uses dup and dup2 (with backups created) to swap stdin and an input file on the file table so that the input file is redirected to the command to be interpreted and executed.
 ====================*/

/*========void double_redirect()==========
Inputs: char *fn1
        char *fn2
        char **command 
Returns: does not return anything; redirects the content of an input file into a command and redirects the outputs of that command into an output file

Uses dup and dup2 (with backups created) to swap stdin and an input file on the file table so that the input file is redirected to the command to be interpreted and executed. Then, an output file is opened and swapped on the file table for the output of that command to be written to the file.
 ====================*/

/*========void pipe_redirect_and_fork()==========
Inputs: char **command1
        char **command2
Returns: does not return anything; 

Opens an unnamed pipe and then forks the process and uses said pipe to read and write through a buffer.
 ====================*/
```

#### main.c
* The main loop of the program
```
/*========int main()==========
Input: None
Returns: 0 when receiving exit command

Asks the user for input and executes commands until the exit command is given. Prints the current working directory if certain conditions are met and also parses input for multiple commands involving the ; separator. 
 ====================*/

```
