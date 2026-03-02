/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyanagis <kyanagis@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 05:06:36 by kyanagis          #+#    #+#             */
/*   Updated: 2025/08/30 01:48:13 by kyanagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	data;
	int		exit_code;

	if (argc != 5)
		usage_exit();
	init_pipex(&data, argc, argv, envp);
	exit_code = execute_pipeline(&data, argv);
	destroy_pipex(&data);
	return (exit_code);
}
