/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrodor <rrodor@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 14:27:19 by rrodor            #+#    #+#             */
/*   Updated: 2023/06/28 17:04:42 by rrodor           ###   ########.fr       */
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
	int				nb_eat;
	int				dead;
	long long int	time_to_die;
	long long int	time_to_eat;
	long long int	time_to_sleep;
	long long int	start_time;
	t_philo			**philo;
	pthread_mutex_t	pen;
	pthread_mutex_t	*fork;
}	t_data;

void			*ph_threadphilo(void *arg);
long long int	get_time(void);
void			ph_free(t_data *data);
void			ph_mutexdestroy(t_data *data);
void			ph_write2(t_philo *philo, int i);
int				ph_atoi(const char *nptr);
int				testval(int argc, char **argv);

#endif
