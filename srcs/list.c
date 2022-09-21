#include "minishell.h"

t_list	*add_list(char *cmd, char *val, t_list **list)
{
	t_list	*n;

	if (!list)
		return (NULL);
	n = (t_list *)malloc(sizeof(t_list));
	if (!n)
		return (NULL);
	n->cmd = cmd;
	n->val = val;
	n->next = NULL;
	n->prev = *list;
	if (*list)
		(*list)->next = n;
	*list = n;
	return (n);
}

t_list	*copy_list(t_list *list)
{
	t_list	*copy;

	copy = NULL;
	while (list && list->prev)
		list = list->prev;
	while (list)
	{
		add_list(ft_strdup(list->cmd), ft_strdup(list->val), &copy);
		list = list->next;
	}
	add_list(ft_strdup(""), NULL, &copy);
	return (copy);
}

void	free_list(t_list *list)
{
	t_list	*t;

	while (list && list->prev)
		list = list->prev;
	while (list)
	{
		t = list->next;
		free(list->cmd);
		free(list->val);
		free(list);
		list = t;
	}
}

void	del_elem(t_list *elem, t_list **list)
{
	if (!elem)
		return ;
	if (elem->prev)
		elem->prev->next = elem->next;
	if (elem->next)
		elem->next->prev = elem->prev;
	if (*list == elem)
		*list = elem->prev;
	free(elem->cmd);
	free(elem->val);
	free(elem);
}

int	len_list(t_list *list)
{
	int	l;

	while (list && list->prev)
		list = list->prev;
	l = 0;
	while (list && ++l)
		list = list->next;
	return (l);
}
