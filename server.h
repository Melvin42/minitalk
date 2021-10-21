/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melperri <melperri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 15:41:31 by melperri          #+#    #+#             */
/*   Updated: 2021/10/21 15:45:50 by melperri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdbool.h>
# define LEN 0
# define INDEX 1
# define I 2
# define FLAG 3

static char	*g_str = NULL;

int		ft_strlen(char *str);
int		ft_itoa_len(int n);
char	*ft_itoa(int n);

#endif
