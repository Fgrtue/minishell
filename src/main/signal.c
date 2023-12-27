/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkopnev <kkopnev@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/27 17:18:21 by kkopnev       #+#    #+#                 */
/*   Updated: 2023/12/27 18:29:06 by kkopnev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void handleCtrlC(int signum)
{
    if (sig == 1)
       write(1,"\nminishell: ", 12);
	else if (sig == 2)
		write(1, "\nheredoc: ", 10);
	else
        exit(signum);
}

// Function to handle Ctrl+D (EOF) signal
void handleCtrlD(void) 
{
    if (sig == 1 || sig == 2)
        exit(0);
    else
		return ;
}


