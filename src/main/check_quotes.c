
#include <stdio.h>
#include <unistd.h>

int check_quotes(char*  str)
{
    int i;

    i = -1;
    if (!str)
        return (0);
    while(str[++i])
    {
        if (str[i] == '\"')
        {
            while(str[++i] && str[i] != '\"')
                continue;
            if (!str[i])
                return (0);
        }
        else if (str[i] == '\'')
        {
            while(str[++i] && str[i] != '\'')
                continue;
            if (!str[i])
                return (0);
        }
    }
    return (1);
}

int main (void)
{
    char    str[] = "the quotes \" are \" not \' \' closed \" \' \" right";

    // "/usr/bin/echo" and "/bin/echo" can execute 
    if (access("/usr/bin/echo", F_OK) == 0)
        printf("%d\n", check_quotes(str));

    return (0);
}