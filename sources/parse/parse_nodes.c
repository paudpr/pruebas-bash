#include "minishell.h"

void	print_nodes(t_def *def)
{
	int	i;

	while (def)
	{
		printf("%p\t%p\n", def, def->next);
		i = -1;
		while (++i < ft_double_len(def->argv))
			printf("%s\t", def->argv[i]);
		i = -1;
		printf("\n");
		while (++i < ft_double_len(def->argv))
			printf("%d\t", def->type[i]);
		printf("\n\n");
		def = def->next;
	}
}

int	count_argvs(t_list *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		if (!ft_strncmp(lst->content, "|", 1))
			break ;
		count++;
		lst = lst->next;
	}
	return (count);
}

int	get_type(char *argv)
{
	int	type;

	if (!ft_strncmp(argv, "<<", 2))
		type = T_HD;
	else if (!ft_strncmp(argv, "<", 1))
		type = T_RIN;
	else if (!ft_strncmp(argv, ">>", 2))
		type = T_APP;
	else if (!ft_strncmp(argv, ">", 1))
		type = T_ROUT;
	else if (!ft_strncmp(argv, "*", 1))
		type = T_WC;
	else
		type = T_CMD;
	return (type);
}

t_list *get_files(void)
{
	DIR *dir;
	struct dirent *items;
	t_list *lst;
	char check_hidden;

	lst = NULL;
	dir = opendir(".");
	if (dir != NULL)
	{
		items = readdir(dir);
		while((items = readdir(dir)) != NULL)
		{
			check_hidden = (char)items->d_name[0];
			if (check_hidden != '.')
				ft_lstadd_back(&lst, ft_lstnew(ft_strdup(items->d_name)));
		}
	}
	closedir(dir);
	return(lst);
}

t_def *get_wildcard(t_def **node)
{
	int i;
	t_def *new;
	t_list *lst;
	t_list *aux;

	lst = get_files();
	if (lst == NULL)
		return (node);
	new = ft_calloc(1, sizeof(t_def));
	if (new == NULL)
		return (new);
	i = ft_double_len((*node)->argv) + ft_lstsize(lst);
	new->argv = ft_calloc(i + 1, sizeof(char *));
	if (new->argv == NULL)
		return (NULL);
	new->type = ft_calloc(i + 1, sizeof(int));
	if (new->type == NULL)
		return (NULL);
	print_nodes(*node);
	free_list(node);
	while (lst)
	{
		// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		aux = lst;
		lst = lst->next;
		free(aux);
	}
	free(lst);


	return(*node);
}

t_def	*create_node(int size, t_list *lst)
{
	int		i;
	t_def	*new;

	new = ft_calloc(1, sizeof(t_def));
	if (new == NULL)
		return (new);
	new->argv = ft_calloc(size + 1, sizeof(char *));
	if (new->argv == NULL)
		return (NULL);
	new->type = ft_calloc(size + 1, sizeof(int));
	if (new->type == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		new->argv[i] = ft_strdup(lst->content);
		new->type[i] = get_type(new->argv[i]);
		if (new->type[i] && new->type[i] < 5)
		{
			i++;
			lst = lst->next;
			new->argv[i] = ft_strdup(lst->content);
			new->type[i] = new->type[i - 1];
			if (i >= size)
				break ;
		}
		if (new->type[i] && new->type[i] == 6)
			new = get_wildcard(&new);
		i++;
		lst = lst->next;
	}
	return (new);
}

t_def	*parse_nodes(t_list *lst, t_env *env)
{
	int		size;
	int		flag;
	t_def	*new;
	t_def	*nodes;

	size = 0;
	flag = 0;
	nodes = NULL;
	while (lst)
	{
		if (size == 0)
		{
			size = count_argvs(lst);
			flag = 1;
		}
		if (flag == 1)
		{
			new = create_node(size, lst);
			clean_com(new->argv, env);
			mini_lstadd_back(&nodes, new);
			flag = 0;
		}
		size--;
		lst = lst->next;
		if (size == 0 && lst && lst->next)
			lst = lst->next;
	}
	return (nodes);
}
