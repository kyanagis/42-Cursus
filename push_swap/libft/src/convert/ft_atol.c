/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyanagis <kyanagis@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 06:00:15 by kyanagis          #+#    #+#             */
/*   Updated: 2025/07/30 02:44:45 by kyanagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atol(const char *s)
{
	long	sign;
	long	res;

	sign = 1;
	res = 0;
	while (*s >= 9 && *s <= 13)
		++s;
	if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			sign = -1;
		++s;
	}
	if (*s == '\0')
		error_exit();
	while (*s)
	{
		if (*s < '0' || *s > '9')
			error_exit();
		res = res * 10 + (*s - '0');
		s++;
	}
	return (res * sign);
}
