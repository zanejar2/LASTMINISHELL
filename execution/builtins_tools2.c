/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_tools2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanejar <zanejar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 06:43:28 by zanejar           #+#    #+#             */
/*   Updated: 2023/03/09 09:15:03 by zanejar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int	exp_hash(char *str, t_env *tenv)
{
	if (!(str) || *str == '#')
	{
		export_o(tenv);
		return (1);
	}
	return (0);
}

void	export_o(t_env	*env)
{
	while (env)
	{
		printf("declare -x %s=\"%s""\"\n", env->var, env->value);
		env = env->next;
	}
}

int	check_dup(t_env	**tenv, char *s)
{
	t_env	*root;
	char	*str;

	root = *tenv;
	str = varexport(s, '=');
	while (root && ft_nstrncmp(root->var, str, ft_strlen(str)))
	{
		root = root->next;
	}
	if (root)
	{
		root->value = ft_search(s, '=');
		return (1);
	}
	return (0);
}

char	*ft_search(char *s, char c)
{
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == c)
		{
			i++;
			return (s + i);
		}
		i++;
	}
	return (ft_strdup(""));
}

void	ft_zid_back(t_env **lst, t_env *ne)
{
	t_env	*l1;

	l1 = *lst;
	if (!lst)
		*lst = ne;
	if (lst != NULL)
	{
		if (*lst == NULL)
			*lst = ne;
		else
		{
			while (l1->next != NULL)
				l1 = l1->next;
			l1->next = ne;
		}
	}
}
