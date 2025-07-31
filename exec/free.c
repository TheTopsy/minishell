#include "../minishell.h"

void	free_args(char **args, int size)
{
	int	i;

	i = 0;
	if (!args)
		return ;
	while (i < size && args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}
