/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipex_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyanagis <kyanagis@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 05:06:45 by kyanagis          #+#    #+#             */
/*   Updated: 2025/09/03 06:46:43 by kyanagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

static void	open_infile_if_normal(t_pipex *data, char **argv)
{
	data->infile_fd = open(argv[1], O_RDONLY);
	if (data->infile_fd < 0)
		perror(argv[1]);
}

static void	setup_branches_and_alloc(t_pipex *data, int argc, char **argv)
{
	if (is_here_doc(argv[1]))
	{
		data->out_mode = OUT_APPEND;
		data->cmd_count = argc - 4;
		data->infile_fd = setup_here_doc_pipe(argv[2]);
		if (data->infile_fd < 0)
		{
			free_double_array(data->path);
			perror_exit(ERR_PIPE, EXIT_FAILURE);
		}
	}
	else
	{
		data->out_mode = OUT_TRUNC;
		data->cmd_count = argc - 3;
		open_infile_if_normal(data, argv);
	}
}

static void	alloc_pids_or_die(t_pipex *data)
{
	data->pids = (pid_t *)malloc(sizeof(pid_t) * data->cmd_count);
	if (!data->pids)
	{
		free_double_array(data->path);
		safe_close(&data->infile_fd);
		perror_exit(ERR_MALLOC, EXIT_FAILURE);
	}
}

void	init_pipex(t_pipex *data, int argc, char **argv, char **envp)
{
	ft_bzero(data, sizeof(*data));
	data->envp = envp;
	data->outfile_fd = -1;
	data->outfile_path = argv[argc - 1];
	data->path = find_and_split_path(envp);
	setup_branches_and_alloc(data, argc, argv);
	alloc_pids_or_die(data);
}
