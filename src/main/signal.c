/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkopnev <kkopnev@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/27 17:18:21 by kkopnev       #+#    #+#                 */
/*   Updated: 2023/12/27 20:40:12 by kkopnev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void handl_ctrlc(int signum)
{
    if (sign == 1)
       write(1,"\nminishell: ", 12);
	else if (sign == 2)
		write(1, "\nheredoc: ", 10);
	else
        exit(signum);
}

// Function to handle Ctrl+D (EOF) signal
void handl_ctrld(int signum) 
{
    if (sign == 1)
        exit(0);
    else if (sign == 2)
        exit(3);
    else
		return ;
}