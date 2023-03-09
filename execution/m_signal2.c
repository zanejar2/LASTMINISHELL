/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_signal2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanejar <zanejar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 06:44:36 by zanejar           #+#    #+#             */
/*   Updated: 2023/03/09 06:53:49 by zanejar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void	signals(void)
{
	if (signal(SIGINT, SIG_IGN) == SIG_ERR)
		exit(1);
	if (signal(SIGQUIT, sig_handl) == SIG_ERR)
		exit(1);
}

void	signals2(void)
{
	if (signal(SIGINT, sig_handle) == SIG_ERR)
		exit(1);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		exit(1);
}

void	heredoc_signal(void)
{
	if (signal(SIGINT, ctrl_handler) == SIG_ERR)
		exit(1);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		exit(1);
}

void	signals3(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	signals4(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
