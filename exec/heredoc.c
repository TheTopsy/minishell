#include "../minishell.h"

void	heredoc_redir(char *delimiter)
{
	int		pipefd[2];
	char	*line;

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return ;
	}
	int pid = fork();
	if (pid == 0)
	{
		//start_signals();
		while (1)
		{
			line = readline("> ");
			if (ft_strcmp(line, delimiter) == 0)
			{
				free(line);
				break ;
			}
			// call expand_var
			write(pipefd[1], line, ft_strlen(line));
			write(pipefd[1], "\n", 1);
			free(line);
			// free expand
		}
	}
	else
	{
		wait(NULL);
		//break;
		exit(0);
	}
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	//signal(SIGINT, signal_handler);
}
