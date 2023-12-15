/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   polisher.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jiajchen <jiajchen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/11 12:35:21 by jiajchen      #+#    #+#                 */
/*   Updated: 2023/12/15 15:42:41 by jiajchen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_lexer	*ft_lexjoin(t_lexer **lst, t_lexer *lexer)
{
	t_lexer	*node;
	char	*str;

	str = NULL;
	while (lexer->state != GENERAL)
	{
		str = ft_strjoin_free(str, lexer->content);
		lexer = lexer->next;
		ft_lexdel(ft_lexretract(lst, lexer->prev));
	}
	node = ft_lexnew(str, WORD);
	ft_lexinsert(lst, lexer->prev, lexer, node);
	return (node);
}


void	join_quotes(t_lexer **lst)
{
	t_lexer	*lex;
	t_lexer	*tmp;

	lex = *lst;
	while (lex)
	{
		if (lex->state != GENERAL)
			lex = ft_lexjoin(lst, lex);
		if (lex->token == ENV && lex->len == 0)
		{
			tmp = lex;
			lex = lex->next;
			ft_lexdel(ft_lexretract(lst, tmp));
		}
		else
			lex = lex->next;
	}
}

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
