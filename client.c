/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melperri <melperri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 11:02:54 by melperri          #+#    #+#             */
/*   Updated: 2021/10/21 18:03:43 by melperri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static void	ft_send_signal(pid_t pid, int sig)
{
	kill(pid, sig);
	usleep(20);
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

int	main(int ac, char **av)
{
	pid_t	server;
	pid_t	client;
	int		i;

	if (ac != 3)
		exit(1);
	server = ft_atoi(av[1]);
	client = getpid();
	i = -1;
	while (av[2][++i])
		ft_send_signal(server, SIGUSR1);
	ft_send_signal(server, SIGUSR2);
	i = -1;
	while (av[2][++i])
		ft_pars_char(server, av[2][i]);
	ft_send_signal(server, SIGUSR1);
	return (0);
}
