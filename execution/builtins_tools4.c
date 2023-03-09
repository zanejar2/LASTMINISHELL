/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_tools4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanejar <zanejar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 06:42:44 by zanejar           #+#    #+#             */
/*   Updated: 2023/03/09 08:48:41 by zanejar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int	c_syntax(char *var)
{
	int	i;

	i = 0;
	while (var[i])
	{
		if (var[i] == '(' || var[i] == ')' || (var[0] >= '0' && var[0] <= '9'))
		{
			ft_putstr_fd("not an identifier : ", 2);
			ft_putchar_fd(var[i], 2);
			ft_putstr_fd("\n", 2);
			return (0);
		}
		i++;
	}
	return (1);
}

t_env	*ft_lstne(char *var, char *value)
{
	t_env	*htr;

	htr = malloc(sizeof(t_env));
	if (!htr)
		return (NULL);
	htr->var = ft_strdup(var);
	htr->value = ft_strdup(value);
	htr->next = NULL;
	return (htr);
}

char	*varexport(char *str, char c)
{
	int		i;
	char	*var;

	i = 0;
	var = ft_malloc(sizeof(char) * sublen_str(str, c) + 1);
	while (str[i] && str[i] != c)
	{
		var[i] = str[i];
		i++;
	}
	var[i] = '\0';
	return (var);
}

int	sublen_str(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != c && str[i])
		i++;
	return (i);
}

size_t	size_env(t_env *lst)
{
	size_t	lst_len;

	lst_len = 0;
	while (lst && lst->next != NULL)
	{
		if (lst->value != NULL)
		{
			lst_len += ft_strlen(lst->value);
			lst_len++;
		}
		lst = lst->next;
	}
	return (lst_len);
}
