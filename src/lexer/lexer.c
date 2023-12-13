/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jiajchen <jiajchen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/08 11:09:00 by jiajchen      #+#    #+#                 */
/*   Updated: 2023/12/13 16:44:20 by jiajchen      ########   odam.nl         */
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
			while (lexer && lexer->token != DOUBLE_QUOTE)
			{
				lexer->state = IN_DQUOTE;
				lexer = lexer->next;
			}
		}
		else if (lexer->token == QUOTE)
		{
			lexer = lexer->next;
			while (lexer && lexer->token != QUOTE)
			{
				lexer->state = IN_QUOTE;
				lexer = lexer->next;
			}
		}
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


t_lexer* ft_lexer(char* str)
{
	t_lexer*	lexer;
	
	lexer = NULL;
	if (!str || !*str)
		return(NULL);
	lexer = lexer_tokenizer(&lexer, str);
	lexer_setstate(lexer);
	// print_list(lexer);
	return (lexer);
}



// Test the tokenizer
// Test set the state

void print_lex(t_lexer* lexer);

void print_lex(t_lexer* lexer)
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
void print_args(char** args)
{
    int i = 0;
    
    printf("The content:\n");
    while(args[i])
    {
        printf("    %d. %s\n", i, args[i]);
        i++;
    }
}

void print_cmd(t_cmd* cmd)
{
    printf("************************************\n");
    while(cmd)
    {
        printf("NAME: %p\n", cmd);
        printf("************************************\n");
        print_args(cmd->args);
        printf("The num of redir: %d\n", cmd->num_redir);
        printf("Redir: %p\n", cmd->redir);
		print_lex(cmd->redir);
        printf("prev: %p\n", cmd->prev);
        printf("next: %p\n", cmd->next);
        printf("************************************\n");
        cmd = cmd->next;
    }
}

int main(int argc, char **argv, char **env)
{
    char* line = "> file  command \"$is$is|\"  $USER$?123$LS > file2 | < file3 echo \" fjkd $LS$?? \"";
	t_lexer	*lst;
	t_cmd	*cmds;
	// char* line = "command1 \" command2 \" \' command3 \'";

    lst = ft_lexer(line);
	// print_list(lst);
	// printf("#######################################\n");
	// printf("EXPANSION\n");
	// printf("#######################################\n");
	expand_env(&lst, env, 0);
	// print_list(lst);
	polish_lex(&lst);
	// print_lex(lst);
	cmds = get_cmds(&lst, lst);
	// print_cmd(cmds);
	return (0);
}


