#include "../minishell.h"

void	remove_redir_tokens(t_token **head, t_token *redir_token)
{
	t_token	*prev;
	t_token	*curr;
	t_token	*filename_token;
	t_token	*after;

	if (!head || !*head || !redir_token)
		return ;
	prev = NULL;
	curr = *head;
	while (curr && curr != redir_token)
	{
		prev = curr;
		curr = curr->next;
	}
	if (!curr || !curr->next)
		return ;
	filename_token = curr->next;
	after = filename_token->next;
	if (prev)
		prev->next = after;
	else
		*head = after;
	free(curr->token);
	free(curr);
	free(filename_token->token);
	free(filename_token);
}

void	restore_fd(int f_stdout, int f_stdin)
{
	if (f_stdout != -1)
	{
		dup2(f_stdout, STDOUT_FILENO);
		close(f_stdout);
	}
	if (f_stdin != -1)
	{
		dup2(f_stdin, STDIN_FILENO);
		close(f_stdin);
	}
}
