/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmellal <nmellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 00:16:38 by nmellal           #+#    #+#             */
/*   Updated: 2024/04/25 20:27:45 by nmellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "ft_libft/libft.h"
# include "ft_printf/ft_printf.h"
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>

typedef pid_t	t_pid;

void			message_sender(pid_t pid, char *msg);
void			check_pid(pid_t pid);
void			arg_check(int ac, char **av);
void			signal_handler(int signum);
void			sig_conf(void);
void			signal_handler2(int signum, siginfo_t *info, void *context);
void			sig_conf2(void);
void			error_exit(char *msg);

#endif