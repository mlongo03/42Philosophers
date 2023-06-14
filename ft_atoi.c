/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 12:14:20 by mlongo            #+#    #+#             */
/*   Updated: 2023/06/12 17:17:32 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"
#include <limits.h>
#include <stdio.h>

static int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

static void	error_long(void)
{
	printf("Error\n");
	exit (1);
}

static int	ft_sign(char c)
{
	return (c == '-' || c == '+');
}

static int	ft_spaces(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r'
		|| c == '\v' || c == '\f');
}

int	ft_atoi(const char *nptr)
{
	char	*p;
	int		s;
	long	r;

	p = (char *) nptr;
	s = 1;
	r = 0;
	while (ft_spaces(*p))
		p++;
	if (ft_sign(*p))
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
		error_long();
	return (r * s);
}
