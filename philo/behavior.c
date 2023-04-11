/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   behavior.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 21:17:32 by chanheki          #+#    #+#             */
/*   Updated: 2023/04/08 22:37:19 by chanheki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 * Description: 철학자들이 포크를 집는다.
 *              0. 철학자가 1명일때 포크를 집고 죽는다.
 *              1. 철학자가 왼쪽 포크를 집는다.
 *              2. 포크를 집었다는 메시지를 출력한다.
 *              3. 철학자가 오른쪽 포크를 집는다.
 *              4. 포크를 집었다는 메시지를 출력한다.
 * Param.   #1: t_philosophers 구조체의 포인터
 * Return     : 없음
 */
void	take_fork(t_philosophers *philosophers)
{
	if (!philosophers->alive)
		return ;
	pthread_mutex_lock(philosophers->left_fork);
	print_fork(philosophers);
	if (philosophers->philo_info->end_flag
		|| philosophers->philo_info->number_of_philosophers == 1)
	{
		pthread_mutex_unlock(philosophers->left_fork);
		philosophers->alive = false;
		return ;
	}
	pthread_mutex_lock(philosophers->right_fork);
	print_fork(philosophers);
}

void	take_eat(t_philosophers *philosophers)
{
	if (!philosophers->alive)
		return ;
	pthread_mutex_lock(&philosophers->critical_section);
	print_eating(philosophers);
	philosophers->last_time_eaten = get_time();
	philosophers->number_of_times_eaten++;
	my_usleep(philosophers->philo_info->time_to_eat);
	pthread_mutex_unlock(&philosophers->critical_section);
	pthread_mutex_unlock(philosophers->left_fork);
	pthread_mutex_unlock(philosophers->right_fork);
}

/*
 * Description: 철학자들이 잠을 잔다.
 *              0. 해당 철학자가 살아있는지 확인한다.
 *              1. 잠을 잔다는 메시지를 출력한다.
 *              2. 잠을 잔다 = 잠자는 시간 만큼 m초 만큼 sleep한다.
 * Param.   #1: t_philosophers 구조체의 포인터
 * Return     : 없음
 */
void	take_sleep(t_philosophers *philosophers)
{
	if (!philosophers->alive)
		return ;
	print_sleeping(philosophers);
	my_usleep(philosophers->philo_info->time_to_sleep);
}

/*
 * Description: 철학자들이 생각한다.
 *              0. 해당 철학자가 살아있는지 확인한다.
 *              1. 생각한다는 메시지를 출력한다.
 * Param.   #1: t_philosophers 구조체의 포인터
 * Return     : 없음
 */
void	thinking(t_philosophers *philosophers)
{
	if (!philosophers->alive)
		return ;
	print_thinking(philosophers);
}
