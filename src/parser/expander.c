/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jiajchen <jiajchen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/08 16:39:12 by jiajchen      #+#    #+#                 */
/*   Updated: 2023/12/20 14:54:24 by jiajchen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


/* find the variable in the env. Never return NULL, 
only can be empty string!! */
char	*find_variable(char *var, char **env, int exit_c)
{
	int		i;
	char	*content;

	if (*var == '?')
		return (ft_itoa(exit_c));
	i = 0;
	var = ft_strjoin(var, "="); //not free original var
	while (env[i] && ft_strncmp(env[i], var, ft_strlen(var)) != 0)
		i++;
	if (env[i])
		content = ft_strdup(env[i] + ft_strlen(var));
	else
		content = ft_calloc(sizeof(char), 1);
	if (!content)
		perror("malloc"); // todo: write another error() to exit(0)
	if (!env[i])
		content[0] = '\0';
	free(var);
	return (content);
}

t_lexer	*ft_lexsplit(t_lexer **lst, t_lexer *lexer, char *str)
{
	char	**tabs;
	t_lexer	*node;
	int		i;
	
	tabs = ft_split(str, ' ');
	i = -1;
	while (*str)
	{
		if (*str == ' ')
		{
			node = ft_lexnew(ft_strdup(" "), WHITE_SPACE);
			while (*str == ' ')
				str++;
		}
		else
		{
			node = ft_lexnew(tabs[++i], WORD);
			str += ft_strlen(tabs[i]);
		}
		ft_lexinsert(lst, lexer->prev, lexer, node);		
	}
	ft_lexdel(ft_lexretract(lst, lexer));
	free(tabs); //only free the crust? not strings
	return (node->next);
}

// t_lexer	*ft_lexsplit(t_lexer **lst, t_lexer *lexer, char *str)
// {
// 	char	**tabs;
// 	t_lexer	*node;
// 	int		i;

// 	tabs = ft_split(str, ' ');
// 	i = -1;
// 	while (tabs[++i])
// 	{
// 		node = ft_lexnew(tabs[i], WORD);
// 		ft_lexinsert(lst, lexer->prev, lexer, node);
// 		if (!tabs[i + 1])
// 			ft_lexinsert(lst, lexer->prev, lexer, \
// 					ft_lexnew(ft_strdup(" "), WHITE_SPACE));
// 	}
// 	ft_lexdel(ft_lexretract(lst, lexer));
// 	free(tabs); //only free the crust? not strings
// 	free(str);
// 	return (node);
// }

void	expand_env(t_lexer **lst, char **env, int exit_c)
{
	char	*tmp;
	t_lexer	*lex;
	
	lex = *lst;
	while (lex)
	{
		if (lex->token == ENV)
		{
			tmp = find_variable(lex->content + 1, env, exit_c);
			if (arr_len(tmp, ' ') != 1 && lex->prev && (lex->prev->token == '<' \
				|| lex->prev->token == '>' || lex->prev->token == DREDIR_OUT))
				exit(1); // error("ambiguous redirect");
			if (ft_strchr(tmp, ' ') && lex->state == GENERAL)
			{
				lex = ft_lexsplit(lst, lex, tmp);
				free(tmp);
				continue;
			}
			ft_lexinsert(lst, lex->prev, lex, ft_lexnew(tmp, WORD));
			lex = lex->prev;
			ft_lexdel(ft_lexretract(lst, lex->next));
		}
		lex = lex->next;
	}
}


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