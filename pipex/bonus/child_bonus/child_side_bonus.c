/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_side_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyanagis <kyanagis@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 05:08:09 by kyanagis          #+#    #+#             */
/*   Updated: 2025/09/03 06:00:20 by kyanagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "child_bonus.h"

void	child_side(t_pipex *data, t_exec stage, char **argv)
{
	char	**args;
	int		base;

	redirect_io(data, stage);
	if (stage.idx != 0 && data->infile_fd >= 0)
		close(data->infile_fd);
	base = 2;
	if (data->out_mode == OUT_APPEND)
		base = 3;
	args = tokenize_argv(argv[base + stage.idx]);
	if (!args || !args[0] || !args[0][0])
	{
		free_double_array(args);
		child_perror_exit_free(data, ERR_CMD_NOT_FOUND, EC_NOT_FOUND);
	}
	exec_or_die(data, args);
}
