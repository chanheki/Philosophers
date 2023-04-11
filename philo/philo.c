/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 21:39:16 by chanheki          #+#    #+#             */
/*   Updated: 2023/04/08 22:58:05 by chanheki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 * Description: 철학자들이 루틴을 수행하는 동안 메인 스레드를 대기시키고,
 *              루틴이 끝나면 critical_section을 해제한다.
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

int	main(int argc, char **argv)
{
	t_philo_info	philo_info;

	if (argc < 5 || 6 < argc)
	{
		printf("Wrong Argument Count\n");
		return (1);
	}
	if (init_philo_info(&philo_info, argv))
	{
		printf("Wrong Argument\n");
		return (1);
	}
	init_philosophers(&philo_info);
	run_philosophers(&philo_info);
	wait_for_end_of_routine(&philo_info);
	return (0);
}
