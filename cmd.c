#include "minishell.h"

int	check_executable(t_token *head)
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
}


int has_pipe(char *input)
{
	int i = 0;
	while(input[i])
	{
		if (input[i] == '|')
			return 1;
		i++;
	}
	return 0;
}

t_cmd *fill_commands(t_cmd *head, char *input)
{
	int i = 0;
	t_cmd *tmp = head;
	t_cmd *tmp2 = NULL;
	char **pipe_split = ft_split(input,'|');
	while (pipe_split[i])
	{
		tmp->cmd = ft_split(pipe_split[i],' ');
		i++;
		insert_token(&tmp,tmp2);
		printf("%s",tmp->cmd[0]);
		tmp = tmp->next;

	}

	return head;
}
