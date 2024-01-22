/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_list.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkopnev <kkopnev@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/12 12:50:39 by kkopnev       #+#    #+#                 */
/*   Updated: 2024/01/22 13:56:29 by kkopnev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_lexer*	ft_lexnew(char *content, int token)
{
	t_lexer	*lexer;

	lexer = malloc(sizeof(t_lexer));
	if (lexer == NULL)
		return (NULL);
	lexer->content = content;
    lexer->len = ft_strlen(content);
	lexer->token = token;
    lexer->state = GENERAL;
    lexer->prev = NULL;
    lexer->next = NULL;
	return (lexer);
}

void	ft_lexaddfront(t_lexer** lexer, t_lexer* new)
{
    if (new == NULL)
    {
        return ;
    }
	new->next = *lexer;
    if (*lexer != NULL)
    {
        (*lexer)->prev = new;
    }
	*lexer = new;
}

void	ft_lexaddback(t_lexer **lexer, t_lexer *new)
{
    t_lexer* last;

    last = NULL;
	if ((*lexer) == NULL)
		ft_lexaddfront(lexer, new);
    else
    {
        last = ft_lexlast(*lexer);
		last->next = new;
        new->prev = last; 
        new->next = NULL;
    }
}

t_lexer*	ft_lexlast(t_lexer* lexer)
{
	if (lexer == NULL)
		return (NULL);
    while (lexer->next != NULL)
        lexer = lexer->next;
    return (lexer);
}

void	ft_lexdel(t_lexer* node)
{
    free(node->content);   
	free(node);
}

/* clearn from beginning */
void    ft_lexclean(t_lexer* lexer)
{
    t_lexer *temp;
    
    while (lexer && lexer->prev)
        lexer = lexer->prev;
    while(lexer)
    {   
        temp = lexer;
        lexer = lexer->next;
        ft_lexdel(temp);
    }
}

void    ft_lexinsert(t_lexer** lexer, t_lexer* prev, t_lexer* next, t_lexer* node)
{
    if (!node)
        return ;
    if (!prev && !next)
        return ;
    else if (!prev)
        ft_lexaddfront(lexer, node);
    else if (!next)
        ft_lexaddback(lexer, node);
    else
    {
        prev->next = node;
        node->prev = prev;
        node->next = next;
        next->prev = node;
    }
}

t_lexer* ft_lexretract(t_lexer** lexer, t_lexer* node)
{
    if (!node)
        return (NULL);
    if (node->prev != NULL && node->next != NULL)
    {
       (node->prev)->next = node->next;
       (node->next)->prev = node->prev;
    }
    else if (node->next == NULL && node->prev != NULL)
        (node->prev)->next = NULL;
    else if (node->prev == NULL && node->next != NULL)
    {
        (node->next)->prev = NULL;
        *lexer = node->next;
    }
    else
        *lexer = NULL;
    node->prev = NULL;
    node->next = NULL;
    return(node);
}

/* 
    Test:
        1. Creation of new lexer;
        2. Adding an element to the back
        3. To the front
        4. In between
        5. Delete one
        6. Clear all

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

void retraction(t_lexer** lexer, t_lexer* node1, t_lexer* node5, t_lexer* node9)
{
    ft_lexretract(lexer, node1);
    printf("##############################\n");
    printf("RETRACTING 1\n");
    printf("##############################\n");
    print_list(*lexer);
    ft_lexretract(lexer, node5);
    printf("##############################\n");
    printf("RETRACTING 5\n");
    printf("##############################\n");
    print_list(*lexer);
    ft_lexretract(lexer, node9);
    printf("##############################\n");
    printf("RETRACTING 9\n");
    printf("##############################\n");
    print_list(*lexer);
    printf("THE LEXER IS %p\n", *lexer);
}

int main(void)
{
    t_lexer* lexer = NULL;
    char*   str1 = ft_strdup("WORD");
    char*   str2 = ft_strdup("ENV");
    char*   str3 = ft_strdup("QUOTE");
    char*   str4 = ft_strdup("DQUOTE");
    char*   str5 = ft_strdup("REDIR");
    char*   str6 = ft_strdup("REDIR");
    char*   str7 = ft_strdup("HERE_DOC");
    char*   str8 = ft_strdup("DREDIR_OUT");
    char*   str9 = ft_strdup("PIPE");
    t_lexer* node1 = ft_lexnew(str1, WORD);
    t_lexer* node2 = ft_lexnew(str2, ENV);
    t_lexer* node3 = ft_lexnew(str3, QUOTE);
    t_lexer* node4 = ft_lexnew(str4, DOUBLE_QUOTE);
    t_lexer* node5 = ft_lexnew(str5, REDIR_IN);
    t_lexer* node6 = ft_lexnew(str6, REDIR_OUT);
    t_lexer* node7 = ft_lexnew(str7, HERE_DOC);
    t_lexer* node8 = ft_lexnew(str8, DREDIR_OUT);
    t_lexer* node9 = ft_lexnew(str9, PIPE_LINE);
    
    ft_lexaddback(&lexer, node1);
    ft_lexaddback(&lexer, node2);
    ft_lexaddback(&lexer, node3);
    ft_lexaddback(&lexer, node4);
    ft_lexaddback(&lexer, node5);
    ft_lexaddback(&lexer, node6);
    ft_lexaddback(&lexer, node7);
    ft_lexaddback(&lexer, node8);
    ft_lexaddback(&lexer, node9);
    print_list(lexer);
    retraction(&lexer, node1, node5, node9);
    print_list(node1);
    print_list(node5);
    print_list(node9);
    ft_lexinsert(&lexer, lexer->prev, lexer->next, node1);
    // print_list(lexer);
    ft_lexinsert(&lexer, (ft_lexlast(lexer))->prev, (ft_lexlast(lexer))->next, node9);
    // print_list(lexer);
    ft_lexinsert(&lexer, node4, node6, node5);
    print_list(lexer);
    printf("THE LEXER IS %p\n", lexer);

    ft_lexclean(&lexer);
    printf("CLEANING\n");
    
    return (0);
}
*/