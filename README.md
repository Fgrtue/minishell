# minishell

/**
 * to read: <termio.h>
 * 			metacharacters(what are they how to interpret them)
 * to read: how pinkshell deal with the quotes DONE
 * discuss: what tokens should be used (what should we expand??) DONE
 * discuss: what should be done for the case of " "h h h" DONE
 * check: what protection should we use for diffrent functions -- PROTECTION FILE
 * discuss: adding a global struct which stores all the other structs DONE
 * check: the manual for $ and evironmental variables 
 * TO DO: the big struct
 * TO DO: create the copy of the env
 * TO DO: handle the case when 
 * TO DO: if you have more than 1 redirections, write only in the last one
 * TO DO: handle the signals
 * TO CHECK: When you provide an env var that doesn't exist, what happens?
 * When it is empty string? 
 * TO DO: write our own error function and change the error in the get_cmd
 * TO CHECK: for export how should we parse the command? Sometimes we have that var=xxx
 * is the whole word, sometimes we have that assignment is done throgh "" and ''
 * TO DO: HANDLE THE CASE OF ECHO 'hh'$USER "hh""$USER" hh$USER 'hh'"jj"
 * TO CHECK: DO WE HAVE TO SEPARATE ARGUMENTS IN THE CASE ab" ""$USER". but not in the case ab"$USER" ? (ATM: NO)
 * TO DO: SET I/O IN THE CREATIONS OF THE COMMAND NODE
 * TO DO: delete all the printf's
 * TO CHECK: when we create new nodes and something goes wrong -- do we handle it?
 * TO DO: protect the open() function
 * 
 * COMMENT:
 * ./program absolute |cat| didnt split tokens from strings 
 * correctly cat | cat | cat | cat didnt link the pipes correctly 
 * for redirects you need to check if you can access all of the redirects 
 * before you continue with the rest of your execution 
 * << stop cat | cat | cat << stop2 << stop < infile cat cat infile | cat > outfile | ls 
 * --- if i chmod -w outfile it just silently ignores that 
 * i dont have access to outfile megashell> unset PATH megashell> cat 
 * You guys will need to rewrite the way you interpet redirects. 
 * Tokens should be allowed next to strings ie. cat|cat & <infile.
 * Absolute path check should be improved 
 * Access checks for program and files should also be improved 
 * Goodluck with improving your minishell.
 * 
 * 



### LEXER



// CHECK: WHEATHER WE NEED BACKSLASH IN OUR TOKENS OF D_QUOTE OR QUOTE
// CHECK: DO WE NEED \n AS TOKEN and \ ?

// ALGO:

// INPUT: String;
// OUTPUT: LL with lexical parts

// Go character by character through the string
// if you find:
// 		- WHITE SPACE
//		- QUOTE
//		- DQUOTE
//		- PIPE
//	CREATE A NODE WITH A TOKEN OF THE CORRESPONDING TYPE
// if you find
//		- ENV
//	TAKE EVERYTHING AFTER UNTIL THE WHITE SPACE
//	AND CREATE A NODE FOR THIS THING WITH TYPE ENV
//	
//	If you find
//	- REDIR_IN
//	CHECK WHEATHER THE NEXT CHAR IS ALSO REDIR_IN
//	If it is, then take the last two characters and
//	create a node for them with token of type HERE_DOC
//	If it is not, then create a node for it with type
//	REDIR_IN;
//
//	If you find
//	- REDIR_OUT
//	CHECK WHEATHER THE NEXT CHAR IS ALSO REDIR_OUT
//	If it is, then take the last two characters and
//	create a node for them with token of type DREDIR_OUT
//	If it is not, then create a node for it with type
//	REDIR_OUT;
//
//	If it is nothing of that, then
//	THIS IS A WORD
//	Thus, create a node for everything starting from the first
//	letter to the first space that you find and assign token WORD
//	to it.

//	THEN ADD THE NODE TO THE LL;

//	Now the part for setting the state
//	WE WILL USE THE STATE TO TRACK THE STATE 
//	ITERATEVELY GO THROUGH LINKED LIST 
//	AND ASSIGN THE PROPER STATE TO IT DEPENDING WHEATHER IT IS IN THE QUOTE OR NOT


// TO DO:
/**
 	1. Functions for linked list:
		
		1) Create a node for linked list;
		2) Add back to LL;
		3) Clear LL;
	
	2. A FUNCTION FOR CREATION OF OUR LL WITH THE CONTENT, TOKENS AND LENGTH; 
	3. A FUNCTION FOR SETTING THE STATE;
*/




