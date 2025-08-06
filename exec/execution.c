#include "../minishell.h"

int	executable(t_token *head)
{
	int		i;
	int		j;
	int		t_count;
	int	fd;
	char	**args;
	char	**path;
	t_token	*tmp;
	char	*prog_name;
	int		pid;
	
	prog_name = malloc(ft_strlen(head->token) * 1000); // protecc
	i = 0;
	j = 0; // not 1 cuz args[0] is program name
	path = ft_split(getenv("PATH"), ':');
	tmp = head;
	t_count = lst_len(tmp);
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
	fd = open(args[0], __O_DIRECTORY);
	if (fd >= 0)
	{
		ft_putstr_fd("BAYSAL SHELL: ",STDERR_FILENO);
		ft_putstr_fd(args[0],STDERR_FILENO);
		ft_putstr_fd(": Is a directory\n",STDERR_FILENO);
	}
	if (args[0][0] == '/' || (args[0][0] == '.' && args[0][1] == '/'))
	{
		if (!access(args[0],F_OK))
		{
			signal(SIGINT,SIG_IGN);
			pid = fork();
			if (pid == 0)
			{
				signal(SIGINT,SIG_DFL);
				execve(args[0],args,NULL);
				exit(0);
			}
			else
			{
				wait(NULL);
				return 0;
			}

		}
		else
		{
			if (ft_strchr(args[0], '/'))
			{
				ft_putstr_fd("BAYSAL SHELL: ",STDERR_FILENO);
				ft_putstr_fd(args[0],STDERR_FILENO);
				ft_putstr_fd(" : no such file or directory\n",STDERR_FILENO); // this should be in another function so i can return 127
				return 127;
			}
		}
	}

	while (path[i])
	{
		strcpy(prog_name, path[i]); //-42
		ft_strcat(prog_name, "/");
		ft_strcat(prog_name, head->token);
		if (!access(prog_name, X_OK))
		{
			signal(SIGINT,SIG_IGN);
			pid = fork();
			if (pid == 0)
			{
				signal(SIGINT,SIG_DFL);
				execve(prog_name, args, NULL);
				exit(1); // if fail is 1
			}
			else
			{
				signal(SIGINT,SIG_IGN);
				int status;
				wait(&status);
				if (WIFEXITED(status))
					return 1;
				//return 1;
				break ;
			}
		}
		i++;
	}
	if (!path[i])
		printf("command not found\n");
	//free(prog_name);
	//free_args(args, j);
	//free_array(path);
	return (0);
}

void	check_command(t_token *head)
{
	//start_signals();
	if (!head || !head->token)
		return ;
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
	else if (ft_strcmp(head->token, "code") == 0)
	{
		chdir("/media/waissi/niggusgus");
		system("/media/waissi/niggusgus/a.out");
	}
	else
		// printf("invalid command\n");
		executable(head);
}

void	execute_redir(t_token *head)
{
	char	*filename;
	t_token	*curr;
	int		type;
	int		f_stdin;
	int		f_stdout;
	int had_sig;

	had_sig = 0;
	f_stdin = -1;
	f_stdout = -1;
	if (!head )
		return ;
	curr = head;
	while (curr)
	{
		type = redirect_type(curr);
		if (type > 0)
		{
			if ((type == 1 || type == 2) && f_stdout == -1) // > or >>
				f_stdout = dup(STDOUT_FILENO);
			else if ((type == 3 || type == 4) && f_stdin == -1) // < or <<
				f_stdin = dup(STDIN_FILENO);
		}
		curr = curr->next;
	}
	curr = head;
	while (curr)
	{
		type = redirect_type(curr);
		if (type > 0)
		{
			if (!curr->next)
			{
				printf("Syntax error: missing filename for redirection\n");
				return ;
			}
			filename = curr->next->token;
			if (!redirect_occur(curr, filename))
				had_sig = 1;
			remove_redir_tokens(&head, curr);
			curr = head;
		}
		else
		{
			curr = curr->next;
		}
	}
	if (head && head->token && !had_sig)
		check_command(head);
	restore_fd(f_stdout, f_stdin);
}
