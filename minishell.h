#ifndef MINISHELL_H
# define MINISHELL_H

#include <limits.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdarg.h>
# include <signal.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include <sys/wait.h>//for wait()
# include "./exec/libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

//extern int	g_status;

# define RED "\033[1;31m"
# define CYAN "\033[1;36m"
# define RESET "\033[0m"

typedef struct s_token
{
	char	*token;//the actual text "echo" "<" ..
	char	*label;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

int lst_len(t_token *head);
t_token	*lst_new (const char *text);
t_token	*lst_last(t_token *lst);
int		check_nl(t_token *head);
int		check_overflow(char *str);

void	restore_fd(int f_stdout, int f_stdin);
int		redirect_type(t_token *head);
int		count_redirect(t_token *head);
t_token	*check_redirect(t_token *head);
int		redirect_occur(t_token *redir, char *s);

void	remove_redir_tokens(t_token **head, t_token *redir_token);
void	outfile_redir(char *filename);
void	heredoc_redir(char *delimiter);
void	infile_redir(char *filename);
void	append_redir(char *filename);
void	execute_redir(t_token **head);

int		token_len(t_token *head);
void	check_command(t_token *head);
int		unclosed_quotes(char *input);

t_token *split_input(char *input);

void	echo(t_token *head);
void	pwd(t_token *head);
void	cd(t_token *head);
void	ft_exit(t_token *head);

void	start_signals(void);
void	signal_handler(int sig);

void	free_array(char **array);
char	*ft_readline(void);
void	free_args(char **args, int size);

#endif
