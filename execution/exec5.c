/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanejar <zanejar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 06:59:34 by zanejar           #+#    #+#             */
/*   Updated: 2023/03/09 08:01:23 by zanejar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void	close_pipes(int pipefds[], int numPipes)
{
	int	i;

	i = 0;
	while (i < 2 * numPipes)
	{
		close(pipefds[i]);
		i++;
	}
}

void	wait_all_children(int numChildren)
{
	int	i;
	int	status;

	i = 0;
	while (i < numChildren)
	{
		wait(&status);
		if (WIFEXITED(status))
			g_b.exit_status = WEXITSTATUS(status);
		i++;
	}
}

void	create_pipes(t_cmd_list *tt, t_env **en, int pipefds[], int numPipes)
{
	int	i;

	i = 0;
	while (i < numPipes)
	{
		if (pipe(pipefds + i * 2) < 0)
		{
			perror("couldn't pipe");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	if (checkforher(tt, en) != 0)
		return ;
}

char	*display_prompt(void)
{
	char	*line;

	line = readline(SHELL);
	if (!line)
	{
		printf("exit\n");
		exit(0);
	}
	add_history(line);
	return (line);
}

void	minishel(char *line, t_env *cpy)
{
	t_cmd_list	*list;
	t_lexer		*lexer;

	lexer = lexer_init(line);
	list = ft_tokenizer(lexer);
	if (token_error_check(list) == 0)
		return ;
	list = redirect_retyper(list);
	list = ft_retokenizer(list);
	list = redirect_list_init(list);
	files_opener(list);
	tokens_num(list);
	expand_variables(list, cpy);
	cmd_line_maker(list);
	m_execution(list, &cpy);
}
