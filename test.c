#include "minishell.h"

t_token	*create_token(char *token)
{
	t_token	*node1;

	node1 = (t_token *)malloc(sizeof(t_token));
	if (!node1)
		return (NULL);
	node1->token = token;
	node1->next = NULL;
	//printf("$%s\n", node1->token);
	return node1;
}

t_token	*ft_lstlast(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	insert_token(t_token **lst, t_token *new)
{
	t_token *last;

	if (!lst || !new)
		return ;
	last = ft_lstlast(*lst);
	if (*lst)
	{
		last->next = new;
		new->prev = last;
	}
	else
		*lst = new;
}

int	count_input(char *input)
{
	int i;
	int k;
	char countspace;

	countspace = 0;
	i = 0;
	k = 1;
	while(input[i])
	{
		if(input[i] == ' ' && countspace)
		{
			k++;
			countspace = 0;
			while(input[i] == ' ')
				i++;
		}
		else
		{
			countspace = 1;
			i++;
		}
	}
	if(i == 0 || input[--i] == ' ')
		k--;
	return k;
}

t_token **split_input(char *input)
{
	int i;
	int j;
	int k;
	char *tmp;
	t_token *head;
	t_token **heads;
	i = 0;
	k = count_input(input);
	j = 0;
	head = NULL;
	while(k--)
	{
		tmp = malloc(ft_strlen(input));
		while(input[i] && input[i] == ' ')
			i++;
		j = 0;
		while(input[i] && input[i] != ' ')
			tmp[j++] = input[i++];
		tmp[j] = '\0';
		insert_token(&head, create_token(tmp));
	}
	heads = &head;
	return heads;
}

int main()
{
	char *input;
	t_token **head;

	while(1)
	{
		input = readline("% ");
		add_history(input);
		if(*input)
		{
			head = split_input(input);
			echo(*head);
			//break;
		}
	}
}
