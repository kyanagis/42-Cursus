/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyanagis <kyanagis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 01:28:31 by kyanagis          #+#    #+#             */
/*   Updated: 2026/01/05 19:03:55 by kyanagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(int c)
{
	return ((unsigned int)(c - '0') <= 9u);
}

static const char	*skip_spaces(const char *s)
{
	while (*s == ' ' || (*s >= 9 && *s <= 13))
		s++;
	return (s);
}

static bool	accumulate_digit(long *value, int digit)
{
	if (*value > (INT_MAX - digit) / 10)
		return (false);
	*value = (*value << 3) + (*value << 1) + digit;
	return (true);
}

static bool	parse_int(const char *s, int *out_value)
{
	long		value;
	const char	*cursor;

	if (!s || !*s)
		return (false);
	cursor = skip_spaces(s);
	if (*cursor == '+')
		++cursor;
	if (!ft_isdigit(*cursor))
		return (false);
	value = 0;
	while (ft_isdigit(*cursor))
	{
		if (!accumulate_digit(&value, *cursor - '0'))
			return (false);
		++cursor;
	}
	if (*cursor != '\0' || value < 1)
		return (false);
	*out_value = (int)value;
	return (true);
}

bool	parse_config(int argc, char **argv, t_config *config)
{
	if (!(argc == 5 || argc == 6))
		return (false);
	if (!parse_int(argv[1], &config->philo_count))
		return (false);
	if (!parse_int(argv[2], &config->die_ms))
		return (false);
	if (!parse_int(argv[3], &config->eat_ms))
		return (false);
	if (!parse_int(argv[4], &config->sleep_ms))
		return (false);
	if (argc == 6)
	{
		if (!parse_int(argv[5], &config->must_eat))
			return (false);
	}
	else
		config->must_eat = -1;
	return (true);
}
