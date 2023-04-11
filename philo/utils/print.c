/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 21:57:18 by chanheki          #+#    #+#             */
/*   Updated: 2023/04/12 01:42:07 by chanheki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/*
 * Description: 몇번 철학자의 죽음을 출력한다.
 * Param.   #1: 철학자들의 정보를 담고 있는 구조체
 * Return     : true = 죽음
 */
void	print_death(t_philosophers *philosophers)
{
	long long	time;

	pthread_mutex_lock(&philosophers->philo_info->during_routine);
	time = get_time() - philosophers->philo_info->borntocode;
	printf("%lld %d died\n", time, philosophers->number);
	philosophers->philo_info->end_flag = true;
	pthread_mutex_unlock(&philosophers->philo_info->during_routine);
}

/*
 * Description: 몇번 철학자가 포크를 집었다고 출력한다.
 * Param.   #1: 철학자들의 정보를 담고 있는 구조체
 * Return     : true = 죽음
 *              false = 살아있음
 */
bool	print_fork(t_philosophers *philosophers)
{
	long long	time;

	pthread_mutex_lock(&philosophers->philo_info->during_routine);
	if (philosophers->philo_info->end_flag)
	{
		pthread_mutex_unlock(&philosophers->philo_info->during_routine);
		return (true);
	}
	time = get_time() - philosophers->philo_info->borntocode;
	printf("%lld %d has taken a fork\n", time, philosophers->number);
	pthread_mutex_unlock(&philosophers->philo_info->during_routine);
	return (false);
}

/*
 * Description: 몇번 철학자가 밥을 먹는다는 메시지를 출력한다.
 * Param.   #1: 철학자들의 정보를 담고 있는 구조체
 * Return     : true = 죽음
 *              false = 살아있음
 */
bool	print_eating(t_philosophers *philosophers)
{
	long long	time;

	pthread_mutex_lock(&philosophers->philo_info->during_routine);
	if (philosophers->philo_info->end_flag)
	{
		pthread_mutex_unlock(&philosophers->philo_info->during_routine);
		return (true);
	}
	time = get_time() - philosophers->philo_info->borntocode;
	printf("%lld %d is eating\n", time, philosophers->number);
	pthread_mutex_unlock(&philosophers->philo_info->during_routine);
	return (false);
}

/*
 * Description: 몇번 철학자가 자는 메시지를 출력한다.
 * Param.   #1: 철학자들의 정보를 담고 있는 구조체
 * Return     : true = 죽음
 *              false = 살아있음
 */
bool	print_sleeping(t_philosophers *philosophers)
{
	long long	time;

	pthread_mutex_lock(&philosophers->philo_info->during_routine);
	if (philosophers->philo_info->end_flag)
	{
		pthread_mutex_unlock(&philosophers->philo_info->during_routine);
		return (true);
	}
	time = get_time() - philosophers->philo_info->borntocode;
	printf("%lld %d is sleeping\n", time, philosophers->number);
	pthread_mutex_unlock(&philosophers->philo_info->during_routine);
	return (false);
}

/*
 * Description: 몇번 철학자가 생각한다는 메시지를 출력한다.
 * Param.   #1: 철학자들의 정보를 담고 있는 구조체
 * Return     : true = 죽음
 *              false = 살아있음
 */
bool	print_thinking(t_philosophers *philosophers)
{
	long long	time;

	pthread_mutex_lock(&philosophers->philo_info->during_routine);
	if (philosophers->philo_info->end_flag)
	{
		pthread_mutex_unlock(&philosophers->philo_info->during_routine);
		return (true);
	}
	time = get_time() - philosophers->philo_info->borntocode;
	printf("%lld %d is thinking\n", time, philosophers->number);
	pthread_mutex_unlock(&philosophers->philo_info->during_routine);
	return (false);
}
