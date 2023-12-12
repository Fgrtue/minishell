/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jiajchen <jiajchen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/08 11:09:00 by jiajchen      #+#    #+#                 */
/*   Updated: 2023/12/12 20:07:16 by kkopnev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void lexer_setstate(t_lexer* lexer)
{
	while (lexer)
	{
		if (lexer->token == DOUBLE_QUOTE)
		{
			lexer = lexer->next;
			while (lexer->token != DOUBLE_QUOTE)
			{
				lexer->state = IN_DQUOTE;
				lexer = lexer->next;
			}
		}
		else if (lexer->token == QUOTE)
		{
			lexer = lexer->next;
			while (lexer->token != QUOTE)
			{
				lexer->state = IN_QUOTE;
				lexer = lexer->next;
			}
		}
		lexer->state = GENERAL;
		lexer = lexer->next;
	}
}

t_lexer*    lexer_tokenizer(t_lexer** lexer, char* str)
{
    while (*str)
	{
		if (*str == WHITE_SPACE || *str == QUOTE
		|| *str == DOUBLE_QUOTE || *str == PIPE_LINE)
			str = handle_sntx(str, lexer, *str);
		else if (*str == REDIR_OUT && *(str + 1) == REDIR_OUT)
			str = handle_dredir(str, lexer, DREDIR_OUT);
        else if (*str == REDIR_IN && *(str + 1) == REDIR_IN)
            str = handle_dredir(str, lexer, HERE_DOC);
		else if (*str == REDIR_OUT)
			str = handle_redir(str, lexer, REDIR_OUT);
		else if (*str == REDIR_IN)
			str = handle_redir(str, lexer, REDIR_IN);
		else if (*str == ENV)
			str = handle_word(str, lexer, ENV);
		else
			str = handle_word(str, lexer, WORD);
	}
    return (*lexer);
}


t_lexer* lexer(char* str)
{
	t_lexer*	lexer;
	
	lexer = NULL;
	if (!str || !*str)
		return(NULL);
	lexer = lexer_tokenizer(&lexer, str);
	lexer_setstate(lexer);
	print_list(lexer);
	return (lexer);
}

/*

Test the tokenizer
Test set the state

void print_list(t_lexer* lexer);

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
    // char* line = "The >> <<  $is < \" command \" \' NULL \' ^ & () ";

	char* line = "command1 \" command2 \" \' command3 \'";

    lexer(line);
	return 0;
}

*/
