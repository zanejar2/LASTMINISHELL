/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_tools3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanejar <zanejar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 06:41:43 by zanejar           #+#    #+#             */
/*   Updated: 2023/03/09 08:24:01 by zanejar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int	ft_checkdigit(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-')
		i = 1;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) || i >= 19)
			return (0);
		i++;
	}
	return (1);
}

void	m_display_env(t_env *list)
{
	if (!list)
		return ;
	while (list)
	{
		printf("%s=\"%s""\"\n", list->var, list->value);
		list = list->next;
	}
}

void	m_export(t_env	**envt, char **str)
{
	int		i;
	char	*newvar;
	char	*check;

	i = -1;
	if (exp_hash(*str, *envt))
		return ;
	while (str[++i])
	{	
		newvar = varexport(str[i], '=');
		check = ft_search(str[i], '=');
		if (!check)
		{
			free(newvar);
			return ;
		}
		if (!c_syntax(newvar))
		{
			free(newvar);
			continue ;
		}
		if (!check_dup(envt, str[i]))
			ft_zid_back(envt, ft_lstne(newvar, check));
		free(newvar);
	}
}

void	m_unset(char **str, t_env	**envt)
{
	int	i;

	i = 0;
	if (!str[i])
	{
		printf("unset: not enough arguments\n");
		return ;
	}
	i = -1;
	while (str[++i])
	{
		if (!c_syntax(str[i]))
			continue ;
		unsetvar(str[i], envt);
	}
}

void	unsetvar(char *str, t_env **envt)
{
	t_env	*head;
	t_env	*prev;

	head = *envt;
	g_b.i = 0;
	while (head)
	{
		if (!ft_nstrncmp(str, head->var, ft_strlen(str) + 1))
		{
			if (g_b.i == 0)
			{
				*envt = head->next;
				if (!head->value)
					head->value = ft_strdup("");
				return ;
			}
			prev->next = head->next;
			if (!head->value)
				head->value = ft_strdup("");
			return ;
		}
		prev = head;
		head = head->next;
		g_b.i++;
	}
}
