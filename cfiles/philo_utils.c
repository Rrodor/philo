/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrodor <rrodor@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 17:33:54 by rrodor            #+#    #+#             */
/*   Updated: 2023/06/27 18:13:26 by rrodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long int	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ph_mutexdestroy(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->fork[i]);
		i++;
	}
	pthread_mutex_destroy(&data->pen);
}

void	ph_free(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		free(data->philo[i]->thread);
		free(data->philo[i]);
		i++;
	}
	free(data->fork);
	free(data->philo);
	free(data);
}

void	ph_write2(t_philo *philo, int i)
{
	long long int	time;

	pthread_mutex_lock(&philo->data->pen);
	if (philo->data->dead == 1)
	{
		pthread_mutex_unlock(&philo->data->pen);
		return ;
	}
	time = get_time() - philo->data->start_time;
	if (i == 1)
		printf("%lld %d has taken a fork\n", time, philo->id + 1);
	else if (i == 2)
		printf("%lld %d has taken a fork\n", time, philo->id + 1
			% philo->data->nb_philo);
	pthread_mutex_unlock(&philo->data->pen);
}

int	ph_atoi(const char *nptr)
{
	int	i;
	int	pol;
	int	res;

	i = 0;
	pol = 1;
	res = 0;
	while ((nptr[i] > 8 && nptr[i] < 14) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			pol *= -1;
		i++;
	}
	while (nptr[i] > 47 && nptr[i] < 58)
	{
		res = res * 10 + (nptr[i] - 48);
		i++;
	}
	return (res * pol);
}
