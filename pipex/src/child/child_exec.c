/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyanagis <kyanagis@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 04:10:00 by kyanagis          #+#    #+#             */
/*   Updated: 2025/09/01 03:46:11 by kyanagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "child.h"

static bool	has_slash(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (false);
	while (s[i])
	{
		if (s[i] == '/')
			return (true);
		i++;
	}
	return (false);
}

static char	*resolve_cmd(const char *cmd, char **pathv)
{
	int		i;
	char	*full;

	i = 0;
	if (!cmd || !*cmd || !pathv)
		return (NULL);
	while (pathv[i])
	{
		if (pathv[i][0] != '\0')
		{
			full = join3(pathv[i], "/", cmd);
			if (!full)
				perror_exit(ERR_MALLOC, EXIT_FAILURE);
			if (access(full, X_OK) == 0)
				return (full);
			free(full);
		}
		i++;
	}
	return (NULL);
}

static void	exec_direct(t_pipex *data, char **args)
{
	int	exist;
	int	execable;

	exist = access(args[0], F_OK);
	if (exist != 0)
	{
		perror(args[0]);
		free_double_array(args);
		child_free_heap_only(data);
		exit(EC_NOT_FOUND);
	}
	execable = access(args[0], X_OK);
	if (execable != 0)
	{
		perror(args[0]);
		free_double_array(args);
		child_free_heap_only(data);
		exit(EC_NOT_EXECUTABLE);
	}
	execve(args[0], args, data->envp);
	perror(args[0]);
	free_double_array(args);
	child_free_heap_only(data);
	exit(EC_NOT_EXECUTABLE);
}

static void	exec_via_path(t_pipex *data, char **args)
{
	char	*full;

	full = resolve_cmd(args[0], data->path);
	if (full)
	{
		execve(full, args, data->envp);
		perror(full);
		free(full);
		free_double_array(args);
		child_free_heap_only(data);
		exit(EC_NOT_EXECUTABLE);
	}
	ft_putstr_fd(args[0], STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(ERR_CMD_NOT_FOUND, STDERR_FILENO);
	free_double_array(args);
	child_free_heap_only(data);
	exit(EC_NOT_FOUND);
}

void	exec_or_die(t_pipex *data, char **args)
{
	if (!args || !args[0] || args[0][0] == '\0')
	{
		ft_putendl_fd(ERR_CMD_NOT_FOUND, STDERR_FILENO);
		free_double_array(args);
		child_free_heap_only(data);
		exit(EC_NOT_FOUND);
	}
	if (has_slash(args[0]))
		exec_direct(data, args);
	exec_via_path(data, args);
}
