/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_tokenizer.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkopnev <kkopnev@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/12 12:27:46 by kkopnev       #+#    #+#                 */
/*   Updated: 2024/01/16 18:21:17 by kkopnev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int word_len(char* str);
char* handle_sntx(char* str, t_lexer** lexer, int token);
char* handle_dredir(char* str, t_lexer** lexer, int token);
char* handle_redir(char* str, t_lexer** lexer, int token);
char* handle_word(char* str, t_lexer** lexer, int token);

int word_len(char* str)
{
    int i;
    
    i = 0;
    if (!str[i])
        return (i);
    if (str[i] == '$')
        i++;
    if (str[i] == '?')
        return (i + 1);
    while (str[i] && str[i] != ' ' && str[i] != '\'' && str[i] != '\"' \
            && str[i] != '>' && str[i] != '<' && str[i] != '|' && str[i] != '$')
        i++;
    return (i);
}

char* handle_sntx(char* str, t_lexer** lexer, int token)
{	
	char* content;
	
    content = NULL;
	if (*str == WHITE_SPACE)
        content = ft_strdup(" ");
	else if (*str == QUOTE)
        content = ft_strdup("\'");
	else if (*str == DOUBLE_QUOTE)
        content = ft_strdup("\"");
	else if (*str == PIPE_LINE)
        content = ft_strdup("|");
    ft_lexaddback(lexer, ft_lexnew(content, token));
	return (str + 1);
}

char* handle_dredir(char* str, t_lexer** lexer, int token)
{
	char* content;

    content = NULL;
    if (*str == REDIR_OUT && *(str + 1) == REDIR_OUT)
		content = ft_strdup(">>");
	else if (*str == REDIR_IN && *(str + 1) == REDIR_IN)
		content = ft_strdup("<<");
	ft_lexaddback(lexer, ft_lexnew(content, token));
	return (str + 2);
}

char* handle_redir(char* str, t_lexer** lexer, int token)
{
	char* content;

	content = NULL;
	if (*str == REDIR_IN)
		content = ft_strdup("<");
	else if (*str == REDIR_OUT)
		content = ft_strdup(">");
	ft_lexaddback(lexer, ft_lexnew(content, token));
	return (str + 1);
}

char* handle_word(char* str, t_lexer** lexer, int token)
{
	char*	content;
    size_t  len;

    len = word_len(str);
	// if (is_env(str))
	// 	token = ENV;
	content = ft_calloc(len + 1, sizeof(char));
	if (content == NULL)
		perror("calloc");
    ft_memcpy(content, str, len);
	ft_lexaddback(lexer, ft_lexnew(content, token));
	return (str + len);
}

/*
Test handling different cases:
1. word
2. redirection
3. dredirection
4. white space, quote, dquote 
5. env
 -- one env variable
 -- two or more

void print_list(t_lexer* lexer)
{
    printf("************************************\n");
    while(lexer)
    {
        printf("NAME: %p\n", lexer);
        printf("************************************\n");
        printf("content: %s\n", lexer->content);
        printf("len: %i\n", lexer->len);
        printf("token: %i\n", lexer->token);
        printf("state: %i\n", lexer->state);
        printf("prev: %p\n", lexer->prev);
        printf("next: %p\n", lexer->next);
        printf("************************************\n");
        lexer = lexer->next;
    }
}

int main(void)
{
    t_lexer* lexer = NULL;

    handle_word("WORD ", &lexer, WORD);
    print_list(lexer);
}
*/