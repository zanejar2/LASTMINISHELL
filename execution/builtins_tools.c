/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanejar <zanejar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 06:41:18 by zanejar           #+#    #+#             */
/*   Updated: 2023/03/09 08:47:24 by zanejar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void	m_echo(char **s)
{
	int	i;
	int	nl;

	i = 0;
	nl = 0;
	if (!(*s))
		ft_putchar_fd('\n', 1);
	else
	{
		if (!ft_nstrncmp(s[i], "-n", 3))
		{
			nl = 1;
			i++;
		}
		while (s[i] != NULL)
		{
			ft_putstr_fd(s[i], 1);
			if (s[i + 1] != NULL)
				ft_putchar_fd(' ', 1);
			i++;
		}
		if (!nl)
			ft_putchar_fd('\n', 1);
	}
}

void	m_cd(const char *dirr)
{
	if (!dirr)
	{
		if (!getenv("HOME"))
		{
			printf("Environment not found\n");
			return ;
		}
		chdir(getenv("HOME"));
		return ;
	}
	if (!chdir(dirr))
		return ;
	printf("%s : is not directory\n", dirr);
}

void	m_pwd(void)
{
	char	path [1024];

	if (getcwd(path, sizeof(path)) == NULL)
		return ;
	ft_putstr_fd(getcwd(path, sizeof(path)), 1);
	ft_putchar_fd('\n', 1);
}

void	m_exit(char **str)
{
	ft_putstr_fd("exit ", STDERR);
	if (!str[1])
	{
		ft_putendl_fd("💚", STDERR);
		exit(0);
	}
	if (str[1] && str[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", STDERR);
	}
	else if (str[1] && !ft_checkdigit(str[1]))
	{
		ft_putstr_fd("minishell: exit: ", STDERR);
		ft_putstr_fd(str[1], STDERR);
		ft_putendl_fd(": numeric argument required", STDERR);
		g_b.exit_status = 255;
		exit(255);
	}
	else
	{
		ft_putstr_fd(str[1], STDERR);
		g_b.exit_status = ft_atoi(str[1]);
		exit(ft_atoi(str[1]));
	}
}
