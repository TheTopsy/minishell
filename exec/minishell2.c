#include "../minishell.h"

void echo_file(t_token *head, char *s, int flag)
{
	t_token *tmp;
	int fd;
	while (head)
        {
                tmp = check_redirect(head);
                if (tmp)
                {
                        fd = open(tmp->next->token, O_CREAT | O_RDWR | O_TRUNC, 0644);
                                ft_putstr_fd(s,fd);
                                head = head->next;
			if (!flag)
                        	ft_putstr_fd("\n",fd);
                }
		head = head->next;
	}
}

void echo(t_token *head)
{
	t_token *last;
	int count;
	char s[99999];
	t_token *word;
	int nl_flag;
	t_token *tmp;

	nl_flag = check_nl(head);
	count = count_redirect(head);
	last = lst_last(head);
	word = check_redirect(head);
	if (nl_flag)
		head = head->next;
	tmp = head;
	if (word)
	{
		while (tmp != word)
		{
			ft_strcat(s, tmp->token);
			if (tmp->next != word)
				ft_strcat(s," ");
			tmp = tmp->next;
		}
		echo_file(head,s,nl_flag);
	}
	else
	{
   		while (head)
		{
				
       	 		printf("%s", head->token);
       	 		if (head->next)
            			putchar(' ');
        		head = head->next;
		}
		if (nl_flag == 0)	
    			putchar('\n');
    	}
}
/*
int main(void)
{
	t_token *tk1 = lst_new("-n");
	t_token *tk2 = lst_new("bibo");
	t_token *tk3 = lst_new("a");
	t_token *tk4 = lst_new("kbir.txt");
	t_token *tk5 = lst_new("a");
	t_token *tk6 = lst_new("w.txt");
	t_token *tk7 = lst_new(">");
	t_token *tk8 = lst_new("kbiiiiir.txt");
	t_token *tk9 = lst_new(">");
	t_token *tk10 = lst_new("mn.txt");

	tk1->next = tk2;
	tk2->next = tk3;
	tk2->prev = tk1;
	tk3->next = tk4;
	tk3->prev = tk2;
	tk4->next = tk5;
	tk4->prev = tk3;
	tk5->next = tk6;
	tk5->prev = tk4;
	tk6->prev = tk5;
	tk6->next = tk7;
	tk7->next = tk8;
	tk7->prev = tk6;
	tk8->next = tk9;
	tk8->prev = tk7;
	tk9->next = tk10;
	tk9->prev = tk8;
	tk10->prev = tk9;

	echo(tk1);
}
*/
