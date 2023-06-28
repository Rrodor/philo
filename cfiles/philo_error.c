/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrodor <rrodor@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 16:54:52 by rrodor            #+#    #+#             */
/*   Updated: 2023/06/28 17:06:53 by rrodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	testatoi(char *str)
{
	int				i;
	long long int	test;

	i = 0;
	test = 0;
	if (!str[i])
		return (0);
	if (str[i] == '-')
		return (0);
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] >= 48 && str[i] <= 57)
			i++;
		else
			return (0);
		test = test * 10 + str[i - 1] - 48;
		if (test > 2147483647)
			return (0);
	}
	return (1);
}

int	testval(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!testatoi(argv[i]))
		{
			printf("Error: %s is not a valid argument\n", argv[i]);
			return (0);
		}
		i++;
	}
	return (1);
}
