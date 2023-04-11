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
 * Description: 철학자가 돌아가는 함수
 *              1. 쓰레드가 실행되면 짝수 번째 철학자는 (밥 먹는 시간 * 1000)밀리초 만큼 usleep 한다.
 *              2. 철학자가 한 명이라도 죽지 않았다면, 아래의 행동을 반복한다.
 *                 1) 포크를 집는다.
 *                 2) 밥을 먹는다.
 *                 3) 잠을 잔다.
 *                 4) 생각한다.
 * Param.   #1: 각 쓰레드별 철학자의 정보값들
 * Return     : 없음
 */
void	*run(void *arg)
{
	t_philosophers	*philosophers;

	philosophers = (t_philosophers *)arg;
	if (philosophers->number % 2 == 0)
		my_usleep(philosophers->philo_info->time_to_eat);
	while (!philosophers->philo_info->end_flag && (philosophers->left_fork))
	{
		thinking_and_take_fork(philosophers);
		take_eat(philosophers);
		take_sleep(philosophers);
	}
	return (NULL);
}

/*
 * Description: 철학자들이 살아있는지 확인한다.
 *              철학자들이 한 명이라도 죽지 않았다면, 아래의 과정을 반복한다.
 *              1. 철학자 한 명만 접근할 수 있는 영역을 잠근다.
 *              2. 철학자들의 루틴 영역을 잠근다.
 *              3. 마지막으로 밥을 먹은 시간과 현재 시간을 비교하여, 철학자가 죽었는지 확인한다.
 *                 1) 만약 죽었다면, 철학자가 죽었다는 메시지를 출력하며 philo_info의 값을 바꾼다.
 *              4. 철학자 한 명만 접근할 수 있는 영역을 잠금 해제한다.
 *              5. 철학자들의 루틴 영역을 잠금 해제한다.
 * Param.   #1: 철학자들의 정보를 담고 있는 구조체
 * Return     : 없음
 */
void	*check_run(void *arg)
{
	t_philosophers	*philosophers;
	long long		after_eating;

	philosophers = (t_philosophers *)arg;
	while (!philosophers->philo_info->end_flag)
	{
		pthread_mutex_lock(&philosophers->critical_section);
		after_eating = get_time() - philosophers->last_time_eaten;
		if (after_eating >= philosophers->philo_info->time_to_die)
			print_death(philosophers);
		pthread_mutex_unlock(&philosophers->critical_section);
	}
	return (NULL);
}

/*
 * Description: 철학자들이 반드시 밥을 먹어야 하는 횟수만큼 먹었는지 확인한다.
 *              1. 철학자들의 루틴 영역을 잠근다.
 *              2. 각각의 철학자들이 반드시 밥을 먹어야 하는 횟수만큼 먹었다면 반복문을 진행한다.
 *                 1) 만약 반드시 밥을 먹어야 하는 횟수만큼 먹지 않았다면 반복문을 종료한다.
 *              3. 반드시 밥을 먹어야 하는 횟수만큼 밥을 먹은 철학자의 수가 전체 철학자의 수와 같다면,
 *                 philo_info의 is_end값을 true로 바꾼다.
 *              4. 철학자들의 루틴 영역을 잠금 해제한다.
 * Param.   #1: 철학자들의 정보를 담고 있는 구조체
 * Return     : 없음
 */
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
