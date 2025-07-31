#include "../minishell.h"

int	redirect_type(t_token *head)
{
	if (!head || !head->token)
		return (0);
	if (head->token[0] == '>')
	{
		if (head->token[1] == '>')
			return (2);
		return (1);
	}
	else if (head->token[0] == '<')
	{
		if (head->token[1] == '<')
			return (4);
		return (3);
	}
	return (0);
}

int	redirect_occur(t_token *redir, char *filename)
{
	int	type;

	if (!redir || !filename)
		return (0);
	type = redirect_type(redir);
	if (type == 1) //>
	{
		outfile_redir(filename);
		return (1);
	}
	else if (type == 2) //>>
	{
		append_redir(filename);
		return (1);
	}
	else if (type == 3) //<
	{
		infile_redir(filename);
		return (1);
	}
	else if (type == 4) //<<
	{
		heredoc_redir(filename);
		return (1);
	}
	return (0);
}

void	infile_redir(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror(filename);
		return ;
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	outfile_redir(char *filename) // input '>'
{
	int fd;

	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(filename);
		return ;
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	append_redir(char *filename) // append ">>"
{
	int fd;

	fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		perror(filename);
		return ;
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}
