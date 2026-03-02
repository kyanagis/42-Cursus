/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_side.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyanagis <kyanagis@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 05:08:09 by kyanagis          #+#    #+#             */
/*   Updated: 2025/09/02 00:29:53 by kyanagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "child.h"

void	child_side(t_pipex *data, t_exec stage, char **argv)
{
	char	**args;

	redirect_io(data, stage);
	if (stage.idx != 0 && data->infile_fd >= 0)
		close(data->infile_fd);
	args = tokenize_argv(argv[2 + stage.idx]);
	if (!args)
		exit(EC_NOT_FOUND);
	exec_or_die(data, args);
}
