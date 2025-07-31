#include "../minishell.h"

void	ft_exit(t_token *head)
{
	char	*arg;

	if (head->next)
	{
		if (head->next->next)
		{
			printf("BAYSAL SHELL: exit: too many arguments\n");
			return ; // exit(1);
		}
		arg = head->next->token;
		if (check_overflow(arg) == 0)
		{
			write(2, "bash: exit: ", 12);
			write(2, arg, ft_strlen(arg));
			write(2, ": numeric argument required\n", 28);
			exit(2);
		}


	}
	else
	{
		printf("exit\n");
		exit(0);
	}
}
