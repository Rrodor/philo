/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrodor <rrodor@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 15:35:25 by rrodor            #+#    #+#             */
/*   Updated: 2023/06/24 18:48:38 by rrodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	*init_philo(t_data *data)
{
	int		i;

	i = 0;
	data->philo = malloc(sizeof(t_philo *) * data->nb_philo);
	if (!data->philo)
		return (NULL);
	while (i < data->nb_philo)
	{
		data->philo[i] = malloc(sizeof(t_philo));
		if (!data->philo[i])
			return (0);
		data->philo[i]->id = i;
		data->philo[i]->state = THINK;
		data->philo[i]->nb_eat = 0;
		data->philo[i]->data = data;
		data->philo[i]->thread = malloc(sizeof(pthread_t));
		data->philo[i]->dead = 0;
		data->philo[i]->last_eat = get_time();
		i++;
	}
	return (data);
}

pthread_mutex_t	*init_mutex(t_data *data)
{
	pthread_mutex_t	*mutex;
	int				i;

	i = 0;
	mutex = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!mutex)
		return (NULL);
	while (i < data->nb_philo)
	{
		pthread_mutex_init(&mutex[i], NULL);
		i++;
	}
	return (mutex);
}

t_data	*init_data(int argc, char const *argv[])
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->nb_philo = atoi(argv[1]);
	data->time_to_die = atoi(argv[2]);
	data->time_to_eat = atoi(argv[3]);
	data->time_to_sleep = atoi(argv[4]);
	data->start_time = get_time();
	data->dead = 0;
	pthread_mutex_init(&data->pen, NULL);
	if (argc == 6)
		data->nb_eat = atoi(argv[5]);
	else
		data->nb_eat = -1;
	data = init_philo(data);
	if (!data)
		return (NULL);
	data->fork = init_mutex(data);
	if (!data->fork)
		return (NULL);
	return (data);
}

int	ph_createthread(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_create(data->philo[i]->thread, NULL,
			&ph_threadphilo, (void *)data->philo[i]);
		i++;
	}
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(*data->philo[i]->thread, NULL);
		i++;
	}
	return (0);
}

int	main(int argc, char const *argv[])
{
	t_data	*data;
	int		i;

	i = 0;
	if (argc < 5 || argc > 6)
	{
		printf("number_of_philosophers time_to_die time_to_eat time_to_sleep");
		printf("[number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	data = init_data(argc, argv);
	if (!data)
		return (1);
	ph_createthread(data);
	ph_mutexdestroy(data);
	ph_free(data);
	return (0);
}
