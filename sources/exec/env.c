// #include "minishell.h"

// t_env   *get_struct_env(char **environ)
// {
//     t_env   *env;

//     env =  malloc(sizeof(t_env));
//     if(env == NULL)
//         return (NULL);
//     (void)environ;
//     if(ft_double_len(environ) == 0)
//     {
//         printf("env borrado\n");
//         env->shlvl = 1;
//         build_environ(env);             //!!!!!!!!!!!!!!!! mala copia del env borrado
//     }
//     else
//     {
//         env->shlvl = get_shlvl(environ);
//         copy_environ(environ, env);
//     }
//     return (env);
// }

// void build_environ(t_env *env)
// {
//     char cwd[PATH_MAX];

//     env->env = ft_calloc(sizeof(char *), 3);
//     if(env->env == NULL)
//         return ; 
//     getcwd(cwd, sizeof(cwd));
//     env->env[0] = ft_strjoin("PWD=", cwd);
//     env->env[1] = ft_strjoin("SHLVL=", ft_itoa(env->shlvl));
//     env->env[2] = ft_strjoin("_=", cwd);
//     printf("antes de asignar memoria -> %p\n", env->path);
//     env->path = ft_calloc(sizeof(char *), 1);
//     if(env->path == NULL)
//         return ;
//     printf("despues de asignar memoria -> %p\n", env->path);
// 	// env->path = NULL;   //!!!!!!!!!!!!!!!!!!!!!!!!! esto será pa revisar después
// }



// int get_shlvl(char **environ)
// {
//     int i;
//     char *aux;
//     char *shlvl;
// 	int lvl;

//     i = 0;
//     shlvl = NULL;

//     // int j = -1;
//     // while(environ[++j])
//     //     printf("ENVIRON -> %s\n", environ[j]);
//     // printf("environ[p] -> %p\n", environ);
//     // printf("-------------- > %d\n", ft_double_len(environ));
//     while(i < ft_double_len(environ))
//     {
//         // printf("environ[i] -> %s\n", environ[i]);
//         // printf("comparación -> %d\n", ft_strncmp(environ[i], "SHLVL=", 6));
//         if(ft_strncmp(environ[i], "SHLVL=", 6) != 0)
//             // printf("ENTRO EN LA CONDICION\n");
//             aux = ft_strdup(environ[i]);
//         i++;
//     }
//     // printf("-----> %p\n%p\n", shlvl+1, aux);
//     shlvl = ft_strchr(aux, '=');
//     // printf("-----> %p\n%p\n", shlvl, aux);
//     shlvl++;
// 	lvl = ft_atoi(shlvl);
// 	free(aux);
//     return(lvl);
// }

// void copy_environ(char **environ, t_env *env)
// {
//     char *path;
//     char *aux;
//     int i;

//     i = 0;
//     env->env = ft_calloc(sizeof(char *), ft_double_len(environ) + 1);
//     if(env->env == NULL)
//         return ;
//     while (environ[i])
//     {
// 		if (ft_strncmp(environ[i], "SHLVL=", 6))
//         	env->env[i] = ft_strdup(environ[i]);
// 		else
// 			env->env[i] = ft_strjoin("SHLVL=", ft_itoa(env->shlvl));
//         if (ft_strnstr(environ[i], "PATH=", 5))
// 			aux = ft_strdup(environ[i]);
// 		i++;
//     }
//     path = ft_strchr(aux, '/');
//     env->path = ft_split(path, ':');
//     free(aux);
// }































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
    {
        // env->shlvl = get_shlvl(environ);
        copy_environ(environ, env);
    }
    return (env);
}

int get_shlvl(char **environ)
{
    int i;
    char *aux;
    char *shlvl;
	int lvl;

    i = 0;
    shlvl = NULL;
    while(i < ft_double_len(environ))
    {
        if(ft_strncmp(environ[i], "SHLVL=", 6) == 0)
            aux = ft_strdup(environ[i]);
        i++;
    }
    shlvl = ft_strchr(aux, '=');
    shlvl++;
    printf("puntero shlvl -> %p\n", shlvl);
	lvl = ft_atoi(shlvl);
	free(aux);
    printf("level -> %d\n", lvl);
    return(lvl);
}

void build_environ(t_env *env)
{
    char cwd[PATH_MAX];

    env->env = ft_calloc(sizeof(char *), 3);
    if(env->env == NULL)
        return ; 
    getcwd(cwd, sizeof(cwd));
    env->env[0] = ft_strjoin("PWD=", cwd);
    env->env[1] = ft_strjoin("SHLVL=", ft_itoa(env->shlvl));
    env->env[2] = ft_strjoin("_=", cwd);
	env->path = NULL;   //!!!!!!!!!!!!!!!!!!!!!!!!! esto será pa revisar después
}

void copy_environ(char **environ, t_env *env)
{
    char *path;
    char *aux;
    int i;

    i = 0;
    env->env = ft_calloc(sizeof(char *), ft_double_len(environ) + 1);
    if(env->env == NULL)
        return ;
    while (environ[i])
    {
		if (ft_strncmp(environ[i], "SHLVL=", 6))
        	env->env[i] = ft_strdup(environ[i]);
		else
			env->env[i] = ft_strjoin("SHLVL=", ft_itoa(env->shlvl));
        if (ft_strnstr(environ[i], "PATH=", 5))
			aux = ft_strdup(environ[i]);
		i++;
    }
    path = ft_strchr(aux, '/');
    env->path = ft_split(path, ':');
    free(aux);
}