/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 21:39:16 by chanheki          #+#    #+#             */
/*   Updated: 2023/04/06 04:46:42 by chanheki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_in_mutex(t_philosophers *philosophers, char *str)
{
	pthread_mutex_lock(philosophers->mutex_print);
	printf("%lldms\t %d\t %s\n",
		get_timestamp(philosophers->philo_info),
		philosophers->number, str);
	pthread_mutex_unlock(philosophers->mutex_print);
}

void	take_fork(t_philosophers *philosophers)
{
	if (!philosophers->alive)
		return ;
	pthread_mutex_lock(philosophers->left_fork);
	print_in_mutex(philosophers, philosophers->philo_info->msg.take);
	if (philosophers->philo_info->end_flag
		|| philosophers->philo_info->number_of_philosophers == 1)
	{
		pthread_mutex_lock(philosophers->left_fork);
		philosophers->alive = FALSE;
		return ;
	}
	pthread_mutex_lock(philosophers->right_fork);
	print_in_mutex(philosophers, philosophers->philo_info->msg.take);
}

// void	take_eat(t_philosophers *philosophers)
// {
	
// }

// void	take_sleep(t_philosophers *philosophers)
// {
	
// }

// void	thinking(t_philosophers *philosophers)
// {
	
// }

void	*run(void *arg)
{
	t_philosophers	*philosophers;

	printf("run");
	philosophers = (t_philosophers *)arg;
	if (philosophers->number & 1)
		my_usleep(philosophers->philo_info->time_to_eat);
	while (!philosophers->philo_info->end_flag && (philosophers->left_fork))
	{
		take_fork(philosophers);
		// take_eat(philosophers);
		// take_sleep(philosophers);
		// thinking(philosophers);
	}
	return (NULL);
}

void	run_philosophers(t_philo_info *philo_info)
{
	int			i;
	pthread_t	monitoring_thread;

	i = -1;
	while (++i < philo_info->number_of_philosophers)
	{
		printf("%d", i);
		pthread_create(&philo_info->philosophers[i].routine, NULL,
			run, &philo_info->philosophers[i]);
		pthread_create(&monitoring_thread, NULL,
			run, &philo_info->philosophers[i]);
		pthread_detach(monitoring_thread);
	}
}

void	init_philosophers(t_philo_info *philo_info)
{
	int	i;

	pthread_mutex_init(&philo_info->mutex_print, NULL);
	pthread_mutex_init(&philo_info->during_routine, NULL);
	philo_info->philosophers = (t_philosophers *)malloc (sizeof(t_philosophers) \
									* philo_info->number_of_philosophers);
	philo_info->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) \
							* philo_info->number_of_philosophers);
	i = -1;
	while (++i < philo_info->number_of_philosophers)
	{
		pthread_mutex_init(&philo_info->philosophers[i].critical_section, NULL);
		pthread_mutex_init(&philo_info->forks[i], NULL);
		philo_info->philosophers[i].number = i + 1;
		philo_info->philosophers[i].number_of_times_eaten = 0;
		philo_info->philosophers[i].last_time_eaten = philo_info->borntocode;
		philo_info->philosophers[i].alive = TRUE;
		philo_info->philosophers[i].philo_info = philo_info;
		philo_info->philosophers[i].left_fork = &philo_info->forks[i];
		philo_info->philosophers[i].mutex_print = &philo_info->mutex_print;
		if (!i)
			philo_info->philosophers[i].right_fork = \
			&philo_info->forks[philo_info->number_of_philosophers - 1];
		else
			philo_info->philosophers[i].right_fork = &philo_info->forks[i - 1];
	}
}

int	init_philo_info(t_philo_info *philo_info, char **argv)
{
	int	validator;

	validator = 1;
	philo_info->number_of_philosophers = ft_atoll(&validator, argv[1]);
	philo_info->time_to_die = ft_atoll(&validator, argv[2]);
	philo_info->time_to_eat = ft_atoll(&validator, argv[3]);
	philo_info->time_to_sleep = ft_atoll(&validator, argv[4]);
	philo_info->borntocode = get_time();
	philo_info->end_flag = FALSE;
	if (argv[5])
		philo_info->number_of_must_eat = ft_atoll(&validator, argv[5]);
	else
		philo_info->number_of_must_eat = 0;
	philo_info->msg.think = "is thinking";
	philo_info->msg.eat = "is eating";
	philo_info->msg.sleep = "is sleeping";
	philo_info->msg.take = "has taken a fork";
	return (!validator);
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
	printf("Init thread\n"); // 철학자를 초기화한다.
	init_philosophers(&philo_info);

	printf("Create thread\n"); // 철학자를 생성한다.
	run_philosophers(&philo_info);
	
	printf("Enjoy dinner thread\n"); // 철학자를 밥먹이고 재우고 생각시킨다.
	
	return (0);
}

