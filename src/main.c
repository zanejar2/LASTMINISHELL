/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanejar <zanejar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 02:58:00 by zanejar           #+#    #+#             */
/*   Updated: 2023/03/09 09:06:20 by zanejar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int	main(int ac, char **av, char **env)
{
	char		*line;
	t_env		*env_cpy;

	(void)ac;
	(void)av;
	env_cpy = env_cpy_maker(env);
	while (1)
	{
		signals2();
		line = display_prompt();
		if (line_errors_checker(line) == 0)
		{
			free(line);
			continue ;
		}
		minishel(line, env_cpy);
	}
	exit(0);
}
