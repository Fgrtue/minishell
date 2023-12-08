/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jiajchen <jiajchen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/08 16:39:12 by jiajchen      #+#    #+#                 */
/*   Updated: 2023/12/08 16:39:15 by jiajchen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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
	and find the line which starts with the name of the variable plus = (use strjoin 
	to create such line and ft_strnstr(const char *big, const char *little, size_t 
	len), protect strjoin and ft_strnstr)

	once you found this line, copy the content of it to some buffer and then
	change the content of the node for this buffer (use *ft_strdup(const char *s)
	and protect it). 
	Also free the previous content of the node
	


*/