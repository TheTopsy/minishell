#include "../minishell.h"

t_token	*lst_new(const char *text)
{
	t_token	*node;

	node = malloc(sizeof(t_token));
	if (!node)
		exit(1);
	node->token = strdup(text);
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

t_token	*lst_last(t_token *lst)
{
	t_token	*tmp;

	if (lst)
	{
		tmp = lst;
		while (tmp->next)
		{
			tmp = tmp->next;
		}
		return (tmp);
	}
	return (NULL);
}

int lst_len(t_token *head)
{
	int i = 0;
	while (head)
	{
		i++;
		head = head->next;
	}
	return i;
}

int lst_len_cmd(t_cmd *head)
{
	int i = 0;
	while (head)
	{
		i++;
		head = head->next;
	}
	return i;
}


int	token_len(t_token *head)
{
	int	i;
	int	ttl;

	i = 0;
	ttl = 0;
	while (head && head->token[0] != '>' && head->token[0] != '<')
	{
		while (head->token[i])
			i++;
		head = head->next;
		ttl += i + 1;
	}
	return (ttl);
}
