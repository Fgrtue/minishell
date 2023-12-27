/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tests.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkopnev <kkopnev@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/15 20:21:47 by kkopnev       #+#    #+#                 */
/*   Updated: 2023/12/27 18:55:01 by jiajchen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <readline/readline.h> 


void print_lex(t_lexer* lexer);

void print_lex(t_lexer* lexer)
{
    printf("################################\n");
    while(lexer)
    {
        printf("LEXER: %p\n", lexer);
        printf("################################\n");
        printf("content:%s\n", lexer->content);
        printf("len: %i\n", lexer->len);
        printf("token: %i\n", lexer->token);
        printf("state: %i\n", lexer->state);
        printf("prev: %p\n", lexer->prev);
        printf("next: %p\n", lexer->next);
        printf("################################\n");
        lexer = lexer->next;
    }
	printf("################################\n");
}
void print_args(char** args)
{
    int i = 0;
    
    printf("The content:\n");
    while(args && args[i])
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
        printf("CMD: %p\n", cmd);
        printf("************************************\n");
        print_args(cmd->args);
        printf("The num of redir: %d\n", cmd->num_redir);
        printf("\nRedir: %p\n", cmd->redir);
		print_lex(cmd->redir);
        printf("\nprev: %p\n", cmd->prev);
        printf("next: %p\n", cmd->next);
        printf("************************************\n");
        cmd = cmd->next;
    }
}

int check_equal(char*   str)
{
    int i;
    int eq;

    i = -1;
    eq = 0;
    while(str[++i])
    {
        if (str[i] == '=')
           eq++; 
    }
    return (eq);
}

int main(int argc, char **argv, char **envp)
{
    char *line0="cd -";
    // char *line0="export key1=value1 key2=value2 key3 key4=";
    char *line1="export";
    // char *line1="\"\" $a $?ab$LS$loop ab\" \"\" 'hh$USER\"\'$USER\'$LS";

char *line2="cd ../../../../../..";
char *line3="cd ~";
char *line4="cd";
char *line5="cd ~/Desktop";
char *line6="unset HOME - cd ~";
char *line7="export HOME=/Users/user42 - cd ~";
char *line8="cd .. cool swag";
char *line9="cd Eyooooo";
char *line10="cd -";
char *line11="mkdir a - mkdir a/b - cd a/b - rm -r ../../a - cd ..";
char *line12="";
char *line13="echo";
char *line14="echo $NonExistingVar";
char *line15="echo $PATH";
char *line16="echo ~";
char *line17="echo -n -n -nnnn -nnnnm";
char *line18="echo -n -nnn hello -n";
char *line19="env";
char *line20="env Weeiirrddd";
char *line21="cd Weyooo - echo $?";
char *line22="random_cmd - echo $?";
char *line23="./file_that_is_not_an_executable";
char *line24="cat bla";
char *line25="hi";
char *line26="export ls=\"ls -l\" - $ls";
char *line27="echo $ls";
char *line28="export var=a - export $var=test - echo $var $a";
char *line29="export $var=test - unset var";
char *line30="export test1 - env";
char *line31="export test2= - env";
char *line32="export var - export var=hoi - export";
char *line33="export \"\" test=a";
char *line34="export test3=$HOME";
char *line35="echo ~";
char *line36="$SHLVL";
char *line37="\"\"";
char *line38="echo \"\\s\" ; echo \"\\\\s\"";
char *line39="echo \"12\"\"";
char *line40="<><>";
char *line41="echo \"bip | bip ; coyotte > < \"";
char *line42="echo \\>";
char *line43="echo $USER$var$USER$USER$USERtest$USER";
char *line44="echo bonjour \\; ls";
char *line45="$";
char *line46="$LESS$VAR";
char *line47="..";
char *line48="echo \'\"abc\"\'";
char *line49="echo \"\" bonjour";
char *line50="cat | cat | cat | ls";
char *line51="cat Makefile | grep pr | head -n 5 | cd file_not_exi";
char *line52="cat Makefile | grep pr | head -n 5 | hello";
char *line53="ls | exit";
char *line54="> test | echo blabla";
char *line55="exit > hoi.txt";
char *line56="env | grep OLDPWD";
char *line57="cd .. > derp.txt";
char *line58="cat - [ PRESS CTRL + C ]";
char *line59="cat - [ PRESS CTRL + \\ ]";
char *line60="cat - [ PRESS CTRL + D ]";
char *line61="> file";
char *line62="cat -e > test1 < test2";
char *line63="cat < test";
char *line64="echo 2 > out1 >> out2";
char *line65="echo 2 >> out1 > out2";
char *line66="./minishell";
char *line67="echo out2 >out2";
char *line68="echo test > file test1";
char *line69="Non_exist_cmd > salut";
char *line70="";
char *line71="unset all envs - env";
char *line72="unset all envs - export lol";
char *line73="Infinite file";
char *line74="export var=\"  truc\" - echo $var | cat -e";
char *line75="export var=\"truc  \" - echo $var | cat -e";
char *line76="echo \"$tests\"\"Makefile\"";
char *line77="echo \"$tests\"Makefile";
char *line78="echo \"$tests\" \"Makefile\"";
char *line79="export $var ($var does not exists)";
char *line80="export test=\"  foo    bar  \" ; echo $test";
char *line81="export test=\"  foo    bar  \" ; echo ab$test";
char *line82="export test=\"  foo    bar  \" ; echo \"ab\"\"$test\"";
char *line83="export test=\" foo   bar \" ; echo \"\"$test\"\"";
char *line84="export test=\" foo   bar \" ; echo \"\"\"$test\"\"\"";
char *line85="export var=\"s -la\" ; l$var"; // \ is not allowed
char *line86="export var=at ; c$var Makefile";
char *line87="export loop=\"bonjour$loop\" ; echo $loop";
char *line88="export test=\"file1 file2\" ; >$test";
char *line89="export test=\"file1 file2\" ; >\"$test\"";
char *line90="export test=\"file1 file2\" ; >$test >hey";
char *line91="export test=\"file1 file2\" ; >hey >$test";
char *line92="|";
char *line93="jddj";
char *line94="echo bonjour > > out";
char *line95="";
char *line96="echo bonjour > $test w/ test=\"o1 o2\"";
char *line97="echo bonjour >>> test";
char *line98="echo bonjour | |";
char *line99="echo bonjour |;";
char *line100="unset PATH ; echo $PATH";
char *line101="unset PATH ; ls";
char *line102="unset \"\" test";
char *line103="unset =";
char *line104="unset PWD";
char *line105="unset var";
char *line106="/bin/echo bonjour";
char *line107="top";
char *line108="cat wfeh | cat csijdsji | cat nfwir";
char *line109="<<$USER cat";
char *line110="clear";
char *line111="unset $(env | cut -d= -f1)";
char *line112="exit -12";
char *line113="< in wc -l | wc>out -l";

	t_lexer	*lst;
	t_cmd	*cmds;
    char**  env;

    env = create_env(envp);

    
    lst = ft_lexer(line2);
	// print_lex(lst);
	expand_env(&lst, env, 127);
	// print_lex(lst);
    printf("\n\n\n");
	polish_lex(&lst);
	// print_lex(lst);
	cmds = get_cmds(&lst, lst);
    // print_cmd(cmds);
    // ft_export(cmds, &env);
    
    ft_cd(cmds, &env);
    ft_pwd(cmds, &env);
	// print_cmd(cmds);
    // executor(cmds, env);

	ft_lexclean(&lst);
	ft_cmdclean(&cmds);
    
    free_arr(env);
 
	return (0);
}