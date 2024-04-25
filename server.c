/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmellal <nmellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 17:21:04 by nmellal           #+#    #+#             */
/*   Updated: 2024/04/25 20:43:12 by nmellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	signal_handler2(int signum, siginfo_t *info, void *context)
{
	static unsigned char	c;
	static int				bits_remaining = -1;

	(void)context;
	if (bits_remaining < 0)
		bits_remaining = 7;
	if (signum == SIGUSR1)
		c |= (1 << bits_remaining);
	bits_remaining--;
	if (bits_remaining < 0 && c)
	{
		write(1, &c, 1);
		c = 0;
		if (kill(info->si_pid, SIGUSR2) == -1)
			error_exit("kill failed");
		return ;
	}
	if (kill(info->si_pid, SIGUSR1) == -1)
		error_exit("kill failed");
}

void	sig_conf2(void)
{
	struct sigaction	act;

	act.sa_sigaction = &signal_handler2;
	act.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &act, NULL) == -1)
		ft_printf("Error: sigaction failed\n");
	if (sigaction(SIGUSR2, &act, NULL) == -1)
		ft_printf("Error: sigaction failed\n");
}

int	main(void)
{
	t_pid	pid;

	pid = getpid();
	ft_printf("Server PID: %d\n", pid);
	sig_conf2();
	while (1)
		;
	return (0);
}
