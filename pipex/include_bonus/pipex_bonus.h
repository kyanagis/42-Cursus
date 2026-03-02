/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyanagis <kyanagis@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 23:03:21 by kyanagis          #+#    #+#             */
/*   Updated: 2025/09/03 06:48:01 by kyanagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "error_msg_bonus.h"
# include "exit_codes_bonus.h"
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

# define PIPE_READ 0
# define PIPE_WRITE 1

enum
{
	FILE_PERMISSIONS = S_IRUSR | S_IWUSR | S_IROTH | S_IRGRP
};

typedef enum e_out_mode
{
	OUT_TRUNC = 0,
	OUT_APPEND = 1
}				t_out_mode;

typedef struct s_pipex
{
	int			infile_fd;
	int			outfile_fd;
	int			cmd_count;
	const char	*outfile_path;
	t_out_mode	out_mode;
	pid_t		*pids;
	char		**path;
	char		**envp;
}				t_pipex;

bool			is_here_doc(char *argv);

void			free_double_array(char **arr);
void			safe_close(int *fdp);
char			*join3(const char *s1, const char *s2, const char *s3);
void			usage_exit(void);
void			perror_exit(const char *msg, const int exit_status);
void			destroy_pipex(t_pipex *data);

void			init_pipex(t_pipex *data, int argc, char **argv, char **envp);
int				execute_pipeline(t_pipex *data, char **argv);
char			**tokenize_argv(const char *line);

// here_doc helper
int				setup_here_doc_pipe(const char *limiter);

#endif
