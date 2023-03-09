/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanejar <zanejar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 06:58:25 by zanejar           #+#    #+#             */
/*   Updated: 2023/03/09 08:58:02 by zanejar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void	ft_hardcoding(char *e, char **m)
{
	char	**args;

	args = ft_malloc(3 * sizeof(char *));
	args[0] = "cat";
	args[1] = "/tmp/.ee.txt";
	args[2] = NULL;
	if (execve(e, &args[0], m) < 0)
		exit(error_message(e));
	if (unlink("/tmp/.ee.txt") == -1)
	{
		perror("/tmp/.ee.txt");
	}
	exit(1);
}

int	ft_exeher(t_cmd_list *b)
{
	t_cmd_list	*tm;

	tm = b;
	while (tm)
	{
		if (typelookup(tm) == 1 && !tm->next)
		{
			if (ft_nstrncmp(tm->cdm_line[0], "cat", 3) == 0)
				return (1);
		}
		tm = tm->next;
	}
	return (0);
}

int	children(t_cmd_list *comanda, t_env **envir)
{
	if (!comanda->cdm_line[0])
		exit(1);
	if ((ft_strcmp(comanda->cdm_line[0], "cat") == 0) \
	&& (typelookup(comanda) == 1))
		exit(1);
	if (comanda->in)
		dup2(comanda->in, STDIN_FILENO);
	if (comanda->out != 1)
		dup2(comanda->out, STDOUT_FILENO);
	if (typelookup(comanda) != 0)
	{
		if (is_builtin(comanda) != 0)
			exit(1);
		else if (typelookup(comanda) == 1)
			exit(1);
	}
	else if (execve(path_exec(patharrays(*envir, 0), comanda->cdm_line[0]), \
	&comanda->cdm_line[0], patharrays(*envir, 1)) < 0)
	{
		g_b.exit_status = error_message(path_exec \
		(patharrays(*envir, 0), comanda->cdm_line[0]));
		exit(127);
	}
	return (g_b.exit_status);
}

void	ft_hardcodetb(t_cmd_list *tn, t_env **env)
{
	char	**str;
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (tn->cdm_line[i] != NULL)
		i++;
	str = ft_malloc(sizeof(char *) * (i +1));
	i--;
	while (j < i)
	{
		str[j] = ft_strdup(tn->cdm_line[j]);
		j++;
	}
	str[j] = valuelookup(tn);
	str[++j] = 0;
	if (execve(path_exec(patharrays(*env, 0), \
	tn->cdm_line[0]), &str[0], patharrays(*env, 1)) < 0)
	{
		g_b.exit_status = error_message(path_exec(patharrays(*env, 0), \
		tn->cdm_line[0]));
		exit(1);
	}
}

int	pipehere(t_cmd_list *op, int *fdh)
{
	while (op)
	{
		if (!op->next && typelookup(op) != 1)
			return (0);
		while (op->token)
		{
			if (op->token->e_type == TOKEN_DLREDIRECT)
			{
*fdh = open("/tmp/.ee.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
				if (*fdh == -1)
					perror("open");
				herdocprompt(*fdh, op->token->next->value);
				close(*fdh);
				if (op->token->next->next)
					op->token = op->token->next;
			}
			if (!op->token->next->next)
				break ;
			op->token = op->token->next;
		}
		if (!op->next && ft_exeher(op) == 1)
			return (1);
		op = op->next;
	}
	return (0);
}
