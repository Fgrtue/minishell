/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jiajchen <jiajchen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/08 16:39:12 by jiajchen      #+#    #+#                 */
/*   Updated: 2023/12/14 19:17:59 by jiajchen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


/* find the variable in the env. Never return NULL, only can be empty string!! */
char	*find_variable(char *var, char **env)
{
	int		i;
	char	*content;
	char	*var_new;

	i = 0;
	var_new = ft_strjoin(var, "=");
	while (env[i] && ft_strncmp(env[i], var_new, ft_strlen(var_new)) != 0)
		i++;
	if (env[i])
		content = ft_strdup(env[i] + ft_strlen(var_new));
	else
		content = ft_calloc(sizeof(char), 1);
	if (!content)
		perror("malloc"); // todo: write another error() to exit(0)
	if (!env[i])
		content[0] = '\0';
	free(var_new);
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

/* return 1 if prev lexer is '<<' and not in the dquotes*/
int	is_dredir(t_lexer *lexer)
{
	t_lexer	*tmp;
	
	tmp = lexer->prev;
	if (tmp->state != GENERAL)
		return (0);
	if (tmp)
	{
		if (tmp->token == DREDIR_OUT)
			return (1);
		if (tmp->token != WHITE_SPACE)
			return (0);
		tmp = tmp->prev;
		if (tmp && tmp->token == DREDIR_OUT)
			return (1);
	}
	return (0);
}

char	*ft_expand_env(char *vars, char **env, int exit_c)
{
	char	**tabs;
	char	*contents;
	char	*tmp;
	int		i;

	tabs = ft_split(vars, '$');
	i = -1;
	contents = NULL;
	while (tabs[++i])
	{
		if (tabs[i][0] == '?')
		{
			tmp = ft_itoa(exit_c);
			contents = ft_strjoin_free(contents, tmp);
			contents = ft_strjoin_free(contents, tabs[i] + 1);
		}
		else
		{
			tmp = find_variable(tabs[i], env);
			contents = ft_strjoin_free(contents, tmp);
		}
		free(tmp);
	}
	free_arr(tabs);
	return (contents);
}

/* echo $?123$USER -- 0123jiajchen*/
void	expand_env(t_lexer **lst, char **env, int exit_c)
{
	char	*tmp;
	t_lexer	*lexer;
	
	lexer = *lst;
	while (lexer)
	{
		if (lexer->token == ENV && lexer->state != IN_QUOTE && !is_dredir(lexer))
		{
			tmp = ft_expand_env(lexer->content, env, exit_c);
			if (ft_strchr(tmp, ' ') && lexer->state == GENERAL)
				lexer = ft_lexsplit(lst, lexer, tmp);
			else
			{
				free(lexer->content);
				lexer->content = tmp;
				lexer->len = ft_strlen(tmp);
			}
		}
		// if (lexer->token == ENV)
		// 	lexer->token = WORD;
		lexer = lexer->next;
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