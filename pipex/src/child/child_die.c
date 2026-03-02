/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_die.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyanagis <kyanagis@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 04:54:46 by kyanagis          #+#    #+#             */
/*   Updated: 2025/09/01 05:01:53 by kyanagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "child.h"

void	child_exit_free(t_pipex *data, int code)
{
	child_free_heap_only(data);
	exit(code);
}

void	child_perror_exit_free(t_pipex *data, const char *msg, int code)
{
	perror(msg);
	child_free_heap_only(data);
	exit(code);
}
