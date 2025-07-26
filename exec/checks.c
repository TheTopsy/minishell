#include "../minishell.h"
/*
int check_overflow(char *str)
{
	int num = ft_atoi(str);
	if (nums == NULL)
		return 1;
	return 0;
}
*/

int	check_overflow(char *str)
{
	int					i;
	int					sign;
	unsigned long long	num;
	unsigned long long	limit;

	i = 0;
	sign = 1;
	num = 0;
	if (!str || str[0] == '\0')
		return (0);
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (str[i] == '\0')
		return (0);
	if (sign == -1)
		limit = (unsigned long long)LLONG_MAX + 1;
	else
		limit = LLONG_MAX;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		if (num > (limit - (str[i] - '0')) / 10)
			return (0);
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return (1);
}

t_token	*check_redirect(t_token *head)
{
	while (head)
	{
		if (redirect_type(head) > 0)
		{
			return (head);
		}
		head = head->next;
	}
	return (NULL);
}

int	count_redirect(t_token *head)
{
	int	i;

	i = 0;
	while (head)
	{
		if (head->token[0] == '>')
			i++;
		head = head->next;
	}
	return (i);
}

int	check_nl(t_token *head) // handle "echo -n -n bby"
{
	int j;
	int i;

	i = 0;
	while (head)
	{
		if (!head->token || head->token[0] != '-')
			break ;
		j = 1;
		while (head->token[j] && head->token[j] == 'n')
			j++;
		if (head->token[j] || j == 1)
			break ;
		i++;
		head = head->next;
	}
	return (i);
}
