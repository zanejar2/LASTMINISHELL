/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanejar <zanejar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 06:57:45 by zanejar           #+#    #+#             */
/*   Updated: 2023/03/09 07:09:07 by zanejar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

char	*valuehredoclookup(t_cmd_list *cmdp)
{
	t_cmd_list	*tmp;

	tmp = cmdp;
	while (tmp->token)
	{
		if (tmp->token->e_type == TOKEN_DLREDIRECT)
			return (ft_strdup(tmp->token->next->value));
		tmp->token = tmp->token->next;
	}
	return (NULL);
}

char	*valuelookup(t_cmd_list *cmdp)
{
	t_cmd_list	*tmp;

	tmp = cmdp;
	while (tmp->token)
	{
		if (tmp->token->e_type == TOKEN_DRREDIRECT)
			return (ft_strdup(tmp->token->next->value));
		else if (tmp->token->e_type == TOKEN_RREDIRECT)
			return (ft_strdup(tmp->token->next->value));
		tmp->token = tmp->token->next;
	}
	return (NULL);
}

char	**patharrays(t_env *env, int a)
{
	char	*ptr;
	char	*exe;
	char	**sp;
	char	**shit;

	ptr = env_to_str(env);
	sp = ft_split(ptr, '\n');
	exe = ft_strdup(find_path(env));
	if (!exe)
		return (0);
	if (a == 1)
		return (sp);
	shit = ft_split(exe, ':');
	return (shit);
}

void	handle_pipe(t_cmd_list *cmd_list, int pipefds[], int j)
{
	if (cmd_list->next)
	{
		if (dup2(pipefds[j + 1], 1) < STDOUT_FILENO)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
	}
	if (j != 0)
	{
		if (dup2(pipefds[j - 2], 0) < STDIN_FILENO)
		{
			perror(" dup2");
			exit(EXIT_FAILURE);
		}
	}
}

void	close_unused_pipes(int pipefds[], int numPipes)
{
	int	i;

	i = 0;
	while (i < 2 * numPipes)
	{
		close(pipefds[i]);
		i++;
	}
}
