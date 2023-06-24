/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrodor <rrodor@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 17:33:54 by rrodor            #+#    #+#             */
/*   Updated: 2023/06/24 17:34:00 by rrodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long int get_time(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
