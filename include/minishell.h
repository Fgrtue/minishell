/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jiajchen <jiajchen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/07 10:10:35 by jiajchen      #+#    #+#                 */
/*   Updated: 2023/12/07 16:16:34 by jiajchen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H


/* standard headers */
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>	// getcwd chdir / isatty ttyname ttyslot 
# include <fcntl.h>
# include <sys/wait.h>
# include <string.h>	// strerror
# include <errno.h>
# include <signal.h>	// signal kill sigaction sigemptyset sigaddset 
# include <sys/stat.h>	// stat lstat fstat
# include <dirent.h>	// opendir readdir closedir
# include <termio.h>	// tcsetattr tcgetattr
# include <readline/readline.h>
# include <readline/history.h>

# include "struct.h"

#endif