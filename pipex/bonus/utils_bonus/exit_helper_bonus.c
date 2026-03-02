/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_helper_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyanagis <kyanagis@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 22:08:38 by kyanagis          #+#    #+#             */
/*   Updated: 2025/09/02 00:49:21 by kyanagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "child_bonus.h"
#include "pipex_bonus.h"

void	usage_exit(void)
{
	ft_putendl_fd(USAGE, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	perror_exit(const char *msg, const int exit_status)
{
	perror(msg);
	exit(exit_status);
}

void	destroy_pipex(t_pipex *data)
{
	if (!data)
		return ;
	safe_close(&data->infile_fd);
	safe_close(&data->outfile_fd);
	free_double_array(data->path);
	data->path = NULL;
	free(data->pids);
	data->pids = NULL;
}

void	cleanup_and_die(t_pipex *data, t_exec *stage, const char *err_msg)
{
	int	saved_in;

	saved_in = -1;
	if (stage)
		saved_in = stage->in_fd;
	if (stage)
		safe_close(&stage->in_fd);
	if (data)
	{
		if (data->infile_fd >= 0 && data->infile_fd != saved_in)
			safe_close(&data->infile_fd);
		if (data->outfile_fd >= 0)
			safe_close(&data->outfile_fd);
		free(data->pids);
		data->pids = NULL;
		free_double_array(data->path);
		data->path = NULL;
	}
	perror_exit(err_msg, EXIT_FAILURE);
}

void	child_free_heap_only(t_pipex *data)
{
	free_double_array(data->path);
	data->path = NULL;
	free(data->pids);
	data->pids = NULL;
}
