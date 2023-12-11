/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jiajchen <jiajchen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/08 11:09:00 by jiajchen      #+#    #+#                 */
/*   Updated: 2023/12/11 20:03:22 by kkopnev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_lexer* lexer(char* str)
{
	t_lexer*	lexer;
	char* 		ptr;

	ptr = str;
	lexer = malloc(sizeof(t_lexer));
	if (lexer == NULL)
		perror("malloc");
	if (!str || !*str)
		return(NULL);
	while (*str)
	{
		if (*str == WHITE_SPACE || *str == QUOTE
		|| *str == DOUBLE_QUOTE || *str == PIPE_LINE)
			ft_lexaddback(ft_lexlist(*str++, 0));
		else if (*str == REDIR_OUT && *(str + 1) == REDIR_OUT
		|| *str == REDIR_IN && *(str + 1) == REDIR_IN)
			str = handle_dredir(*str, lexer);
		else if (*str == REDIR_OUT || *str == REDIR_IN)
			str = handle_redir(*str, lexer);
		else
			str = handle_word(*str, lexer);
	}
	while (*ptr)
	{
		
	}
	return (lexer);
}