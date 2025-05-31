/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielm3 <danielm3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 11:49:02 by danielm3          #+#    #+#             */
/*   Updated: 2025/05/31 16:10:21 by danielm3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stagerace.h"

void	racedata_init(t_race_data *racedata, char **argv)
{
	(void) argv;
	racedata->runner_num = 5;
	racedata->stage_num = 3;
	racedata->min_stage_time = 100;
	racedata->max_stage_time = 500;
}

t_runner_data *create_runners_array(t_race_data *racedata)
{
	int				id;
	int				i;
	t_runner_data	*runners_array;

	i = 0;
	runners_array = (t_runner_data *)malloc(racedata.runner_num *
				sizeof(t_runner_data));
	if (!runners_array)
		return (NULL);
	while (i < racedata->runner_num)
	{
		runners_array[i].id = i + 1;
		runners_array[i].stages_completed = 0;
		runners_array[i].race = racedata;
		i++;
	}
	return (runners_array);
}

void	*runner_routine(void *arg)
{
	t_runner_data	*runner;
	t_race_data		*race;
	struct timeval	now;
		
	runner = (t_runner_data *)arg;
	race = runner->race; //shared race data
	gettimeofday(&now, NULL);
	
	
}


void	thread_launcher(t_race_data *racedata, t_runner_data *runners_array)
{
	pthread_t	*threads;
	int			i;

	threads = (pthread_t *)malloc(racedata->runner_num * sizeof(pthread_t));
	if (!threads)
		return (NULL);
	i = 0;
	while (i < racedata->runner_num)
	{
		pthread_create(&threads[i], NULL, runner_routine,
			 &runners_array[i]);
		i++;
	}
	
}

int	main(int argc, char **argv)
{
	t_race_data 	racedata;
	t_runner_data	*runners_array;
			
	racedata_init(&racedata, argv);
	pthread_mutex_init(&racedata.print_mutex, NULL);
	gettimeofday(&racedata.start_time, NULL);
	srand(racedata.start_time.tv_usec);
	runners_array = create_runners_array(&racedata);
	if (!runners_array)
		return (1);
	thread_launcher(&racedata, runners_array);
	return (0);
}
