/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanejar <zanejar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 06:44:20 by zanejar           #+#    #+#             */
/*   Updated: 2023/03/09 06:53:33 by zanejar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void	herdocprompt(int fd, char *limit)
{
	char	*ptr;

	while (1)
	{
		ptr = readline(">");
		if (!ptr)
			break ;
		if (!ft_nstrncmp(limit, ptr, ft_strlen(limit) + 1))
			break ;
		write(fd, ptr, ft_strlen(ptr));
		write(fd, "\n", 1);
		free(ptr);
	}
}

int	heredoc(char *limiter)
{
	int		fd[2];
	int		pid;
	int		status;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		heredoc_signal();
		close (fd[0]);
		herdocprompt(fd[1], limiter);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (status);
	close(fd[1]);
	return (fd[0]);
}