### EXPANDER

/**
 * After doing Lexer we have a linked list as an output.
Thus, we have to expand all the enviromental variables that we have
How do we do it?

ALGORITHM:
INPUT: LINKED LIST without expanded environmental variables, ENVIRONMENT
OUTPUT: LINKED LIST with expanded enviromental variables

We iteratively go through the linked list, checking for the nodes with
token ENV and witout state QUOTE.

If we find one, then
    Use the EXPAND that converts the content of the note into the
    content that epands the env variable.
	
void EXPAND (node, env)

    first check what is the first letter of node -> content after the $
	
    if it is ?, then we expand it as the string of the last exit code,
	using itoa(exit_status),add the rest of the string after ? (but better read
	the manual)
	
    else
	
	env is a 2D array
	
    go iteratively through env (note that you shouldn't move the pointer, in env), 
	and find the line which starts with the name of the variable plus = (UPD: no,
	it seems that the first variant is still better cause we have to be able to
	update environment UPD: use getenv instead of :: use strjoin to create such 
	line and ft_strnstr(const char *big, const char *little, size_t 
	len), protect strjoin and ft_strnstr). Split the string with spaces, so that
	a command argument like ls -la becomes a proper command.
	

	once you found this line, copy the content of it to some buffer and then
	change the content of the node for this buffer (use *ft_strdup(const char *s)
	and protect it). 
	Also free the previous content of the node
	
*** DO NOT EXPAND ENV VAR (the env after '<<')

*/

### POLISHER

/**
 * 

INPUT: Expanded t_lexer 
OUTPUT: Polished t_lexer (with all the useful parts)
ALGORITHM:

	We go through the t_lexer until the end. 

	If we see token DOUBLE_Q/QOUTE/WHITE_SPACE in GENERAL state, then it
	should delete it from the linked list.

	If it sees something in the state IN_[D]QUOTE, then it changes the linked list:

		updates the content, length and the stat of the first one, str_joining
		with the second one if it is IN_QUOTE, and deletes the following node
		(Clearning everything)
*/


### PARSER

/**
 * There will be two functions:
 * 
 * 1. Fills the redirections
 * 2. Fills the arguments
 * 
 * The first one retreives all the redirections until the first encountered pipe
 * Moving the redirections (<, >, <<, >>) to the t_lexer linked list in the 
 * t_cmd struct
 * 
 * The second one retreives all the commands into 2D array (args) skipping the spaces
 * inbetween the nodes, and in case when it finds a quoted part it creates one
 * string out of everything that is inside the quotes and puts it into argc. 
 * 
 * INPUT: t_lexer (which is the LL)
 * OUTPUT: t_cmd (which is also a LL)
 * 
 * ALGORITHM:
 * 
 * We need a pointer that will be used for lexering the beggning of new iteration.
 * It will be updated when we finish with the part unting the closest pipe or NULL.
 * First we allocate the memory for the current t_cmd. Then we use two functions 
 * 
 *  ft_redir -- uses and changes the t_lexer LL and adds redirection nodes to t_cmd
 * 
 * 	ft_fill_args -- uses t_lexer to fill the t_cmd. It should return the pointer to
 * 	the closest pipe (or NULL). 
 * 
 *	We update our pointer with the new value returned by ft_fill_args, and add the
	created node to the Linked List of commands.
 * 
 * 	ft_redir:
 * 
 * 	takes to t_lexer and t_cmd
 *	Goes through the t_lexer until the first pipe

	If it sees a node with REDIR_OUT/REDIR_IN/HERE_DOC/DREDIR_OUT in GENERAL STATE
	then it adds a value to the number of redir and adds this node to the redir in 
	t_cmd as a redirection. 
	After that it takes the second element and adds this to the redir in t_cmd.

	Now we have tha updated Lexer. Function returns the count var.

	ft_fill_args:
	
		takes t_cmd and allocates the amount of memory for the lenght of the LL until
		the pipe (or NULL), and then fills 2D array one by one 
		terminating it with NULL.
*/

