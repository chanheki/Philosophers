/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 21:41:19 by chanheki          #+#    #+#             */
/*   Updated: 2023/04/12 04:42:49 by chanheki         ###   ########.fr       */
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
	long long			number_of_times_eaten;
	long long			last_time_eaten;
	pthread_t			routine;
	pthread_mutex_t		critical_section;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	t_philo_info		*philo_info;
}	t_philosophers;

/* behavior */

bool		thinking_and_take_fork(t_philosophers *philosophers);
bool		take_eat(t_philosophers *philosophers);
bool		take_sleep(t_philosophers *philosophers);

/* philosophers */

void		*run(void *arg);
void		run_philosophers(t_philo_info *philo_info);

/************** utils begin **************/

/* initialize */

void		init_philosophers(t_philo_info *philo_info);
int			init_philo_info(t_philo_info *philo_info, char **argv);

/* print */

void		print_death(t_philosophers *philosophers);
bool		print_fork(t_philosophers *philosophers);
bool		print_eating(t_philosophers *philosophers);
bool		print_sleeping(t_philosophers *philosophers);
bool		print_thinking(t_philosophers *philosophers);

/* progress */

bool		check_run(t_philo_info *philo_info);
bool		check_all_done_eating(t_philo_info	*philo_info);
void		check_routine(t_philo_info *philo_info);
void		wait_for_end_of_routine(t_philo_info *philo_info);

/* util */

long long	get_timestamp(t_philo_info *philo_info);
long long	get_time(void);
void		my_usleep(long long duration);
long long	ft_atoll(int *validator, const char *str);

/************** utils end **************/
#endif