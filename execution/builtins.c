/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanejar <zanejar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 06:44:15 by zanejar           #+#    #+#             */
/*   Updated: 2023/03/09 06:53:00 by zanejar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int	is_builtin(t_cmd_list *str)
{
	if (!str->cdm_line[0])
		return (-1);
	else if (!ft_strcmp(str->cdm_line[0], "echo"))
		return (3);
	else if (!ft_strcmp(str->cdm_line[0], "unset"))
		return (2);
	else if (!ft_strcmp(str->cdm_line[0], "pwd"))
		return (1);
	else if (!ft_strcmp(str->cdm_line[0], "exit"))
		return (2);
	else if (!ft_strcmp(str->cdm_line[0], "export"))
		return (1);
	else if (!ft_strcmp(str->cdm_line[0], "env"))
		return (1);
	else if (!ft_strcmp(str->cdm_line[0], "cd"))
		return (1);
	return (0);
}

void	exebultin(t_cmd_list *cmd, t_env **envi)
{
	if (!ft_strcmp(cmd->cdm_line[0], "echo"))
		m_echo(&cmd->cdm_line[1]);
	else if (!ft_strcmp(cmd->cdm_line[0], "pwd"))
		m_pwd();
	else if (!ft_strcmp(cmd->cdm_line[0], "unset"))
		m_unset(&cmd->cdm_line[1], envi);
	else if (!ft_strcmp(cmd->cdm_line[0], "exit"))
		m_exit(&cmd->cdm_line[0]);
	else if (!ft_strcmp(cmd->cdm_line[0], "export"))
		m_export(envi, &cmd->cdm_line[1]);
	else if (!ft_strcmp(cmd->cdm_line[0], "env"))
		m_display_env(*envi);
	else if (!ft_strcmp(cmd->cdm_line[0], "cd") && \
	(cmd->cdm_line[1] == NULL || cmd->cdm_line[2] == NULL))
		m_cd(cmd->cdm_line[1]);
	else if (!ft_strcmp(cmd->cdm_line[0], "cd") && \
	(cmd->cdm_line[1] != NULL || cmd->cdm_line[2] == NULL))
		m_cd(cmd->cdm_line[1]);
	else
		printf("too many arguments\n");
}
