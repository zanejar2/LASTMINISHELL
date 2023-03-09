/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanejar <zanejar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 06:57:09 by zanejar           #+#    #+#             */
/*   Updated: 2023/03/09 08:03:23 by zanejar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void	m_execution(t_cmd_list *list, t_env **env)
{
	if (!list->next && list->cdm_line[0] != '\0')
	{
		if (is_builtin(list) != 0 && typelookup(list) == 0)
			exebultin(list, env);
		else
			execute_commands_with_pipes(list, env);
	}
	else
		execute_commands_with_pipes(list, env);
}

int	countpipes(t_cmd_list *list)
{
	int	i;

	i = 1;
	while (list)
	{
		i++;
		list = list->next;
	}
	return (i);
}

void	fttobi(t_cmd_list *cc)
{
	t_cmd_list	*tmp;

	tmp = cc;
	while (tmp->token)
	{
		if (tmp->token->e_type == TOKEN_DLREDIRECT)
		{
		cc->in = heredoc(tmp->token->next->value);
			if (tmp->token->next->next)
				tmp->token = tmp->token->next;
		}
		if (!tmp->token->next->next)
			return ;
		tmp->token = tmp->token->next;
	}
}

int	typelookup(t_cmd_list *cmde)
{
	t_cmd_list	*cmdd;
	int			i;

	i = 0;
	cmdd = cmde;
	while (cmdd)
	{
		while (cmdd->token)
		{
			if (cmdd->token->e_type == TOKEN_DLREDIRECT)
				return (1);
			else if (cmdd->token->e_type == TOKEN_DRREDIRECT)
				i = 2;
			else if (cmdd->token->e_type == TOKEN_LREDIRECT)
				i = 3;
			else if (cmdd->token->e_type == TOKEN_RREDIRECT)
				i = 4;
			cmdd->token = cmdd->token->next;
		}
		cmdd = cmdd->next;
	}
	return (i);
}

int	llo(t_cmd_list *llo)
{
	int	i;

	i = 0;
	while (llo->token)
	{
		if (llo->token->e_type == TOKEN_DRREDIRECT)
			i = 2;
		else if (llo->token->e_type == TOKEN_LREDIRECT)
			i = 3;
		else if (llo->token->e_type == TOKEN_RREDIRECT)
			i = 4;
		llo->token = llo->token->next;
	}
	return (i);
}
