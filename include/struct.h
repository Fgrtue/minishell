/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   struct.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jiajchen <jiajchen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/07 12:41:33 by jiajchen      #+#    #+#                 */
/*   Updated: 2023/12/11 19:31:04 by kkopnev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef	STRUCT_H
# define STRUCT_H

//ARE THESE ALL THE TOKENS THAT WE NEED?
enum e_token
{
	WORD = -1,
	WHITE_SPACE = ' ',
//	NEW_LINE = '\n', //	?
	QUOTE = '\'',
	DOUBLE_QUOTE = '\"',
//	ESCAPE = '\\', // ?
	ENV = '$',
	PIPE_LINE = '|',
	REDIR_IN = '<',
	REDIR_OUT = '>',
	HERE_DOC, // <<
	DREDIR_OUT, // >>
};

enum e_state
{
	GENERAL,
	IN_QUOTE,
	IN_DQUOTE,
};

typedef struct s_lexer
{
	char			*content;
	int				len;
	enum e_token	token; // E_TOKEN ABOVE
	enum e_state	state; // DQUOTE, QUOTE, NOT_QUOTED 
	struct s_lexer	*prev;
	struct s_lexer	*next;
}	t_lexer;

typedef struct s_cmd
{
	char			**args;
	// int				(*builtin)(t_tools *, struct s_cmd *);
	int				num_redir;
	t_lexer			*redirections;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}	t_cmd;



#endif