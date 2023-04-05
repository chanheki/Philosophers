/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 21:41:19 by chanheki          #+#    #+#             */
/*   Updated: 2023/04/06 04:42:49 by chanheki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>

# define TRUE	1
# define FALSE	0

typedef struct s_msg
{
	char	*think;
	char	*take;
	char	*eat;
	char	*sleep;
}	t_msg;

typedef struct s_philosophers
{
	int					number;
	int					number_of_times_eaten;
	long long			last_time_eaten;
	int					alive;
	pthread_t			routine;
	pthread_mutex_t		critical_section;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		*mutex_print;
	struct s_philo_info	*philo_info;
}	t_philosophers;

typedef struct s_philo_info
{
	long long		number_of_philosophers;
	long long		number_of_must_eat;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	long long		borntocode;
	int				end_flag;
	t_msg			msg;
	pthread_mutex_t	*forks;
	pthread_mutex_t	mutex_print;
	pthread_mutex_t	during_routine;
	t_philosophers	*philosophers;
}	t_philo_info;


long long	ft_atoll(int *validator, const char *str);
long long	get_time(void);
long long	get_timestamp(t_philo_info *philo_info);
void	my_usleep(long long duration);

#endif