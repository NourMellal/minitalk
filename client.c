/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmellal <nmellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 00:17:07 by nmellal           #+#    #+#             */
/*   Updated: 2024/04/25 20:51:04 by nmellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	message_sender(pid_t pid, char *msg)
{
	unsigned char	c;
	int				bits_remaining;

	while (*msg)
	{
		c = *msg;
		bits_remaining = 8;
		while (bits_remaining--)
		{
			if (c & 0b10000000)
			{
				if (kill(pid, SIGUSR1) == -1)
					error_exit("kill failed");
			}
			else
			{
				if (kill(pid, SIGUSR2) == -1)
					error_exit("kill failed");
			}
			usleep(1500);
			c <<= 1;
		}
		msg++;
	}
}

void	arg_check(int ac, char **av)
{
	int	i;

	i = 0;
	if (ac != 3)
		error_exit("Bad arguments\n");
	while (av[1][i])
	{
		if (!ft_isdigit(av[1][i]))
			error_exit("Invalid pid\n");
		i++;
	}
	if (*av[2] == '\0')
		ft_printf("Empty string\n");
	if (kill(ft_atoi(av[1]), 0) == -1)
		error_exit("Invalid pid\n");
}

void	signal_handler(int signum)
{
	if (signum == SIGUSR2)
		write(1, "char received\n", 15);
}

void	sig_conf(void)
{
	struct sigaction	sa;

	sa.sa_handler = &signal_handler;
	sa.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		error_exit("sigaction failed");
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
		error_exit("sigaction failed");
}

int	main(int ac, char **av)
{
	pid_t	pid;

	arg_check(ac, av);
	pid = ft_atoi(av[1]);
	sig_conf();
	message_sender(pid, av[2]);
	while (1)
		sleep(5);
	return (0);
}
