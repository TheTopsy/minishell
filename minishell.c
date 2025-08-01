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

// WHEN EVER \" OR \' OR SPACE OR $ IS ENCOUNTERED INCREMENT THE COUNT

int	count_input(char *input)
{
	int i;
	int opened;
	int l;
	char countspace;

	countspace = 1;
	opened = 0;
	l = 0;
	i = 0;
	while(input[i])
	{
		if(input[i] == '\"')
		{
			l++;
			while(input[i] && input[i] != '\"')
				i++;
			i++;
			opened = 0;
		}
		if(input[i] == '\'')
                {
                        l++;
                        while(input[i] && input[i] != '\'')
                                i++;
                        i++;
			opened = 0;
                }
		if(countspace && opened && input[i] == ' ')
                {
                        l++;
                        countspace = 0;
                }
		i++;
		opened = 1;
	}
	printf("%d\n", l);
	return l;
}

/*int	ft_strlen(char *str)
{
	int i;

	i = 0;
	while(str[i])
		i++;
	return i;
}*/

void do_absolutely_nothing()
{
	//nothing
}

void delete_token(t_token **head, t_token *token)
{
	t_token *tmp;
	t_token *prv;

	tmp = *head;
	if(tmp == token)
	{
		(*head)->next->prev = NULL;
		(*head) = (*head)->next;
		//free(tmp);
		return;
	}
	while(tmp)
	{
		if(tmp == token)
		{
			if(tmp->next)
			{
				tmp->next->prev = prv;
				prv->next = tmp->next;
			}
			else
				prv->next = NULL;
			//free(tmp);
			return;
		}
		prv = tmp;
		tmp = tmp->next;
	}
}

char *get_ev_name(char *str, int *pos)
{
	char *ev;
	char *tmp;
	int i;
	int j;

	i = *pos;
	j = 0;
	tmp = ft_calloc(ft_strlen(str), sizeof(char));
	if(str[i] == '$')
	{
		i++;
		/*if(!str[i] || str[i] == ' ' || str[i] == '\"' || str[i] == '\'')
		{
			*pos = i;
			tmp[0] = '$';
			tmp[1] = '\0';
			return tmp;
		}*/
		while(ft_isalnum(str[i]) || str[i] == '_')
			tmp[j++] = str[i++];
		tmp[j] = '\0';
		ev = getenv(tmp);
		//free(tmp);
		if(ev)
		{
			*pos = i;
			return ev;
		}
	}
	*pos = i;
	return NULL;
}

int	get_size(char *str)
{
	int i;
	int sum;
	char *ev;

	i = 0;
	sum = 0;
	while(str[i])
	{
		while(str[i] && str[i] != '$')
		{
			sum++;
			i++;
		}
		if(str[i] == '$')
		{
			ev = get_ev_name(str, &i);
			if(ev)
				sum += ft_strlen(ev);
		}
	}
	//printf("size = %d\n", sum);
	return sum;
}

void my_strjoin(char *res, char *s2)
{
	int j;
	int i;
	
	j = 0;
	i = 0;
	j = ft_strlen(res);
	while(s2[i])
		res[j++] = s2[i++];
	//return res;
}

char *expand(char *str)
{
	//printf(" str = %s\n",str);
	char *res = NULL;
	char *ev;
	int i;
	int j;

	i = 0;
	j = 0;
	res = ft_calloc(1 ,get_size(str));
	while(str[i])
	{
		while(str[i] && str[i] != '$')
		{
			res[j] = str[i++];
			j++;
		}
		if(str[i] == '$')
		{
			ev = get_ev_name(str, &i);
			if(ev)
			{
				my_strjoin(res, ev);
				j += ft_strlen(ev);
			}
		}
	}
	res[j] = '\0';
	return (res);
}

void search_and_expand(t_token **head)
{
	t_token *tmp;

	tmp = *head;
	while(tmp)
	{
		tmp->token = expand(tmp->token);
		tmp = tmp->next;
	}
}

