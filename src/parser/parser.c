/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jiajchen <jiajchen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/08 14:37:24 by jiajchen      #+#    #+#                 */
/*   Updated: 2023/12/08 17:12:45 by jiajchen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/**
 * There will be two functions:
 * 
 * 1. Fills the redirections
 * 2. Fills the arguments
 * 
 * The first one retreives all the redirections until the first encountered pipe
 * Moving the redirections (<, >, <<, >>) to the t_lexer linked list in the 
 * t_cmd struct
 * 
 * The second one retreives all the commands into 2D array (args) skipping the spaces
 * inbetween the nodes, and in case when it finds a quoted part it creates one
 * string out of everything that is inside the quotes and puts it into argc. 
*/