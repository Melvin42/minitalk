/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melperri <melperri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 11:04:48 by melperri          #+#    #+#             */
/*   Updated: 2021/07/09 15:57:44 by melperri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _POSIX_C_SOURCE 199309L
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdbool.h>

int		g_i = 0;
int		g_index = 0;
int		g_len = 0;
char	g_c = 0;
char	*g_str = NULL;
bool	g_flag = 0;

static int	ft_strlen(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		;
	return (i);
}

static void	ft_realloc(void)
{
	if (g_str)
	{
		free(g_str);
		g_str = NULL;
	}
	g_str = malloc(sizeof(char) * (g_len + 1));
	if (g_str == NULL)
	{
		free(g_str);
		exit(1);
	}
}

static void	handler(int signum)
{
	if (signum == SIGUSR1 && g_flag == 0)
		g_len++;
	else if (signum == SIGUSR2 && g_flag == 0)
	{
		g_flag = 1;
		ft_realloc();
		return ;
	}
	if (signum == SIGUSR1 && g_flag == 1 && g_len > 0)
	{
		g_c |= 1 << g_i;
		g_i++;
	}
	else if (signum == SIGUSR2 && g_flag == 1 && g_len > 0)
		g_i++;
	if (g_i == 8 && g_flag == 1 && g_len > 0)
	{
		g_str[g_index] = g_c;
		g_index++;;
		g_len--;
		g_c = 0;
		g_i = 0;
	}
	if (signum == SIGUSR1 && g_flag == 1 && g_len == 0)
	{
		write (1, &(*g_str), ft_strlen(g_str));
		write(1, "\nMESSAGE BIEN RECU!!!\n", 22);
		g_c = 0;
		g_i = 0;
		g_index = 0;
		g_flag = 0;
		g_len = 0;
		if (g_str)
		{
			free(g_str);
			g_str = NULL;
		}
	}
}

/*
**	how to check the 8 bits of one char
**	int	k = -1;
**	while (++k < 8)
**	{
**		if (c & (1u << k))
**			printf("bit %d == 1\n", k);
**		else
**			printf("bit %d == 0\n", k);
**	}
*/

int main(void)
{
	struct sigaction action;

	action.sa_handler = handler;
	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;
	if (sigaction(SIGUSR1, &action, NULL) == -1)
		;
	if (sigaction(SIGUSR2, &action, NULL) == -1)
		;
	printf("Pret a recevoir des signaux. Mon PID : %d\n", getpid());
	while (1)
		;
	free(g_str);
	g_str = NULL;
	return (0);
}
