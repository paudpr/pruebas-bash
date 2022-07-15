#include "minishell.h"

t_env   *get_struct_env(char **environ)
{
    t_env   *env;

    env =  malloc(sizeof(t_env));
    if(env == NULL)
        return (NULL);
    if(ft_double_len(environ) == 0)
    {
        env->shlvl = 1;
        build_environ(env);     //!!!!!!!!!!!!!!!! mala copia del env borrado
    }
    else
        copy_environ(environ, env);
    return (env);
}

void build_environ(t_env *env)
{
    char cwd[PATH_MAX];

    env->env = ft_calloc(sizeof(char *), 3);
    if(env->env == NULL)
        return ; 
    getcwd(cwd, sizeof(cwd));
    env->shlvl = 1;
    env->env[0] = ft_strjoin("PWD=", cwd);
    env->env[1] = ft_strjoin("SHLVL=", ft_itoa(env->shlvl));
    env->env[2] = ft_strjoin("_=", cwd);
    env->path = NULL;
}

void    copy_environ(char **environ, t_env *env)
{
    char    *point;
    char    *aux_path;
    char    *aux_shlvl;
    int     i;
	char	*shlvl;

    i = 0;
    env->env = ft_calloc(sizeof(char *), ft_double_len(environ) + 1);   //he borrado el +1, comprobar que no de problemas
    if(env->env == NULL)
        return ;
    while (environ[i])
    {
		if (ft_strncmp(environ[i], "SHLVL=", 6))
        	env->env[i] = ft_strdup(environ[i]);
		else
        {
            aux_shlvl = ft_strdup(environ[i]);
            point = ft_strchr(aux_shlvl, '=') + 1;
            env->shlvl = ft_atoi(point) + 1;
			shlvl = ft_itoa(env->shlvl);
			env->env[i] = ft_strjoin("SHLVL=", shlvl);
			free(aux_shlvl);
			free(shlvl);
        }
        if (ft_strnstr(environ[i], "PATH=", 5))
			aux_path = ft_strdup(environ[i]);
		i++;
    }
    point = ft_strchr(aux_path, '/');
    env->path = ft_split(point, ':');
    free(aux_path);
}
