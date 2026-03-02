/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyanagis <kyanagis@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 07:06:00 by kyanagis          #+#    #+#             */
/*   Updated: 2025/09/03 06:48:16 by kyanagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	is_limiter_line(const char *line, const char *lim)
{
	size_t	lim_len;
	size_t	i;

	if (!line || !lim)
		return (0);
	lim_len = ft_strlen(lim);
	i = 0;
	while (i < lim_len && line[i] && line[i] == lim[i])
		++i;
	if (i == lim_len && line[i] == '\n')
		return (1);
	return (0);
}

int	setup_here_doc_pipe(const char *limiter)
{
	int		pfd[2];
	char	*line;

	if (pipe(pfd) < 0)
		return (-1);
	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (is_limiter_line(line, limiter))
		{
			free(line);
			break ;
		}
		write(pfd[PIPE_WRITE], line, ft_strlen(line));
		free(line);
	}
	close(pfd[PIPE_WRITE]);
	return (pfd[PIPE_READ]);
}
