/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stagerace.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielm3 <danielm3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 11:49:43 by danielm3          #+#    #+#             */
/*   Updated: 2025/05/31 18:00:03 by danielm3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STAGERACE_H
# define STAGERACE_H

# include <stdlib.h>     // malloc, rand, srand
# include <stdio.h>      // printf
# include <sys/time.h>   // gettimeofday, struct timeval
# include <unistd.h>     // usleep
# include <pthread.h>    // pthread_create, join, mutex
# include <stdbool.h>    // bool, true, false

typedef struct s_race_data
{
	int				runner_num;
	int				stage_num;
	int				min_stage_time;
	int				max_stage_time;
	int				winner_id;
	bool			winner_declared;
	struct timeval	start_time;
	pthread_mutex_t	print_mutex;
}	t_race_data;

typedef struct s_runner_data
{
	int			id;
	int			stages_completed;
	t_race_data	*race;
}	t_runner_data;

#endif
