/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nopipe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanejar <zanejar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 06:46:41 by zanejar           #+#    #+#             */
/*   Updated: 2023/03/09 06:56:19 by zanejar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

char	*find_path(t_env *envt)
{
	while (envt)
	{
		if (!ft_nstrncmp(envt->var, "PATH", 5))
			return (envt->value);
		envt = envt->next;
	}
	return (NULL);
}

char	*env_to_str(t_env *lst)
{
	char	*env;
	int		i;
	int		j;

	env = ft_malloc(sizeof(char) * size_env(lst) + 1);
	i = 0;
	while (lst && lst->next != NULL)
	{
		if (lst->value != NULL)
		{
			j = 0;
			while (lst->value[j])
			{
				env[i] = lst->value[j];
				i++;
				j++;
			}
		}
		if (lst->next->next != NULL)
			env[i++] = '\n';
		lst = lst->next;
	}
	env[i] = '\0';
	return (env);
}

int	error_message(char *path)
{
	DIR	*folder;
	int	fd;

	fd = open(path, O_WRONLY);
	folder = opendir(path);
	ft_putstr_fd("minishell: ", STDERR);
	ft_putstr_fd(path, STDERR);
	if (ft_search(path, '/') == NULL)
		ft_putendl_fd(": command not found", STDERR);
	else if (fd == -1 && folder == NULL)
		ft_putendl_fd(": No such file or directory", STDERR);
	else if (fd == -1 && folder != NULL)
		ft_putendl_fd(": is a directory", STDERR);
	else if (fd != -1 && folder == NULL)
		ft_putendl_fd(": Permission denied", STDERR);
	if (ft_search(path, '/') == NULL || (fd == -1 && folder == NULL))
		g_b.exit_status = 127;
	else
		g_b.exit_status = 126;
	if (folder)
		closedir(folder);
	ft_close(fd);
	return (g_b.exit_status);
}

void	ft_close(int fd)
{
	if (fd > 0)
		close(fd);
}

char	*path_exec(char **str, char *cmd)
{
	char	*path_exe;
	char	*tmp;
	int		i;

	if (!cmd || !cmd[0])
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	if (!str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		path_exe = ft_strjoin(str[i], "/");
		tmp = path_exe;
		path_exe = ft_strjoin(path_exe, cmd);
		if (access(path_exe, X_OK) != -1)
			return (path_exe);
		i++;
	}
	return (NULL);
}
