/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 21:39:16 by chanheki          #+#    #+#             */
/*   Updated: 2023/04/12 03:32:58 by chanheki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	check_routine(&philo_info);
	wait_for_end_of_routine(&philo_info);
	return (0);
}
