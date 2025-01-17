/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jiajchen <jiajchen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/07 10:10:35 by jiajchen      #+#    #+#                 */
/*   Updated: 2024/01/23 19:11:20 by kkopnev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* standard headers */
# include <unistd.h>
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
# include <signal.h>
# include "struct.h"
# include "lexer.h"
# include "../libft/libft.h"

/* main */
char**  create_env(char** envp);
int     check_eq(char*   str);
int     check_quotes(char *str);
int     get_env_size(char **env);
int		check_quotes(char *str);

/* error */
int		ft_error(t_global* global, char* error_msg, int exit_c);
void	ft_unlink(t_cmd *cmds);
void	free_global(t_global *global);
void	check_sig(t_global *global);

/* signal */
void	signals_handler(t_mode mode);

/* paser and polisher */
int		expand_env(t_lexer	*lex, t_global *global);
int		polish_lex(t_lexer **lst);
int		get_cmds(t_global* global);


/* t_cmd link list utils*/
t_cmd*	ft_cmdnew(void);
void	ft_cmdaddfront(t_cmd** cmd, t_cmd* new);
void	ft_cmdaddback(t_cmd** cmd, t_cmd* new);
t_cmd*	ft_cmdlast(t_cmd* cmd);
void	ft_cmddel(t_cmd* node);
void    ft_cmdclean(t_cmd* cmd); //edited

/* executor */
int     executor(t_global *global);
int     pipe_exe(t_global* global);
void	process_cmd(t_cmd *cmd, t_global *global, int pipe_inpt);
int     check_directory(char *path);
char	*find_variable(char *var, t_global *global);
int		check_redirection(t_cmd *cmd);
int		set_redir(t_cmd* cmd, char* inf, char* outf);
char*	redir_out(t_cmd*	cmd, t_lexer* redir);
char*	redir_in(t_cmd*	cmd, t_lexer* redir);
void	here_doc(char *heredoc, char *inf);
int     process_here_doc(char* count, t_lexer* redir, t_global* global);
int     create_heredoc(t_global* global);
void 	close_fd(int fd[]);
int		ft_wait(t_cmd* cmd);
int		specify_builtins(t_cmd* cmd, char ***env);

/* builtins */
int     ft_echo(t_cmd* cmd, t_global* global);
int     ft_env(t_cmd* cmd, t_global* global);
int     ft_exit(t_cmd* cmd, t_global* global);
int     ft_export(t_cmd* cmd, t_global* global);
int     ft_unset(t_cmd* cmd, t_global* global);
int     ft_pwd(t_cmd* cmd, t_global* global);
int     ft_cd(t_cmd *cmd, t_global *global);

char	**ft_del_env(char *var, char **env);
void	ft_move_env(char **env, char **tmp, int pos);
char	**ft_change_env(char *var, char *str, t_global *global);
int		get_env_size(char **env);
int		ft_find_key(char *var, char **env);

void    print_args(char** args);
void	print_lex(t_lexer* lexer);
void	print_cmd(t_cmd* cmd);



#endif