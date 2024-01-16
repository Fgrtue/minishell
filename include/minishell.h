/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jiajchen <jiajchen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/07 10:10:35 by jiajchen      #+#    #+#                 */
/*   Updated: 2024/01/16 12:25:32 by jiajchen      ########   odam.nl         */
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
# include "struct.h"
# include "lexer.h"
# include "../libft/libft.h"



/* main */
char**  create_env(char** envp);
int     check_eq(char*   str);
int     check_quotes(char *str);
int     get_env_size(char **env);
int		check_quotes(char *str);
void	error_msg(char *cmd, char *msg);
void	free_cmd_exit(char *msg, t_cmd *cmd, char **env, int ec);

void	signals_handler(t_mode mode);
void	interrupt_interactive(int sig);
void	interrupt_execute(int sig);
void	interrupt_heredoc(int sig);

/* paser and polisher */
void	expand_env(t_lexer **lst, char **env, int exit_c);
void	polish_lex(t_lexer **lst);
t_cmd	*get_cmds(t_lexer **lst, t_lexer *lexer);

void	print_lex(t_lexer* lexer);
void	print_cmd(t_cmd* cmd);

/* t_cmd link list utils*/
t_cmd*	ft_cmdnew(void);
void	ft_cmdaddfront(t_cmd** cmd, t_cmd* new);
void	ft_cmdaddback(t_cmd** cmd, t_cmd* new);
t_cmd*	ft_cmdlast(t_cmd* cmd);
void	ft_cmddel(t_cmd* node);
void    ft_cmdclean(t_cmd* cmd); //edited

/* executor */
int		executor(t_cmd *cmd, char **env);
int		pipe_exe(t_cmd* cmd, char** env);
void    process_cmd(t_cmd *cmd, char **env);
char	*find_variable(char *var, char **env, int exit_c);
int		check_redirection(t_cmd *cmd);
int		set_redir(t_cmd* cmd, char* inf, char* outf);
char*	redir_out(t_cmd*	cmd, t_lexer* redir);
char*	redir_in(t_cmd*	cmd, t_lexer* redir);
char	*here_doc(t_cmd *cmd, char *inf);
void 	close_fd(int fd[]);
int		ft_wait(t_cmd* cmd);
int		specify_builtins(t_cmd* cmd, char ***env);

/* builtins */
int     ft_echo(t_cmd* cmd, char ***env);
int     ft_env(t_cmd* cmd, char ***env);
int     ft_exit(t_cmd* cmd, char ***env);
int     ft_export(t_cmd* cmd, char*** env);
int		ft_unset(t_cmd *cmd, char ***env);
int		ft_pwd(t_cmd *cmd, char ***env);
int		ft_cd(t_cmd *cmd, char ***env);

int     ft_print_exp(t_cmd* cmd, char **env);
char	**ft_change_env(char *var, char *str, char **env);
char	**ft_del_env(char *var, char **env);
void	ft_move_env(char **env, char **tmp, int pos);
int     ft_find_key(char *var, char **env);
char	*expand_dir(t_cmd *cmd, char *dir, char **env);

char	**ft_del_env(char *var, char **env);
char	**ft_change_env(char *var, char *str, char **env);
int		get_env_size(char **env);
void	ft_move_env(char **env, char **tmp, int pos);
int		ft_find_key(char *var, char **env);

#endif