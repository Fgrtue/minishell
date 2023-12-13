/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkopnev <kkopnev@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/12 12:48:29 by kkopnev       #+#    #+#                 */
/*   Updated: 2023/12/12 19:14:55 by kkopnev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#ifndef LEXER_H
# define LEXER_H

#include "../include/minishell.h"

int word_len(char* str);
t_lexer*    lexer_tokenizer(t_lexer** lexer, char* str);
char* handle_sntx(char* str, t_lexer** lexer, int token);
char* handle_dredir(char* str, t_lexer** lexer, int token);
char* handle_redir(char* str, t_lexer** lexer, int token);
char* handle_word(char* str, t_lexer** lexer, int token);
t_lexer*	ft_lexnew(char *content, int token);
void	ft_lexaddfront(t_lexer** lexer, t_lexer* new);
void	ft_lexaddback(t_lexer **lexer, t_lexer *new);
t_lexer*	ft_lexlast(t_lexer* lexer);
void	ft_lexdel(t_lexer* node);
void    ft_lexclean(t_lexer** lexer);
void    ft_lexinsert(t_lexer** lexer, t_lexer* prev, t_lexer* next, t_lexer* node);


#endif