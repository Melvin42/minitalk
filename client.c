/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melperri <melperri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 11:02:54 by melperri          #+#    #+#             */
/*   Updated: 2021/07/06 22:00:53 by melperri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _POSIX_SOURCE
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

static void	ft_send_signal(pid_t pid, int sig)
{
	kill(pid, sig);
	usleep(21);
}

static void	ft_pars_char(pid_t pid, char c)
{
	int	i;

	i = -1;
	while (++i < 8)
	{
		if (c & 1)
			ft_send_signal(pid, SIGUSR1);
		else
			ft_send_signal(pid, SIGUSR2);
		c >>= 1;
	}
}

int main(int ac, char **av)
{
	pid_t	server;
	char	*str;
	int		i;

	if (ac != 3)
		exit(1);
	server = atoi(av[1]);
	str = av[2];
	i = -1;
	while (str[++i])
		ft_send_signal(server, SIGUSR1);
	ft_send_signal(server, SIGUSR2);
	i = -1;
	while (str[++i]) 
		ft_pars_char(server, str[i]);
	ft_send_signal(server, SIGUSR1);
	return (0);
}
