#include "../minishell.h"

void	ft_exit(t_token *head)
{
	char *args;

	if (head && head->next)
	{
		if (head->next->next)
		{
			printf("BAYSAL SHELL: exit: too many arguments\n");
			return ; // exit(1);
		}
		args = head->next->token;
		if (!check_overflow(args))
		{
			write(2, "bash: exit: ", 12);
			write(2,args,ft_strlen(args));
			write(2, ": numeric argument required\n", 28);
			exit(2);
		}
		else
		{
			printf("exit\n");
			exit(ft_atoi(args));
		}


	}
	else
	{
		printf("exit\n");
		exit(0);
	}
}
