/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   behavior.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 21:17:32 by chanheki          #+#    #+#             */
/*   Updated: 2023/04/12 04:42:37 by chanheki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 * Description: 철학자들이 생각하고나서, 철학자들이 포크를 집는다.
 *              1. 해당 철학자가 살아있는지 확인한다. 그리고 생각한다.
 *              2. 철학자가 1명일때 포크를 집고 죽는다.
 *              3. 철학자가 왼쪽 포크를 집는다.
 *              4. 포크를 집었다는 메시지를 출력한다.
 *              5. 철학자가 오른쪽 포크를 집는다.
 *              6. 포크를 집었다는 메시지를 출력한다.
 * Param.   #1: t_philosophers 구조체의 포인터
 * Return     : true = 죽음
 *              false = 살아있음
 */
bool	thinking_and_take_fork(t_philosophers *philosophers)
{
	if (print_thinking(philosophers))
		return (true);
	pthread_mutex_lock(philosophers->left_fork);
	if (print_fork(philosophers))
	{
		pthread_mutex_unlock(philosophers->left_fork);
		return (true);
	}
	if (philosophers->philo_info->number_of_philosophers == 1)
	{
		pthread_mutex_unlock(philosophers->left_fork);
		return (true);
	}
	pthread_mutex_lock(philosophers->right_fork);
	if (print_fork(philosophers))
	{
		pthread_mutex_unlock(philosophers->right_fork);
		return (true);
	}
	return (false);
}

/*
 * Description: 철학자들이 먹는다.
 *              1. 식사하는 동안 critical_section을 잠금한다.
 *              1-2. 마지막으로 식사를 시작한 시간을 갱신한다.
 *              1-3. critical_section을 잠금 해제한다.
 *              2. 식사 메시지를 출력한다.
 *              3. 식사를 한다 = 식사 시간 만큼 sleep한다.
 *              4. 식사하는 동안 critical_section을 잠금한다.
 *              4-1. 식사 횟수를 1 증가시킨다.
 *              4-2. critical_section을 잠금 해제한다.
 *              5. 왼쪽 포크를 놓는다.
 *              6. 오른쪽 포크를 놓는다.
 * Param.   #1: t_philosophers 구조체의 포인터
 * Return     : true = 죽음
 *              false = 살아있음
 */
bool	take_eat(t_philosophers *philosophers)
{
	long long	now;

	now = get_time();
	pthread_mutex_lock(&philosophers->critical_section);
	philosophers->last_time_eaten = now;
	pthread_mutex_unlock(&philosophers->critical_section);
	if (print_eating(philosophers))
	{
		pthread_mutex_unlock(philosophers->left_fork);
		pthread_mutex_unlock(philosophers->right_fork);
		return (true);
	}
	my_usleep(philosophers->philo_info->time_to_eat);
	pthread_mutex_lock(&philosophers->critical_section);
	philosophers->number_of_times_eaten++;
	pthread_mutex_unlock(&philosophers->critical_section);
	pthread_mutex_unlock(philosophers->left_fork);
	pthread_mutex_unlock(philosophers->right_fork);
	return (false);
}

/*
 * Description: 철학자들이 잠을 잔다. 잠을 잘 땐 아무것도 하면 안된다.
 *              1. 잠을 잔다는 메시지를 출력한다.
 *              2. 잠을 잔다 = 잠자는 시간 만큼 m초 만큼 sleep한다.
 * Param.   #1: t_philosophers 구조체의 포인터
 * Return     : true = 죽음
 *              false = 살아있음
 */
bool	take_sleep(t_philosophers *philosophers)
{
	if (print_sleeping(philosophers))
		return (true);
	my_usleep(philosophers->philo_info->time_to_sleep);
	return (false);
}
