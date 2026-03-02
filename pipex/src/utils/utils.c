/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyanagis <kyanagis@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 22:47:51 by kyanagis          #+#    #+#             */
/*   Updated: 2025/08/29 00:59:07 by kyanagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static size_t	safe_strlen(const char *str)
{
	if (!str)
		return (0);
	return (ft_strlen(str));
}

char	*join3(const char *s1, const char *s2, const char *s3)
{
	size_t	len1;
	size_t	len2;
	size_t	len3;
	char	*result;

	len1 = safe_strlen(s1);
	len2 = safe_strlen(s2);
	len3 = safe_strlen(s3);
	result = malloc(len1 + len2 + len3 + 1);
	if (!result)
		perror_exit(ERR_MALLOC, EXIT_FAILURE);
	if (s1)
		ft_memcpy(result, s1, len1);
	if (s2)
		ft_memcpy(result + len1, s2, len2);
	if (s3)
		ft_memcpy(result + len1 + len2, s3, len3);
	result[len1 + len2 + len3] = '\0';
	return (result);
}

void	free_double_array(char **arr)
{
	size_t	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		++i;
	}
	free(arr);
}

void	safe_close(int *fdp)
{
	if (fdp && *fdp >= 0)
	{
		close(*fdp);
		*fdp = -1;
	}
}

int	is_dq_escapable(char c)
{
	return (c == '\"' || c == '\\' || c == '$' || c == '`');
}
