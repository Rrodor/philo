/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrodor <rrodor@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 14:27:19 by rrodor            #+#    #+#             */
/*   Updated: 2023/06/24 18:11:15 by rrodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

# define EAT 0
# define SLEEP 1
# define THINK 2
# define FORK 3
# define DEAD 4

typedef struct s_philo
{
	int				id;
	int				state;
	int				nb_eat;
	int				dead;
	long long int	last_eat;
	struct s_data	*data;
	pthread_t		*thread;
}	t_philo;

typedef struct s_data
{
	int				nb_philo;
	long long int	time_to_die;
	long long int	time_to_eat;
	long long int	time_to_sleep;
	long long int	start_time;
	int				nb_eat;
	int				dead;
	t_philo 		**philo;
	pthread_mutex_t	pen;
}	t_data;

void			*ph_threadphilo(void *arg);
long long int	get_time(void);

#endif

