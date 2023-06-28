/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrodor <rrodor@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 16:49:53 by rrodor            #+#    #+#             */
/*   Updated: 2023/06/28 16:54:36 by rrodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ph_write(t_philo *philo)
{
	long long int	time;

	pthread_mutex_lock(&philo->data->pen);
	if (philo->data->dead == 1)
	{
		pthread_mutex_unlock(&philo->data->pen);
		return ;
	}
	time = get_time() - philo->data->start_time;
	if (philo->state == THINK)
		printf("%lld %d is thinking\n", time, philo->id + 1);
	else if (philo->state == EAT)
		printf("%lld %d is eating\n", time, philo->id + 1);
	else if (philo->state == SLEEP)
		printf("%lld %d is sleeping\n", time, philo->id + 1);
	else if (philo->state == DEAD)
	{
		printf("%lld %d died\n", time, philo->id + 1);
		philo->data->dead = 1;
	}
	pthread_mutex_unlock(&philo->data->pen);
}

t_philo	*ph_eat(t_philo *philo)
{
	if (philo->id % 2)
	{
		pthread_mutex_lock(&philo->data->fork[philo->id]);
		ph_write2(philo, 1);
		pthread_mutex_lock(&philo->data->fork[(philo->id + 1)
			% philo->data->nb_philo]);
		ph_write2(philo, 2);
	}
	else
	{
		pthread_mutex_lock(&philo->data->fork[(philo->id + 1)
			% philo->data->nb_philo]);
		ph_write2(philo, 2);
		pthread_mutex_lock(&philo->data->fork[philo->id]);
		ph_write2(philo, 1);
	}
	ph_write(philo);
	philo->nb_eat++;
	philo->last_eat = get_time();
	usleep(philo->data->time_to_eat * 1000);
	philo->state = SLEEP;
	pthread_mutex_unlock(&philo->data->fork[philo->id]);
	pthread_mutex_unlock(&philo->data->fork[(philo->id + 1)
		% philo->data->nb_philo]);
	return (philo);
}

t_philo	*ph_sleep(t_philo *philo)
{
	ph_write(philo);
	usleep(philo->data->time_to_sleep * 1000);
	philo->state = THINK;
	return (philo);
}

void	*ph_threadphilo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->data->nb_eat == -1 || philo->nb_eat < philo->data->nb_eat)
	{
		if (philo->state == DEAD)
			return (NULL);
		if (philo->last_eat + philo->data->time_to_die < get_time())
		{
			philo->state = DEAD;
			ph_write(philo);
			return (NULL);
		}
		if (philo->state == THINK)
		{
			ph_write(philo);
			philo->state = EAT;
		}
		else if (philo->state == EAT)
			philo = ph_eat(philo);
		else if (philo->state == SLEEP)
			philo = ph_sleep(philo);
	}
	return (NULL);
}
