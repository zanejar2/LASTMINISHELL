/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanejar <zanejar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 07:36:22 by zanejar           #+#    #+#             */
/*   Updated: 2023/03/09 07:46:23 by zanejar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int	export_norm(t_token *token)
{
	if (ft_strcmp(token->value, "export") == 0 \
	&& token->next && token->next->next \
	&& token->next->next->e_type == 2 \
	&& quotes_finder(token->next->value))
		return (1);
	return (0);
}

char	*expand_exit_status(char *var)
{
	var = ft_itoa(g_b.exit_status);
	return (var);
}

void	*ft_malloc(int size)
{
	void	*ptr;

	ptr = malloc (size);
	g_b.g_c[g_b.index] = ptr;
	g_b.index++;
	return (ptr);
}

char	*var_exp_suit(char *var, t_env *env)
{
	while (env)
	{
		if (ft_strcmp(env->var, var) == 0)
		{
			var = env->value;
			return (var);
		}
		env = env->next;
	}
	return (ft_strdup(""));
}

int	quotes_finder(char *str)
{
	int	i;

	i = 0;
	while (str[i + 1])
		i++;
	if (str[i] == '=')
		return (1);
	return (0);
}
