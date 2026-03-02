/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyanagis <kyanagis@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 05:06:36 by kyanagis          #+#    #+#             */
/*   Updated: 2025/09/03 06:32:51 by kyanagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

bool	is_here_doc(char *argv)
{
	if (argv && ft_strncmp(argv, "here_doc", 8) == 0)
		return (true);
	return (false);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	data;
	int		exit_code;

	if (argc < 5 || (is_here_doc(argv[1]) && (argc < 6)))
		usage_exit();
	init_pipex(&data, argc, argv, envp);
	exit_code = execute_pipeline(&data, argv);
	destroy_pipex(&data);
	return (exit_code);
}
