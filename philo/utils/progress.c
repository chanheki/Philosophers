/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   progress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 03:26:58 by chanheki          #+#    #+#             */
/*   Updated: 2023/04/12 04:43:33 by chanheki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/*
 * Description: 철학자들이 전부 살아있는지 확인한다.
 * Param.   #1: 철학자들의 정보를 담고 있는 구조체
 * Return     : 없음
 */
bool	check_run(t_philo_info *philo_info)
{
	long long	after_eating;
	long long	now;
	int			i;

	i = -1;
	while (++i < philo_info->number_of_philosophers)
	{
		now = get_time();
		pthread_mutex_lock(&philo_info->philosophers->critical_section);
		after_eating = now - philo_info->philosophers[i].last_time_eaten;
		if (after_eating < philo_info->time_to_die)
			break ;
		print_death(&philo_info->philosophers[i]);
		pthread_mutex_unlock(&philo_info->philosophers->critical_section);
		return (true);
	}
	pthread_mutex_unlock(&philo_info->philosophers->critical_section);
	return (false);
}

/*
 * Description: 철학자들이 반드시 밥을 먹어야 하는 횟수만큼 먹었는지 전부 확인한다.
 * Param.   #1: 철학자들의 정보를 담고 있는 구조체
 * Return     : 없음
 */
bool	check_all_done_eating(t_philo_info	*philo_info)
{
	int	i;

	i = -1;
	while (++i < philo_info->number_of_philosophers)
	{
		pthread_mutex_lock(&philo_info->philosophers->critical_section);
		if (philo_info->philosophers[i].number_of_times_eaten
			<= philo_info->number_of_must_eat)
			break ;
		pthread_mutex_unlock(&philo_info->philosophers->critical_section);
		pthread_mutex_lock(&philo_info->during_routine);
		philo_info->end_flag = true;
		pthread_mutex_unlock(&philo_info->during_routine);
		return (true);
	}
	pthread_mutex_unlock(&philo_info->philosophers->critical_section);
	return (false);
}

/*
 * Description: 철학자들이 루틴을 수행하는 동안 메인 스레드에서 철학자들을 감시한다.
 *              철학자의 must eat이 있으면 전부 다 먹었는지 검사한다.
 *              다먹었으면 while문에서 빠져나간다.
 *              혹은 철학자가 하나라도 죽으면 while문에서 빠져나간다.
 * Param.   #1: t_philo_info 구조체의 포인터
 * Return     : 없음
 */
void	check_routine(t_philo_info *philo_info)
{
	while (true)
	{
		if (philo_info->number_of_must_eat != 0)
		{
			if (check_all_done_eating(philo_info))
				break ;
		}
		if (check_run(philo_info))
			break ;
	}
}

/*
 * Description: 철학자가 죽으면 루틴들이 끝날때 까지 join으로 기다리고,
 *              기다림이 끝나면 critical_section을 해제한다.
 *              모든 철학자들의 루틴이 끝나면, 철학자들을 free하고, 포크를 해제한 후 free한다.
 * Param.   #1: t_philo_info 구조체의 포인터
 * Return     : 없음
 */
void	wait_for_end_of_routine(t_philo_info *philo_info)
{
	int	i;

	i = -1;
	while (++i < philo_info->number_of_philosophers)
	{
		pthread_join(philo_info->philosophers[i].routine, NULL);
		pthread_mutex_destroy(&philo_info->philosophers[i].critical_section);
	}
	free(philo_info->philosophers);
	i = -1;
	while (++i < philo_info->number_of_philosophers)
		pthread_mutex_destroy(&philo_info->forks[i]);
	free(philo_info->forks);
}
