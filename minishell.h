#ifndef MINISHELL_H
#define MINISHELL_H

#include "./libft/libft.h"
#include <stdio.h>
#include <stdarg.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_token
{
	char *token;
	char *label;
	struct s_token *next;
	struct s_token *prev;
} t_token;

t_token *lst_new (const char *text);
t_token  *lst_last(t_token *lst);
t_token *check_redirect(t_token *head);
int count_redirect(t_token *head);
int check_nl(t_token *head);
void echo_file(t_token *head, char *s);
void echo(t_token *head);
#endif
