/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jiajchen <jiajchen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/08 16:39:12 by jiajchen      #+#    #+#                 */
/*   Updated: 2023/12/15 15:45:29 by jiajchen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


/* find the variable in the env. Never return NULL, only can be empty string!! */
char	*find_variable(char *var, char **env)
{
	int		i;
	char	*content;

	i = 0;
	var = ft_strjoin_free(var, "=");
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
	while (tabs[++i])
	{
		node = ft_lexnew(tabs[i], WORD);
		ft_lexinsert(lst, lexer->prev, lexer, node);
	}
	ft_lexdel(ft_lexretract(lst, lexer));
	free(tabs); //only free the crust? not strings
	free(str);
	return (node);
}

char	*get_minivar(char *vars)
{
	int		i;
	char	*str;

	i = 0;
	while (vars[i] == '$')
		i++;
	while (vars[i] && vars[i] != '$')
		i++;
	str = ft_calloc(sizeof(char), i + 1);
	if (!str)
		perror("malloc"); // todo: write another error() to exit(0)
	ft_strlcpy(str, vars , i + 1);
	return (str);
}

char	*ft_expand_env(char *vars, char **env, int exit_c)
{
	char	*str;
	char	*tmp;
	
	str = NULL;
	if (*vars != '$')
	{
		str = ft_strjoin_free_d(str, get_minivar(vars));
		vars += ft_strlen(str);
	}
	while (vars)
	{
		if (++vars == '?')
		{
			str = ft_strjoin_free_d(str, ft_itoa(exit_c));
			vars++;
		}
		if (vars)
		{
			tmp = get_minivar(vars); //free in find_variable
			vars += ft_strlen(tmp);
			str = ft_strjoin_free_d(str, find_variable(tmp, env));
		}
	}
	return (str);
}

/* echo $?123$USER -- 0123jiajchen*/
void	expand_env(t_lexer **lst, char **env, int exit_c)
{
	char	*tmp;
	t_lexer	*lex;
	
	lex = *lst;
	while (lex)
	{
		if (lex->token == ENV)
		{
			tmp = ft_expand_env(lex->content, env, exit_c);
			if (ft_strchr(tmp, ' ') && lex->prev && lex->prev->token == '>')
				exit(1); // error("ambiguous redirect");
			if (ft_strchr(tmp, ' ') && lex->state == GENERAL)
				lex = ft_lexsplit(lst, lex, tmp);
			else
			{
				free(lex->content);
				lex->content = tmp;
				lex->len = ft_strlen(tmp);
			}
		}
		lex = lex->next;
	}
}

		// if (lexer->token == ENV)
		// 	lexer->token = WORD;



// char	*ft_expand_env(char *vars, char **env, int exit_c)
// {
// 	char	**tabs;
// 	char	*str;
// 	int		i;

// 	tabs = ft_split(vars, '$');
// 	i = -1;
// 	str = NULL;
// 	while (tabs[++i])
// 	{
// 		if (tabs[i][0] == '?')
// 		{
// 			str = ft_strjoin_free_d(str, ft_itoa(exit_c));
// 			str = ft_strjoin_free(str, tabs[i] + 1);
// 		}
// 		else
// 			str = ft_strjoin_free_d(str, find_variable(tabs[i], env));
// 	}
// 	free_arr(tabs);
// 	return (str);
// }

// /* return 1 if prev lexer is '<<' and not in the dquotes*/
// int	is_dredir(t_lexer *lexer)
// {
// 	t_lexer	*tmp;
	
// 	tmp = lexer->prev;
// 	if (!tmp)
// 		return (0);
// 	if (tmp->state != GENERAL)
// 		return (0);
// 	if (tmp)
// 	{
// 		if (tmp->token == DREDIR_OUT)
// 			return (1);
// 		if (tmp->token != WHITE_SPACE)
// 			return (0);
// 		tmp = tmp->prev;
// 		if (tmp && tmp->token == DREDIR_OUT)
// 			return (1);
// 	}
// 	return (0);
// }


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