### EXECUTOR

// 1. if there is redir inf = redir in; outf = redir out;
// 1.1 if '<<' inf = the new file user types
// 1.2 if '>>'
// 2. inf = stdin(if it is the first cmd)or fd[0](not first cmd)
// 3. outf = fd[1](if not the last cmd) or stdout(if it is the last cmd)

// 1. if there is no argument, 

// if there is one cmd, parent process; else, chile process
// if cmd is not found, exit(127)
// TO CHECK: how to do with 'bin/cat file1' in path match


/*
pipe_exe

 	1.	Check for redirections in a separate function that returns 
		the file descriptions for the input and output. If no input/output
		is specified, then you put the pippw in input/output variables 
	2.	Then we get into the while loop that will be running until we reach the
		last command. We also write down the process id into the struct that we 
		work with. 
	3.	First open the pipe, and check the fd returned by redir function. If any of
		then are filled, use them instead of a pipe. Else use the pipe.
	4.	Proceed to function process_cmd(), plugging in arguments, env, inf, outf
	5.	Inside it we check: a) That args is not empty; b) For the builtins (whether the command that we have in args[0]
		is a builtin) -- if the command is a path to a builtin. If it is, then we 
		poceed to the function and execute it. If
		its not, then we find a path to the command and then run it using dup, execve;
	6. In the end we wait for the processes with id written down in the struct,
		in other words we go through the linked list again and wait for every
		process id written down in there.

how the redirection func should work?

	1. If it is normal > or <, then take the last redir 
		check the unlink
		check the order or redir

how the builtins should work?

	echo 
	
	cd -- cd with only a relative or absolute path

		Change the current working directory to directory. 
		
		If directory is not supplied, the value of the HOME shell 
		
		variable is used. If the shell variable CDPATH exists, it 
		
		is used as a search path: each directory name in CDPATH is 
		
		searched for directory, with alternative directory names in 
		
		CDPATH separated by a colon (‘:’). If directory begins with 
		
		a slash, CDPATH is not used. 

	void ft_cd(char* directory);
	{
		home = get_home();
		if (directory starts with home)
			chdir(home)
		else 
			append home to dir
			
	}

	pwd

	export

	unset

	env

	exit

how the wait function should wait?
*/	

### PROTECTION OF FUNCTION


In C programming, certain functions should be used with caution or protected due to their potential to cause errors, security vulnerabilities, or system instability if misused. Here's a breakdown of the functions you listed and considerations for their protection:

Functions that should be used with caution or protected:

malloc/free: Memory allocation and deallocation functions. Protect against memory leaks and ensure proper memory management.

printf: Format string vulnerabilities can occur if not used carefully, leading to potential security risks like buffer overflows. Using printf with user-input or unchecked data can be unsafe.

access, open, read, close: File I/O operations. Protect against file-related errors, handle permissions properly, and ensure files are closed after use to prevent resource leaks.

execve: Executes a program. Properly validate input and be cautious with its use, especially when dealing with user input or external data.

unlink: Deletes a file. Ensure appropriate permissions and validate inputs before using this function.

signal, sigaction, sigemptyset, sigaddset, kill: Signal handling functions. Misuse can lead to unexpected behavior or instability. Proper signal handling is essential in robust applications.

exit: Terminates the process. Care should be taken to ensure proper cleanup before exiting the program.

getcwd, chdir, stat, lstat, fstat: File and directory manipulation functions. Validate inputs and handle errors properly to avoid security vulnerabilities or unexpected behavior.

dup, dup2, pipe: File descriptor manipulation. Use with care to avoid mishandling file descriptors or creating vulnerabilities.

opendir, readdir, closedir: Directory manipulation functions. Validate inputs and handle errors appropriately.

strerror, perror: Error handling functions. Proper use helps in debugging and reporting errors accurately.

ioctl: System call for device-specific I/O operations. Requires proper understanding and use specific to the system/devices being accessed.

getenv: Retrieves environment variables. Validate inputs and handle cases where the variable might not exist.

