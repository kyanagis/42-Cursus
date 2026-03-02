/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyanagis <kyanagis@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 05:06:23 by kyanagis          #+#    #+#             */
/*   Updated: 2025/09/03 06:48:57 by kyanagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "child_bonus.h"

static void	parent_side(int *in_fd, int pipefd[2])
{
	safe_close(&pipefd[PIPE_WRITE]);
	safe_close(in_fd);
	*in_fd = pipefd[PIPE_READ];
}

static void	pipe_if_needed(t_pipex *data, t_exec *stage)
{
	if (stage->idx < data->cmd_count - 1)
	{
		if (pipe(stage->pipefd) < 0)
			cleanup_and_die(data, stage, ERR_PIPE);
	}
}

static pid_t	fork_or_die(t_pipex *data, t_exec *stage)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		if (stage->idx < data->cmd_count - 1)
		{
			safe_close(&stage->pipefd[PIPE_READ]);
			safe_close(&stage->pipefd[PIPE_WRITE]);
		}
		cleanup_and_die(data, stage, ERR_FORK);
	}
	return (pid);
}

static int	wait_all_and_status(t_pipex *data, pid_t last_pid)
{
	int		i;
	int		code;
	int		st;
	pid_t	w;

	code = 0;
	i = data->cmd_count;
	while (i > 0)
	{
		st = 0;
		w = waitpid(data->pids[i - 1], &st, 0);
		if (w == last_pid)
		{
			if (WIFEXITED(st))
				code = WEXITSTATUS(st);
			else if (WIFSIGNALED(st))
				code = 128 + WTERMSIG(st);
		}
		--i;
	}
	return (code);
}

int	execute_pipeline(t_pipex *data, char **argv)
{
	t_exec	stage;
	int		i;
	int		status;

	stage.in_fd = data->infile_fd;
	i = 0;
	while (i < data->cmd_count)
	{
		stage.idx = i;
		pipe_if_needed(data, &stage);
		data->pids[i] = fork_or_die(data, &stage);
		if (data->pids[i] == 0)
			child_side(data, stage, argv);
		else if (i < data->cmd_count - 1)
			parent_side(&stage.in_fd, stage.pipefd);
		++i;
	}
	if (stage.in_fd != data->infile_fd)
		safe_close(&stage.in_fd);
	status = wait_all_and_status(data, data->pids[data->cmd_count - 1]);
	return (status);
}
