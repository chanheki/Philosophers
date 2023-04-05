/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 21:52:59 by chanheki          #+#    #+#             */
/*   Updated: 2023/04/06 04:46:43 by chanheki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long long	get_timestamp(t_philo_info *philo_info)
{
	return (get_time() - philo_info->borntocode);
}

long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	my_usleep(long long duration)
{
	long long	now;

	now = get_time();
	while (get_time() < duration + now)
		usleep(1);
}

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
