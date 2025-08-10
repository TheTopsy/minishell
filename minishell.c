#include "minishell.h"

t_token	*create_token(char *token)
{
	t_token	*node1;

	node1 = (t_token *)malloc(sizeof(t_token));
	if (!node1)
		return (NULL);
	node1->token = token;
	node1->next = NULL;
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

t_env *create_env(char *key, char *val)
{
        t_env *node1;

        node1 = (t_env *)malloc(sizeof(t_env));
        if (!node1)
                return (NULL);
        node1->value = val;
        node1->key = key;
        node1->next = NULL;
        return node1;
}

t_env *ft_envlast(t_env *lst)
{
        if (!lst)
                return (NULL);
        while (lst->next)
                lst = lst->next;
        return (lst);
}

void    insert_env(t_env **lst, t_env *new)
{
        t_env *last;

        if (!lst || !new)
                return ;
        last = ft_envlast(*lst);
        if (*lst)
                last->next = new;
        else
                *lst = new;
}


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

char *my_getenv(char *key, t_env *env_head)
{
	int i;

	while(env_head)
	{
		i = 0;
		while(key[i] && env_head->key[i] && key[i] == env_head->key[i])
			i++;
		if(i == (int)ft_strlen(key))
			return env_head->value;
		env_head = env_head->next;
	}
	return NULL;
}

char *get_ev_name(char *str, int *pos, t_env *env_head)
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
		if(!str[i] || str[i] == ' ' || str[i] == '\"' || str[i] == '\'')
		{
			*pos = i;
			tmp[0] = '$';
			tmp[1] = '\0';
			return tmp;
		}
		while(ft_isalnum(str[i]) || str[i] == '_')
			tmp[j++] = str[i++];
		tmp[j] = '\0';
		ev = my_getenv(tmp, env_head);
		if(ev)
		{
			*pos = i;
			return ev;
		}
	}
	*pos = i;
	return NULL;
}

int	get_size(char *str, t_env *env_head)
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
			ev = get_ev_name(str, &i, env_head);
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
}

