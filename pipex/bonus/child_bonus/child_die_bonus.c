/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_die_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyanagis <kyanagis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 04:54:46 by kyanagis          #+#    #+#             */
/*   Updated: 2025/09/02 07:09:50 by kyanagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "child_bonus.h"

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
