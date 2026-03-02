/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyanagis <kyanagis@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 23:03:21 by kyanagis          #+#    #+#             */
/*   Updated: 2025/09/01 02:24:21 by kyanagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "error_msg.h"
# include "exit_codes.h"
# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

// # define FILE_PERMISSIONS S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH

enum
{
	FILE_PERMISSIONS = S_IRUSR | S_IWUSR | S_IROTH | S_IRGRP
};

typedef struct s_pipex
{
	int			infile_fd;
	int			outfile_fd;
	int			cmd_count;
	const char	*outfile_path;
	pid_t		*pids;
	char		**path;
	char		**envp;
}				t_pipex;

void			free_double_array(char **arr);
void			safe_close(int *fdp);
char			*join3(const char *s1, const char *s2, const char *s3);
void			usage_exit(void);
void			perror_exit(const char *msg, const int exit_status);
void			destroy_pipex(t_pipex *data);

void			init_pipex(t_pipex *data, int argc, char **argv, char **envp);
int				execute_pipeline(t_pipex *data, char **argv);
char			**tokenize_argv(const char *line);

#endif