t_token *split_input(char *input)
{
	int i;
	int j;
	char *tmp;
	t_token *head;

	i = 0;
	j = 0;
	head = NULL;
	while(input[i])
	{
		tmp = ft_calloc(ft_strlen(input) + 1, sizeof(char));
		while(input[i] && input[i] == ' ')
			i++;
		j = 0;
		while(input[i] && input[i] != ' ')
		{
			if(input[i] == '\'')
                        {
                                tmp[j++] = input[i++];
                                if(input[i] == '\'')
                                {
                                        i++;
                                        break;
                                }
                                while(input[i] && input[i] != '\'')
                                        tmp[j++] = input[i++];
                                if(input[i] && input[i] == '\'')
                                        tmp[j] = '\'';
                                if(input[++i] && input[i] == '\'')
                                {
                                        j++;
                                        break;
                                }
                                if(input[i] && input[i] == ' ')
                                        tmp[++j] = ' ';
                                else
                                        i--;
                                if(input[++i] && input[i] != ' ' && input[i] != '\'')
                                {
                                        j++;
                                        break;
                                }
                                else
                                        i--;
                                if(tmp[j] == ' ')
                                {
                                        j++;
                                }
                        }
			if(input[i] == '\"')
			{
				tmp[j++] = input[i++];
				if(input[i] == '\"')
				{
					i++;
					break;
				}
				while(input[i] && input[i] != '\"')
					tmp[j++] = input[i++];
				if(input[i] && input[i] == '\"')
					tmp[j] = '\"';
				if(input[++i] && input[i] == '\"')
                                {
					j++;
					break;
                                }
				if(input[i] && input[i] == ' ')
					tmp[++j] = ' ';
				else
					i--;
				if(input[++i] && input[i] != ' ' && input[i] != '\"')
				{
					j++;
					break;
				}
				else
					i--;
				if(tmp[j] == ' ')
				{
					j++;
				}
			}
			else
			{
				tmp[j++] = input[i++];
				if(input[i] && (input[i] == '\"' || input[i] == '\'' || input[i] == '$'))
					break;
			}
		}
		tmp[j] = '\0';
		if((tmp[0] == '\"' && tmp[1] == '\0') || (tmp[0] == '\'' && tmp[1] == '\0'))
			do_absolutely_nothing();
		else
			insert_token(&head, create_token(tmp));
	}
	return head;
}

int unclosed_quotes(char *input)
{
	int i;
	int d_count;
	int s_count;
	
	s_count = 0;
	d_count = 0;
	i = 0;
	while(input[i])
	{
		if(input[i] == '\"')
		{
			i++;
			d_count++;
			while(input[i] && input[i] != '\"')
				i++;
			if(input[i])
				d_count++;
			else
				return (0);
		}
		if(input[i] == '\'')
                {
			i++;
                        s_count++;
                        while(input[i] && input[i] != '\'')
                                i++;
                        if(input[i])
			       	s_count++;
                        else
                                return (0);
                }
		i++;
	}
	//printf("s = %d  d = %d\n", s_count, d_count);
	if(s_count || d_count)
	{
		if(((s_count % 2) != 0) || ((d_count % 2) != 0))
			return (0);
	}
	return (1);
}

int main()
{
	char *input;
	t_token *head;

	head = NULL;
	while(1)
	{
		start_signals();
		input = readline(RED"➜  "RESET CYAN"~ "RESET);
		if (!input)
		 ft_exit(NULL);
		add_history(input);
		if(*input)
		{
			if(!unclosed_quotes(input))
			{
				printf("unclosed quotes\n");
				return 0;
			}
			head = split_input(input);
			search_and_expand(&head);
			execute_redir(head);
			/*while(head)
			{
				if(head->next)
					printf("%s -> ", (head)->token);
				else
					printf("%s\n", (head)->token);
				head = head->next;
			}*/
			//break;
		}
	}
}