char *expand(char *str, t_env *env_head, int *expandable)
{
	char *res = NULL;
	char *ev;
	int i;
	int j;

	i = 0;
	j = 0;
	res = ft_calloc(1 ,get_size(str, env_head));
	while(str[i])
	{
		while(str[i] && str[i] != '$')
			res[j++] = str[i++];
		if(str[i] == '$')
		{
			*expandable = 1;
			ev = get_ev_name(str, &i, env_head);
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

void split_expansion(t_token **head, t_token *target)
{
        int i;
        int j;
        char *str;
        t_token *first;
	t_token *last;

        i = 0;
        j = 0;
        str = ft_calloc(1, ft_strlen(target->token));
	first = NULL;
        while(1)
        {
                if(target->token[i] == ' ' || !target->token[i])
                {
                        str[j] = '\0';
                        j = 0;
			insert_token(&first, create_token(str));
			i++;
			str = ft_calloc(1, ft_strlen(target->token));
                }
		if(!target->token[i])
			break;
                str[j++] = target->token[i++];
        }
	target->prev->next = first;
	last = ft_lstlast(first);
	last->next = target->next;
	free(target);
}

void search_and_expand(t_token **head, t_env *env_head)
{
	t_token *tmp;
	int expandable;
       	
	expandable = 0;
	tmp = *head;
	while(tmp)
	{
		if(tmp->token[0] != '\'')
		{
			tmp->token = expand(tmp->token, env_head, &expandable);
			if(expandable && tmp->token[0] != '\"')
				split_expansion(head, tmp);
			expandable = 0;
		}
		tmp = tmp->next;
	}
}

char *extract_token(char *str, int start, int end)
{
	char *res;
	int i;

	i = 0;
	res = ft_calloc(ft_strlen(str), sizeof(char));
	while(start < end)
	{
		if((str[start] == '\'' && str[start + 1] == '\'') || (str[start] == '\"' && str[start + 1] == '\"'))
			start += 2;
		else
			res[i++] = str[start++];
	}
	//printf("\n");
	res[i] = '\0';
	//printf("%s\n", res);
	return res;
}

t_token *split_input(char *input)
{
	t_token *head = NULL;
	int dbl;
	int sgl;
	int i;
	int start;

	dbl = 0;
	sgl = 0;
	i = 0;
	start = 0;
	while(input[i])
	{
		if(input[i] == ' ' && !dbl && !sgl)
		{
                        insert_token(&head, create_token(extract_token(input, start, i)));
                        while(input[i] && input[i] == ' ')
                                i++;
                        start = i;
                }
		if(input[i] && input[i] == '\'' && !sgl)
			sgl = 1;
		else if(input[i] && input[i] == '\'' && sgl)
			sgl = 0;
		if(input[i] && input[i] == '\"' && !dbl)
			dbl = 1;
		else if(input[i] && input[i] == '\"' && dbl)
                        dbl = 0;
		i++;
	}
	insert_token(&head, create_token(extract_token(input, start, i)));
	return head;
}

t_token *spli_input(char *input)
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
			if(input[i] == '\"' && input[i - 1] == ' ')
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

char *get_key(char *env)
{
	int i;
	char *key;

	i = 0;
	key = ft_calloc(ft_strlen(env), sizeof(char));
	while(env[i] && env[i] != '=')
	{
		key[i] = env[i];
		i++;
	}
	key[i] = '\0';
	return key;
}

char *get_val(char *env)
{
	int i;
	int j;
	char *val;

	i = 0;
	j = 0;
	val = ft_calloc(ft_strlen(env), sizeof(char));
	while(env[i] && env[i] != '=')
		i++;
	i++;
	while(env[i])
		val[j++] = env[i++];
	val[j] = '\0';
	return val;
}

t_env *list_env(char **envp)
{
	int i;
	t_env *env_head;

	env_head = NULL;
	i = 0;
	while(envp[i])
	{
		insert_env(&env_head, create_env(get_key(envp[i]), get_val(envp[i])));
		i++;
	}
	return env_head;
}
//handle '"$a"'
void	clean_quotes(t_token *head)
{
	char *str;
	int i;
	int j;

	i = 0;
	j = 0;
	while(head)
	{
		str = ft_calloc(1, ft_strlen(head->token));
		while(head->token[i])
		{
			if(head->token[i] == '\"')
			{
				i++;
				while(head->token[i] && head->token[i] != '\"')
					str[j++] = head->token[i++];
				i++;
			}
			if(head->token[i] == '\'')
                        {
                                i++;
                                while(head->token[i] && head->token[i] != '\'')
                                        str[j++] = head->token[i++];
                                i++;
                        }
			while(head->token[i] && head->token[i] != '\"' && head->token[i] != '\'')
				str[j++] = head->token[i++];
		}
		str[j] = '\0';
		free(head->token);
		head->token = str;
		head = head->next;
		j = 0;
		i = 0;
	}
}

int main(int ac, char **av, char **envp)
{
	char *input;
	t_token *head;
	t_env *env_head;

	env_head = NULL;
	head = NULL;
	env_head = list_env(envp);
	env_head->key[0] = 'a';
	env_head->key[1] = '\0';
	env_head->value[0] = 'a';
	env_head->value[1] = 'b';
	env_head->value[2] = ' ';
	env_head->value[3] = 'c';
	env_head->value[4] = 'd';
	env_head->value[5] = '\0';
	while(1)
	{
		input = readline("% ");
		// if (!input)
		// ft_exit(NULL);
		add_history(input);
		if(*input)
		{
			if(!unclosed_quotes(input))
			{
				printf("unclosed quotes\n");
				return 0;
			}
			head = split_input(input);
			clean_quotes(head);
			search_and_expand(&head, env_head);
			while(head)
			{
				if(head->next)
					printf("%s -> ", (head)->token);
				else
					printf("%s\n", (head)->token);
				head = head->next;
			}
			//break;
		}
	}
}
