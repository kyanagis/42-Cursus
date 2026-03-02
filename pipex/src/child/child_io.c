/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_io.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyanagis <kyanagis@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 05:37:33 by kyanagis          #+#    #+#             */
/*   Updated: 2025/09/01 05:32:13 by kyanagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "child.h"

void	open_devnull_read_die(t_pipex *data)
{
	int	devnull_fd;

	devnull_fd = open("/dev/null", O_RDONLY);
	if (devnull_fd < 0 || dup2(devnull_fd, STDIN_FILENO) == -1)
	{
		if (devnull_fd >= 0)
			close(devnull_fd);
		child_perror_exit_free(data, ERR_DEVNULL, EXIT_FAILURE);
	}
	close(devnull_fd);
}

static void	setup_stdin(t_pipex *data, int in_fd)
{
	if (in_fd < 0)
		open_devnull_read_die(data);
	else
	{
		if (dup2(in_fd, STDIN_FILENO) < 0)
		{
			close(in_fd);
			child_perror_exit_free(data, ERR_DUP, EXIT_FAILURE);
		}
		close(in_fd);
	}
}

static void	setup_stdout(t_pipex *data, t_exec stage)
{
	int	fd;

	if (stage.idx < data->cmd_count - 1)
	{
		close(stage.pipefd[PIPE_READ]);
		if (dup2(stage.pipefd[PIPE_WRITE], STDOUT_FILENO) < 0)
		{
			close(stage.pipefd[PIPE_WRITE]);
			child_perror_exit_free(data, ERR_DUP, EXIT_FAILURE);
		}
		close(stage.pipefd[PIPE_WRITE]);
	}
	else
	{
		fd = open(data->outfile_path, O_WRONLY | O_CREAT | O_TRUNC,
				FILE_PERMISSIONS);
		if (fd < 0)
			child_perror_exit_free(data, data->outfile_path, EXIT_FAILURE);
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			close(fd);
			child_perror_exit_free(data, ERR_DUP, EXIT_FAILURE);
		}
		close(fd);
	}
}

void	redirect_io(t_pipex *data, t_exec stage)
{
	setup_stdin(data, stage.in_fd);
	setup_stdout(data, stage);
}
