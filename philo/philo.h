/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 21:41:19 by chanheki          #+#    #+#             */
/*   Updated: 2023/04/08 22:41:10 by chanheki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>

typedef struct s_philo_info
{
	long long				number_of_philosophers;
	long long				number_of_must_eat;
	long long				time_to_die;
	long long				time_to_eat;
	long long				time_to_sleep;
	long long				borntocode;
	bool					end_flag;
	pthread_mutex_t			during_routine;
	pthread_mutex_t			*forks;
	struct s_philosophers	*philosophers;
}	t_philo_info;

typedef struct s_philosophers
{
	int					number;
	int					number_of_times_eaten;
	long long			last_time_eaten;
	bool				alive;
	pthread_t			routine;
	pthread_mutex_t		critical_section;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	t_philo_info	*philo_info;
}	t_philosophers;

/* utils */
long long	get_timestamp(t_philo_info *philo_info);
long long	get_time(void);
void		my_usleep(long long duration);
long long	ft_atoll(int *validator, const char *str);
void		print_in_mutex(t_philosophers *philosophers, char *str);
void		print_death(t_philosophers *philosophers);

/* initialize */
void		init_philosophers(t_philo_info *philo_info);
int			init_philo_info(t_philo_info *philo_info, char **argv);

/* philosophers */
void		*run(void *arg);
void		*check_run(void *arg);
void		*check_all_done_eating(void *arg);
void		run_philosophers(t_philo_info *philo_info);

/* behavior */
void		thinking_and_take_fork(t_philosophers *philosophers);
void		take_eat(t_philosophers *philosophers);
void		take_sleep(t_philosophers *philosophers);

/* print */
void		print_death(t_philosophers *philosophers);
void		print_fork(t_philosophers *philosophers);
void		print_eating(t_philosophers *philosophers);
void		print_sleeping(t_philosophers *philosophers);
void		print_thinking(t_philosophers *philosophers);

#endif