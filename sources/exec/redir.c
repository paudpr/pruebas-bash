#include "minishell.h"

void redir_in(t_def *def, char *infile)
{
    int fd;

    (void)def;
    fd = open(infile, O_RDONLY);
    if(fd < 0)
        perror("");
    dup2(fd, STDIN_FILENO);
    close(fd);
}

void redir_out(t_def *def, char *outfile)
{
    int fd;

    (void)def;
    fd = open(outfile, O_RDWR | O_CREAT | O_TRUNC, 0644);
    if(fd < 0)
        perror("");
    dup2(fd, STDOUT_FILENO);
    close(fd);
}

void check_redir(t_def *def)
{
    int i;

    i = 0;
    while(def->argv[i])
    {
        if(def->type[i] == 0)
        {
            i++;
            redir_in(def, "/tmp/heredoc");
        }
        if(def->type[i] == 1)
            redir_in(def, def->argv[++i]);
        if(def->type[i] == 2)
            redir_out(def, def->argv[++i]);
        if(def->type[i] == 3)
            redir_out(def, def->argv[++i]);
        i++;
    }
}
