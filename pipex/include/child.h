/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyanagis <kyanagis@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 23:22:29 by kyanagis          #+#    #+#             */
/*   Updated: 2025/09/01 04:58:48 by kyanagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHILD_H
# define CHILD_H

# include "pipex.h"

# define PIPE_READ 0
# define PIPE_WRITE 1

typedef struct s_exec
{
	int	idx;
	int	in_fd;
	int	pipefd[2];
}		t_exec;

void	cleanup_and_die(t_pipex *data, t_exec *stage, const char *err_msg);
void	child_perror_exit_free(t_pipex *data, const char *msg, int code);
void	child_exit_free(t_pipex *data, int code);
void	child_free_heap_only(t_pipex *data);
void	open_devnull_read_die(t_pipex *data);
void	redirect_io(t_pipex *data, t_exec stage);
void	exec_or_die(t_pipex *data, char **args);

void	child_side(t_pipex *data, t_exec stage, char **argv);
#endif
