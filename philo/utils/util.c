/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 21:52:59 by chanheki          #+#    #+#             */
/*   Updated: 2023/04/08 22:56:52 by chanheki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/*
 * Description: 철학자들의 죽음을 출력한다.
 * Param.   #1: 철학자들의 정보를 담고 있는 구조체
 * Return     : 없음
 */
void	print_death(t_philosophers *philosophers)
{
	if (philosophers->philo_info->end_flag)
		return ;
	pthread_mutex_lock(&philosophers->philo_info->mutex_print);
	printf("%lld %d died\n",
		get_time() - philosophers->philo_info->borntocode,
		philosophers->number);
	pthread_mutex_unlock(&philosophers->philo_info->mutex_print);
	philosophers->philo_info->end_flag = true;
	philosophers->alive = false;
}

/*
 * Description: 철학자들의 행동을 출력한다.
 * Param.   #1: 철학자들의 정보를 담고 있는 구조체
 *          #2: 출력할 문자열
 * Return     : 없음
 */
void	print_in_mutex(t_philosophers *philosophers, char *str)
{
	if (philosophers->philo_info->end_flag)
		return ;
	pthread_mutex_lock(&philosophers->philo_info->mutex_print);
	printf("%lld %d %s\n",
		get_time() - philosophers->philo_info->borntocode,
		philosophers->number, str);
	pthread_mutex_unlock(&philosophers->philo_info->mutex_print);
}

/*
 * Description: 현재 시각을 밀리초 단위로 변환 한다.
 * Param.     : 없음
 * Return     : 밀리초 단위의 시각
 *              = (초 단위 * 1000) + (마이크로초 단위 / 1000)
 */
long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

/*
 * Description: 주어진 시간 만큼 usleep을 한다.
 * Param.   #1: usleep을 하는 데 걸리는 시간
 * Return     : 없음
 */
void	my_usleep(long long duration)
{
	long long	now;

	now = get_time();
	while (get_time() < duration + now)
		usleep(100);
}

/*
 * Description: 입력 받고 예외처리 플래그를 세운다.
 *              1. long long 타입으로 입력을 받는다.
 *              2. - 입력이 들어오면 validator을 &연산으로 0으로 초기화.
 *              3. 0 입력이 들어오지 않을 때만 validator를 ll로 
 * Param.   #1: validator
 *          #2: 입력 문자열
 * Return     : str to long long
 */
long long	ft_atoll(int *validator, const char *str)
{
	long long	ll;
	int			i;

	ll = 0;
	i = 0;
	while ((*(str + i) >= 9 && *(str + i) <= 13) || *(str + i) == 32)
		i++;
	if (*(str + i) == '-' || *(str + i) == '+')
	{
		if (*(str + i) == '-')
			*validator &= 0;
		i++;
	}
	while (*(str + i) >= '0' && *(str + i) <= '9')
	{
		ll = ll * 10 + (*(str + i) - '0');
		i++;
	}
	if (!ll || (*validator && ll))
		*validator = ll;
	return (ll);
}
