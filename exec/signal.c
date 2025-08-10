#include "../minishell.h"

 void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
	//	g_status = SIGINT;
		rl_on_new_line();
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig == SIGQUIT)
	{
	//	g_status = SIGQUIT;
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	start_signals(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}
