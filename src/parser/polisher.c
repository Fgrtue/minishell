/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   polisher.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jiajchen <jiajchen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/11 12:35:21 by jiajchen      #+#    #+#                 */
/*   Updated: 2023/12/20 14:54:31 by jiajchen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_lexjoin_quotes(t_lexer **lst, t_lexer *lexer)
{
	t_lexer			*node;
	t_lexer			*track;
	char			*str;

	while (lexer)
	{
		str = NULL;
		if (lexer->state != GENERAL)
		{	
			track = lexer;
			while (track && track->state != GENERAL)
			{
				str = ft_strjoin_free(str, track->content);
				track = track->next;
			}
			node = ft_lexnew(str, WORD);
			ft_lexinsert(lst, lexer->prev, lexer, node);
			while (node->next && node->next->state != GENERAL)
				ft_lexdel(ft_lexretract(lst, node->next));
			lexer = node;
		}
		lexer = lexer->next;
	}
}

void	ft_lexjoin_word(t_lexer **lst, t_lexer *lexer)
{
	t_lexer			*node;
	t_lexer			*track;
	char			*str;

	while (lexer)
	{
		str = NULL;
		if (lexer->token == WORD && lexer->next && \
			 lexer->next->token == WORD)
		{	
			track = lexer;
			while (track && track->token == WORD)
			{
				str = ft_strjoin_free(str, track->content);
				track = track->next;
			}
			node = ft_lexnew(str, WORD);
			ft_lexinsert(lst, lexer->prev, lexer, node);
			while (node->next && node->next->token == WORD)
				ft_lexdel(ft_lexretract(lst, node->next));
			lexer = node;
		}
		lexer = lexer->next;
	}
}

void	polish_lex(t_lexer **lst)
{
	t_lexer	*lex;
	t_lexer	*tmp;

	ft_lexjoin_quotes(lst, *lst);
	ft_lexjoin_word(lst, *lst);
	lex = *lst;
	while (lex)
	{
		if (lex->token == WHITE_SPACE)
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
