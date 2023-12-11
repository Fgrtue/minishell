/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   polisher.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jiajchen <jiajchen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/11 12:35:21 by jiajchen      #+#    #+#                 */
/*   Updated: 2023/12/11 12:44:13 by jiajchen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/**
 * 

INPUT: Expanded t_lexer 
OUTPUT: Polished t_lexer (with all the useful parts)
ALGORITHM:

	We go through the t_lexer until the end. 

	If we see token DOUBLE_Q/QOUTE/WHITE_SPACE in GENERAL state, then it
	should delete it from the linked list.

	If it sees something in the state IN_[D]QUOTE, then it changes the linked list:

		updates the content, length and the stat of the first one, str_joining
		with the second one if it is IN_QUOTE, and deletes the following node
		(Clearning everything)

