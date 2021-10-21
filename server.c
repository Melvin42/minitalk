/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melperri <melperri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 11:04:48 by melperri          #+#    #+#             */
/*   Updated: 2021/10/21 15:44:17 by melperri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static void	ft_realloc(int len)
{
	if (g_str)
	{
		free(g_str);
		g_str = NULL;
	}
	g_str = malloc(sizeof(wchar_t) * (len + 1));
	if (g_str == NULL)
	{
		free(g_str);
		exit(1);
	}
}

static void	ft_send_message(int tab[4], char *c)
{
	write (1, &(*g_str), ft_strlen(g_str));
	*c = 0;
	tab[I] = 0;
	tab[LEN] = 0;
	tab[INDEX] = 0;
	tab[FLAG] = 0;
	if (g_str)
	{
		free(g_str);
		g_str = NULL;
	}
}

static void	handler(int signum)
{
	static int	tab[4] = {0};
	static char	c = 0;

	if (signum == SIGUSR1 && tab[FLAG] == 0)
		tab[LEN]++;
	else if (signum == SIGUSR2 && tab[FLAG] == 0)
	{
		tab[FLAG] = 1;
		return (ft_realloc(tab[LEN]));
	}
	if (signum == SIGUSR1 && tab[FLAG] == 1 && tab[INDEX] < tab[LEN])
		c |= 1 << tab[I]++;
	else if (signum == SIGUSR2 && tab[FLAG] == 1 && tab[LEN] > 0)
		tab[I]++;
	if (tab[I] == 8 && tab[FLAG] == 1 && tab[INDEX] < tab[LEN])
	{
		g_str[tab[INDEX]] = c;
		tab[INDEX]++;
		c = 0;
		tab[I] = 0;
	}
	if (signum == SIGUSR1 && tab[FLAG] == 1 && tab[INDEX] == tab[LEN])
		ft_send_message(tab, &c);
}

int	main(void)
{
	struct sigaction	action;
	char				*pid;

	action.sa_handler = handler;
	sigemptyset(&action.sa_mask);
	action.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &action, NULL) == -1)
		return (write(2, "Error\n", 6));
	if (sigaction(SIGUSR2, &action, NULL) == -1)
		return (write(2, "Error\n", 6));
	write(1, "My PID : ", 9);
	pid = ft_itoa(getpid());
	write(1, &(*pid), ft_strlen(pid));
	write(1, "\n", 1);
	while (1)
		;
	free(g_str);
	g_str = NULL;
	return (0);
}
