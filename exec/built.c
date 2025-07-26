#include "../minishell.h"

void	echo(t_token *head)
{
	int	i;
	int	nl_flag;

	if (!head)
	{
		printf("\n");
		return ;
	}
	i = check_nl(head);
	nl_flag = i;
	if (nl_flag)
		head = head->next;
	while (head)
	{
		printf("%s", head->token);
		if (head->next)
			printf(" ");
		head = head->next;
	}
	if (nl_flag == 0)
		printf("\n");
}

void	pwd(t_token *head) // should accept no arguments
{
	char *pwd;

	(void)head;
	pwd = getcwd(NULL, 0); // protect this
	if (pwd != NULL)
	{
		printf("%s\n", pwd);
		free(pwd);
		return ;
	}
	else
	{
		perror("pwd");
		return ;
	}
}

void	cd(t_token *head)
{
	char	*path;

	if (head->next == NULL)
	{
		path = getenv("HOME");
		if (!path)
		{
			printf("cd: HOME not set\n");
			return ;
		}
	}
	else
		path = head->next->token;
	if (chdir(path))
		perror("cd");
}
