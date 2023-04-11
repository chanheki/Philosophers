/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 20:10:27 by chanheki          #+#    #+#             */
/*   Updated: 2023/04/12 01:13:47 by chanheki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/*
 * Description: philosophers에게 포크를 쥐어준다.
 *              1. 왼손에 n의 포크를 쥔다.
 *              2. 오른손에 n-1의 포크를 쥔다.
 *              3. 첫번째 철학자의 오른손에는 마지막 철학자의 포크를쥔다.
 * Param.   #1: t_philo_info 구조체의 포인터
 *          #2: 철학자 번호 i
 * Return     : 없음
 */
static void	_hold_fork(t_philo_info *philo_info, int i)
{	
	philo_info->philosophers[i].left_fork = &philo_info->forks[i];
	if (!i)
		philo_info->philosophers[i].right_fork = \
		&philo_info->forks[philo_info->number_of_philosophers - 1];
	else
		philo_info->philosophers[i].right_fork = &philo_info->forks[i - 1];
}

/*
 * Description: philosophers를 초기화 한다.
 *              1. print용 뮤텍스와 행동하고있는 중이라는 mutex를 초기화한다.
 *              2. philo_info 내 philosophers와 forks를 동적할당한다.
 *              3. 각 philosophers의 critical_section을 mutex로 초기화한다.
 *              4. 각 philo_info의 각 fork를 mutex로 초기화한다.
 *              5. 각 philosophers의 남은 멤버 변수를 초기화한다.
 * Param.   #1: t_philo_info 구조체의 포인터
 * Return     : 없음
 */
void	init_philosophers(t_philo_info *philo_info)
{
	int	i;

	pthread_mutex_init(&philo_info->during_routine, NULL);
	philo_info->philosophers = (t_philosophers *)malloc(
			sizeof(t_philosophers) * philo_info->number_of_philosophers);
	philo_info->forks = (pthread_mutex_t *)malloc(
			sizeof(pthread_mutex_t) * philo_info->number_of_philosophers);
	i = -1;
	while (++i < philo_info->number_of_philosophers)
	{
		pthread_mutex_init(&philo_info->philosophers[i].critical_section, NULL);
		pthread_mutex_init(&philo_info->forks[i], NULL);
		philo_info->philosophers[i].number = i + 1;
		philo_info->philosophers[i].number_of_times_eaten = 0;
		philo_info->philosophers[i].last_time_eaten = philo_info->borntocode;
		philo_info->philosophers[i].philo_info = philo_info;
		_hold_fork(philo_info, i);
	}
}

/*
 * Description: philo_info를 초기화 한다.
 *              예외처리 변수를 두어 info를 초기화할 때 같이 예외처리를 해준다.
 *              이때, forks와 philosophers는 init_philosophers 초기화한다.
 *              5번째 인자가 없을 경우, number_of_must_eat은 0으로 초기화한다.
 * Param.   #1: t_philo_info 구조체의 포인터
 * Param.   #2: 입력받은 인자들의 배열
 * Return     : 예외처리 결과 값.
 *              = validator값이 0이면 예외 상황 (입력 값들 중 하나라도 음수값 혹은 0인 경우)
 */
int	init_philo_info(t_philo_info *philo_info, char **argv)
{
	int	validator;

	validator = 1;
	philo_info->number_of_philosophers = ft_atoll(&validator, argv[1]);
	philo_info->time_to_die = ft_atoll(&validator, argv[2]);
	philo_info->time_to_eat = ft_atoll(&validator, argv[3]);
	philo_info->time_to_sleep = ft_atoll(&validator, argv[4]);
	philo_info->borntocode = get_time();
	philo_info->end_flag = false;
	if (argv[5])
		philo_info->number_of_must_eat = ft_atoll(&validator, argv[5]);
	else
		philo_info->number_of_must_eat = 0;
	return (!validator);
}
