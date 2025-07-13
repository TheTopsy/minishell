#include "minishell.h"

t_token *lst_new (const char *text)
{
	t_token *node = malloc(sizeof(t_token));
	if (!node)
		exit(1);
	node->token = strdup(text);
	node->next = NULL;
	node->prev = NULL;
	return node;
}

t_token  *lst_last(t_token *lst)
{
        t_token  *tmp;

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

void echo(t_token *head)
{
	t_token *last = lst_last(head);
   	while (head)
	{
		if (head->token[0] == '>')
		{
			int fd = open(head->next->token, O_CREAT | O_RDWR | O_TRUNC, 0644);
			ft_putstr_fd(head->prev->token,fd);
			exit(1);
		}
		else
		{
       	 		printf("%s", head->token);
       	 		if (head->next)
            			putchar(' ');
		}
        	head = head->next;
    	}
    	putchar('\n');
}

int main(void)
{
	t_token *tk1 = lst_new("zbi");
	t_token *tk2 = lst_new(">");
	t_token *tk3 = lst_new("hello.txt");
	tk1->next = tk2;
	tk2->next = tk3;
	tk2->prev = tk1;
	tk3->prev = tk2;
	echo(tk1);
}

