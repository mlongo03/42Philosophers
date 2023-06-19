/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 12:14:20 by mlongo            #+#    #+#             */
/*   Updated: 2023/06/19 17:58:27 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"
#include <limits.h>
#include <stdio.h>

static int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

static int	ft_error(void)
{
	printf("Error\n");
	return (1);
}

static int	ft_spaces(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r'
		|| c == '\v' || c == '\f');
}

static int	check_int(char *str)
{
	int	j;

	j = 0;
	while (str[j])
	{
		if (str[j] < 48 || str[j] > 57)
		{
			ft_error();
			return (1);
		}
		j++;
	}
	return (0);
}

int	ft_atoi(const char *nptr)
{
	char	*p;
	int		s;
	long	r;

	p = (char *) nptr;
	if (check_int(p))
		return (-2);
	s = 1;
	r = 0;
	while (ft_spaces(*p))
		p++;
	if (*p == '-' || *p == '+')
	{
		if (*p == '-')
			s = -1;
		p++;
	}
	while (ft_isdigit((int) *p))
	{
		r *= 10;
		r += *(p++) - 48;
	}
	if ((r * s) > INT_MAX || (r * s) < INT_MIN)
		ft_error();
	return (r * s);
}
