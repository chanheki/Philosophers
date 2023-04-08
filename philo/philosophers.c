/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 20:53:04 by chanheki          #+#    #+#             */
/*   Updated: 2023/04/08 22:58:05 by chanheki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 * Description: 철학자가 일생을 살아가는 함수
 *              1. 홀수 번째 철학자는 (밥 먹는 시간 * 1000)밀리초 만큼 usleep 한다.
 *              2. 철학자가 한 명이라도 죽지 않았다면, 아래의 행동을 반복한다.
 *                 1) 포크를 집는다.
 *                 2) 밥을 먹는다.
 *                 3) 잠을 잔다.
 *                 4) 생각한다.
 * Param.   #1: 철학자들의 정보를 담고 있는 구조체
 * Return     : 없음
 */
void	*run(void *arg)
{
	t_philosophers	*philosophers;

	philosophers = (t_philosophers *)arg;
	if (philosophers->number & 1)
		my_usleep(philosophers->philo_info->time_to_eat);
	while (!philosophers->philo_info->end_flag && (philosophers->left_fork))
	{
		take_fork(philosophers);
		take_eat(philosophers);
		take_sleep(philosophers);
		thinking(philosophers);
	}
	return (NULL);
}

void	*check_run(void *arg)
{
	t_philosophers	*philosophers;
	long long		after_eating;

	philosophers = (t_philosophers *)arg;
	while (!philosophers->philo_info->end_flag)
	{
		pthread_mutex_lock(&philosophers->critical_section);
		pthread_mutex_lock(&philosophers->philo_info->during_routine);
		after_eating = get_time() - philosophers->last_time_eaten;
		if (after_eating >= philosophers->philo_info->time_to_die)
			print_death(philosophers);
		pthread_mutex_unlock(&philosophers->critical_section);
		pthread_mutex_unlock(&philosophers->philo_info->during_routine);
	}
	return (NULL);
}

void	*check_all_done_eating(void *arg)
{
	t_philo_info	*philo_info;
	int				i;

	philo_info = ((t_philosophers *)arg)->philo_info;
	while (!philo_info->end_flag)
	{
		pthread_mutex_lock(&philo_info->during_routine);
		i = -1;
		while (++i < philo_info->number_of_philosophers)
		{
			if (philo_info->philosophers[i].number_of_times_eaten
				< philo_info->number_of_must_eat)
				break ;
			if (!philo_info->philosophers->alive)
			{
				philo_info->end_flag = true;
				break ;
			}
		}
		if (i == philo_info->number_of_philosophers)
			philo_info->end_flag = true;
		pthread_mutex_unlock(&philo_info->during_routine);
	}
	return (NULL);
}

/*
 * Description: 쓰레드를 생성한다.
 *              1. 각각의 철학자들이 실행하는 스레드를 생성한다.
 *              2. 각각의 철학자들을 체크하는 스레드를 생성한다.
 *              3. 1~2의 과정을 철학자의 수만큼 반복한 후, 만약 철학자가 반드시 먹어야 하는 식사의 수가 정해져 있다면,
 *                 철학자들이 모두 해당 수만큼 식사를 했는지 확인하는 스레드를 생성한다.
 * Param.   #1: 철학자들의 정보를 담고 있는 구조체
 * Return     : 없음
 */
void	run_philosophers(t_philo_info *philo_info)
{
	int			i;
	pthread_t	monitoring_thread;

	i = -1;
	while (++i < philo_info->number_of_philosophers)
	{
		pthread_create(&philo_info->philosophers[i].routine, NULL,
			run, &philo_info->philosophers[i]);
		pthread_create(&monitoring_thread, NULL,
			check_run, &philo_info->philosophers[i]);
		pthread_detach(monitoring_thread);
	}
	if (!philo_info->end_flag && philo_info->number_of_must_eat)
	{
		pthread_create(&monitoring_thread, NULL,
			check_all_done_eating, philo_info->philosophers);
		pthread_detach(monitoring_thread);
	}
}
