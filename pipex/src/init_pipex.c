/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyanagis <kyanagis@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 05:06:45 by kyanagis          #+#    #+#             */
/*   Updated: 2025/09/01 06:56:13 by kyanagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**find_and_split_path(char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (ft_split(envp[i] + 5, ':'));
		++i;
	}
	return (NULL);
}

static void	open_files(t_pipex *data, char **argv)
{
	data->infile_fd = open(argv[1], O_RDONLY);
	if (data->infile_fd < 0)
		perror(argv[1]);
	data->outfile_fd = -1;
}

void	init_pipex(t_pipex *data, int argc, char **argv, char **envp)
{
	open_files(data, argv);
	data->cmd_count = argc - 3;
	data->envp = envp;
	data->outfile_path = argv[argc - 1];
	data->path = find_and_split_path(envp);
	data->pids = malloc(sizeof(pid_t) * data->cmd_count);
	if (!data->pids)
	{
		free_double_array(data->path);
		safe_close(&data->infile_fd);
		safe_close(&data->outfile_fd);
		perror_exit(ERR_MALLOC, EXIT_FAILURE);
	}
}
