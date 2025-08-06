#include "../minishell.h"

int	heredoc_redir(char *delimiter)
{
	int		pipefd[2];
	int	status;
	char	*line;

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return -1;
	}
	signal(SIGINT,SIG_IGN);
	int pid = fork();
	if (pid == 0)
	{
		//start_signals();
		signal(SIGINT,SIG_DFL);
		//close(pipefd[0]);
		while (1)
		{
			line = readline("> ");
			if (!line)
			{
				printf("zbi\n");
				exit(0);
			}
			if (ft_strcmp(line, delimiter) == 0)
			{
				free(line);
				//close(pipefd[1]);
				break ;
				//exit(0);
			}
			// call expand_var
			write(pipefd[1], line, ft_strlen(line));
			write(pipefd[1], "\n", 1);
			free(line);
			// free expand
		}
		exit(0);
		//return 0;
	}
	else
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		signal(SIGINT,SIG_IGN);
		wait(&status); // read issues file
		if (WIFEXITED(status))
			return 0;
		//break;
		//exit(0);
		return 1337;
	}
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	return 0;
	//signal(SIGINT, signal_handler);
}
