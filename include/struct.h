/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   struct.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jiajchen <jiajchen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/07 12:41:33 by jiajchen      #+#    #+#                 */
/*   Updated: 2024/01/16 12:22:07 by jiajchen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef	STRUCT_H
# define STRUCT_H

extern volatile sig_atomic_t	g_sig;

enum e_token
{
	WORD = -1,
	WHITE_SPACE = ' ',
	QUOTE = '\'',
	DOUBLE_QUOTE = '\"',
	ENV = '$',
	PIPE_LINE = '|',
	REDIR_IN = '<',
	REDIR_OUT = '>',
	HERE_DOC,
	DREDIR_OUT,
};

enum e_state
{
	GENERAL,
	IN_QUOTE,
	IN_DQUOTE,
};

typedef enum e_mode
{
	INTERACTIVE,
	NON_INTERACTIVE,
	HEREDOC,
}	t_mode;

typedef struct s_lexer
{
	char			*content;
	int				len;
	enum e_token	token;
	enum e_state	state;
	struct s_lexer	*prev;
	struct s_lexer	*next;
}	t_lexer;

typedef struct s_cmd
{
	char			**args;
	int				(*builtin)(struct s_cmd *, char ***);
	int				num_redir;
	int				pid;
	int				fd_io[2];
	char			*heredoc;
	int				dr_bool;
	t_lexer			*redir;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}	t_cmd;



#endif