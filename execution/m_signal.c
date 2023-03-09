/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_signal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanejar <zanejar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 06:44:48 by zanejar           #+#    #+#             */
/*   Updated: 2023/03/09 09:07:55 by zanejar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void	ctrl_handler(int sig)
{
	sig = 1;
	exit(1);
}

void	sig_handl(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	rl_on_new_line();
	write(1, "Quit: 3", 7);
	write(1, "\n", 1);
}

void	sig_handle(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	rl_on_new_line();
	write(1, "\n", 1);
	rl_redisplay();
}

void	exit_handle(int exits)
{
	ft_putendl_fd("exit", 1);
	exit(exits);
}
