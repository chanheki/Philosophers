/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 20:53:04 by chanheki          #+#    #+#             */
/*   Updated: 2023/04/12 04:13:15 by chanheki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 * Description: 철학자가 돌아가는 함수
 *              1. 쓰레드가 실행되면 짝수 번째 철학자는 0.5초 만큼 usleep 한다.
 *              2. 철학자가 한 명이라도 죽지 않았다면, 아래의 행동을 반복한다.
 *                 1) 생각한다. 포크를 집는다.
 *                 2) 밥을 먹는다.
 *                 3) 잠을 잔다.
 *                 break) 행동을 하다가 죽는 경우 반복문을 빠져나온다.
 * Param.   #1: 각 쓰레드별 철학자의 정보값들
 * Return     : 없음
 */
void	*run(void *arg)
{
	t_philosophers	*philosophers;

	philosophers = (t_philosophers *)arg;
	if (philosophers->number % 2 == 0)
		usleep(5000);
	while (philosophers->left_fork)
	{
		if (thinking_and_take_fork(philosophers))
			break ;
		if (take_eat(philosophers))
			break ;
		if (take_sleep(philosophers))
			break ;
	}
	return (NULL);
}

/*
 * Description: 쓰레드를 생성한다.
 *              1. 각각의 철학자들이 실행하는 스레드를 생성한다.
 * Param.   #1: 철학자들의 정보를 담고 있는 구조체
 * Return     : 없음
 */
void	run_philosophers(t_philo_info *philo_info)
{
	int			i;

	i = -1;
	while (++i < philo_info->number_of_philosophers)
	{
		pthread_create(&philo_info->philosophers[i].routine, NULL,
			run, &philo_info->philosophers[i]);
	}
}
