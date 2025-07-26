#include "../minishell.h"

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

int	executable(t_token *head)
{
	int		i;
	int		j;
	int		t_count;
	char	**args;
	char	**path;
	t_token	*tmp;
	char	*prog_name;
	int		pid;

	prog_name = malloc(ft_strlen(head->token) * 1000); // protecc
	i = 0;
	j = 0; // not 1 (args[0] is program name)
	path = ft_split(getenv("PATH"), ':');
	tmp = head;
	t_count = 0;
	while (tmp)
	{
		t_count++;
		tmp = tmp->next;
	}
	args = malloc((t_count + 1) * sizeof(char *));
	if (!args)
	{
		free(prog_name);
		free_array(path);
		return (-1);
	}
	tmp = head;
	while (tmp)
	{
		args[j] = ft_strdup(tmp->token);
		if (!args)
		{
			free_args(args, j); // free what we allocated so far
			free(prog_name);
			free_array(path);
			return (-1);
		}
		tmp = tmp->next;
		j++;
	}
	args[j] = NULL;
	while (path[i])
	{
		strcpy(prog_name, path[i]); //-42
		ft_strcat(prog_name, "/");
		ft_strcat(prog_name, head->token);
		if (!access(prog_name, X_OK))
		{
			pid = fork();
			if (pid == 0)
			{
				execve(prog_name, args, NULL);
				exit(1); // if fail is 1
			}
			else
			{
				wait(NULL);
				break ;
			}
		}
		i++;
	}
	if (!path[i])
		printf("command not found\n");
	free(prog_name);
	free_args(args, j);
	free_array(path);
	return (0);
}

void	check_command(t_token *head)
{
	if (!ft_strcmp(head->token, "echo"))
	{
		head = head->next;
		echo(head);
	}
	else if (!ft_strcmp(head->token, "pwd"))
		pwd(head);
	else if (!ft_strcmp(head->token, "cd"))
		cd(head);
	/*	else if (ft_strcmp(head->token, "env") == 0)
			env(head);
		else if (ft_strcmp(head->token, "export") == 0)
			export(head);
		else if (ft_strcmp(head->token, "unset") == 0)
			unset(head);*/
	else if (ft_strcmp(head->token, "exit") == 0)
		ft_exit(head);
	else
		// printf("invalid command\n");
		executable(head);
}
