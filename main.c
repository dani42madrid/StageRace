/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielm3 <danielm3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 11:49:02 by danielm3          #+#    #+#             */
/*   Updated: 2025/05/31 17:59:38 by danielm3         ###   ########.fr       */
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
	racedata->winner_declared = false;
}

t_runner_data *create_runners_array(t_race_data *racedata)
{
	int				id;
	int				i;
	t_runner_data	*runners_array;

	i = 0;
	runners_array = (t_runner_data *)malloc(racedata->runner_num *
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
	int				stage_time_range;
	int				sleep_ms;
	long			elapsed_ms;
	int				i;

	runner = (t_runner_data *)arg;
	race = runner->race;
	stage_time_range = race->max_stage_time - race->min_stage_time + 1;
	i = 1;
	while (i <= race->stage_num)
	{
		sleep_ms = rand() % stage_time_range + race->min_stage_time;
		usleep(sleep_ms * 1000);
		gettimeofday(&now, NULL);
		pthread_mutex_lock(&race->print_mutex);
		elapsed_ms = (now.tv_sec - race->start_time.tv_sec) * 1000
				+ (now.tv_usec - race->start_time.tv_usec) / 1000;
		printf("[%ld] Runner %d finished stage %d\n",
				elapsed_ms, runner->id, i);
		if (i == race->stage_num && !race->winner_declared)
		{
			race->winner_declared = true;
			race->winner_id = runner->id;
			printf("Runner %d won\n", runner->id);
		}
		pthread_mutex_unlock(&race->print_mutex);
		i++;
	}
	return (NULL);
}
int	thread_launcher(t_race_data *racedata, t_runner_data *runners_array)
{
	pthread_t	*threads;
	int			i;

	threads = (pthread_t *)malloc(racedata->runner_num * sizeof(pthread_t));
	if (!threads)
		return (2);
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
	int				return_thread;
			
	racedata_init(&racedata, argv);
	pthread_mutex_init(&racedata.print_mutex, NULL);
	gettimeofday(&racedata.start_time, NULL);
	srand(racedata.start_time.tv_usec);
	return_thread = runners_array = create_runners_array(&racedata);
	if (!runners_array)
		return (1);
	thread_launcher(&racedata, runners_array);
	if (return_thread == 2)
		return (1);
	return (0);
}
