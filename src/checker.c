/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanejar <zanejar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 02:57:03 by zanejar           #+#    #+#             */
/*   Updated: 2023/03/09 07:59:30 by zanejar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void	ft_error(int errno)
{
	if (errno == 5)
		write(2, "Syntax error\n", 14);
	else if (errno == 2)
		write(2, "File opening failure\n", 21);
}

int	pipe_check(char *line)
{
	g_b.i = 0;
	while (line[g_b.i])
	{
		g_b.flag = 0;
		if (line[0] == '|')
			return (0);
		if (line[g_b.i] == '|')
		{	
			g_b.i++;
			if (line[g_b.i] == '\0')
				return (0);
			while (line[g_b.i] && line[g_b.i] != '|')
			{	
				if (ft_isprint(line[g_b.i]) && line[g_b.i] != ' ' && \
				line[g_b.i] != '\t')
					g_b.flag = 1;
				g_b.i++;
			}
			g_b.i--;
			if (g_b.flag == 0)
				return (0);
		}
		g_b.i++;
	}
	return (1);
}

int	redirect_doubles_check(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '<' && line[i + 1] == '>')
			return (0);
		else if (line[i] == '>' && line[i + 1] == '<')
			return (0);
		if ((line[i] == '<' || line[i] == '>') && \
		(line[i + 1] == '<' || line[i + 1] == '>'))
		{	
			if (line[i + 2] == '<' || line[i + 2] == '>')
				return (0);
		}
		i++;
	}
	return (1);
}

int	quotes_check(char *line, int i, int d, int s)
{
	while (line[i])
	{
		if (line[i] == '"')
		{	
			d++;
			i++;
			while (line[i] && line[i] != '"')
				i++;
			if (line[i])
				d++;
		}
		else if (line[i] == '\'')
		{	
			s++;
			i++;
			while (line[i] && line[i] != '\'')
				i++;
			if (line[i])
				s++;
		}
		i++;
	}
	if (d % 2 != 0 || s % 2 != 0)
		return (0);
	return (1);
}

int	line_errors_checker(char *line)
{
	if (ft_strcmp(line, "") == 0)
		return (0);
	if (vars_init(line) == 0)
	{	
		ft_error(SYNTAX_ERROR);
		return (0);
	}
	if (redirect_doubles_check(line) == 0)
	{	
		ft_error(SYNTAX_ERROR);
		return (0);
	}
	if (pipe_check(line) == 0)
	{
		ft_error(SYNTAX_ERROR);
		return (0);
	}
	return (1);
}
