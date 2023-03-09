/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanejar <zanejar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 06:59:01 by zanejar           #+#    #+#             */
/*   Updated: 2023/03/09 08:56:43 by zanejar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int	ft_lencmd(char **ss)
{
	int	i;

	i = 0;
	while (ss[i] != NULL)
	{
		i++;
	}
	return (i);
}

char	*ftpiperr(t_cmd_list *oo)
{
	t_cmd_list	*tmp;

	tmp = oo;
	while (tmp && tmp->next)
	{
		tmp = tmp->next;
	}
	if (!tmp->cdm_line[0])
		return (NULL);
	else
		return (tmp->cdm_line[0]);
	return (NULL);
}

void	herdocchild(t_cmd_list *lli, t_env **eo)
{
	t_cmd_list	*ll;
	char		*ar;

	ll = lli;
	signals4();
	ar = ftpiperr(ll);
	if (pipehere(ll, &g_b.tmp_fd) == 1 && ar != NULL)
	{
		ft_hardcoding(path_exec(patharrays(*eo, 0), ar), patharrays(*eo, 1));
		exit(1);
	}
	else if (ft_strcmp(ar, "cat") == 0)
		exit(1);
	else if (is_builtin(lli) == 1)
	{
		exebultin(lli, eo);
		exit(1);
	}
	else if (execve(path_exec(patharrays(*eo, 0), ll->cdm_line[0]), \
	&ll->cdm_line[0], patharrays(*eo, 1)) < 0)
	{
		g_b.exit_status = error_message(path_exec(patharrays(*eo, 0), \
		ll->cdm_line[0]));
		exit(1);
	}
}

int	checkforher(t_cmd_list *lli, t_env **eo)
{
	t_cmd_list	*tor;
	pid_t		pid;
	int			status;

	tor = lli;
	if (typelookup(lli) == 1)
	{
		pid = fork();
		if (pid == 0)
			herdocchild(tor, eo);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_b.exit_status = WEXITSTATUS(status);
	}
	else if (llo(lli) == 3 || llo(lli) == 4 || llo(lli) == 2)
	{
		if (lli->in)
			dup2(lli->in, STDIN_FILENO);
	}
	return (0);
}

int	execute_commands_with_pipes(t_cmd_list *cmd_list, t_env **env)
{
	int	numpipes;
	int	j;
	int	*pipefds;

	j = 0;
	numpipes = countpipes(cmd_list) - 1;
	pipefds = ft_malloc(2 * numpipes);
	create_pipes(cmd_list, env, pipefds, numpipes);
	while (cmd_list)
	{
		g_b.pid = fork();
		if (g_b.pid == 0)
		{
			signals4();
			handle_pipe(cmd_list, pipefds, j);
			close_unused_pipes(pipefds, numpipes);
			return (children(cmd_list, env));
		}
		signals();
		cmd_list = cmd_list->next;
		j += 2;
	}
	close_pipes(pipefds, numpipes);
	wait_all_children(numpipes);
	return (g_b.exit_status);
}
