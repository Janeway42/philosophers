/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_bonus.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 11:25:36 by cpopa         #+#    #+#                 */
/*   Updated: 2022/08/01 12:14:30 by cpopa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	check_digit(char *input, int *str)
{
	int		nr;
	size_t	lenght;
	char	*test;

	if (*input == '\0')
		return (ERROR);
	nr = ft_atoi(input);
	test = ft_itoa(nr);
	lenght = ft_strlen(input);
	if (test == NULL || ft_strncmp(input, test, lenght) != 0)
	{
		free(test);
		return (ERROR);
	}
	*str = nr;
	free(test);
	return (0);
}

static int	check_input(int argc, char **argv, t_data *data)
{
	if (argc < 5 || argc > 6)
		return (error("wrong number of arguments\n"));
	if (check_digit(argv[1], &data->nr_philo) != 0)
		return (error("odd party of philosophers there...\n"));
	if (check_digit(argv[2], &data->t_die) != 0)
		return (error("might want to check that time to die...\n"));
	if (check_digit(argv[3], &data->t_eat) != 0)
		return (error("must eat brains! lunch time is off!\n"));
	if (check_digit(argv[4], &data->t_sleep) != 0)
		return (error("put your glasses on and let me sleep!\n"));
	data->nr_rounds = -1;
	if (argc == 6)
	{
		if (check_digit(argv[5], &data->nr_rounds) != 0)
			return (error("don't be skimpy! let us eat more times!\n"));
	}
	if (data->nr_philo < 1 || data->t_die < 0 || data->t_eat < 0
		|| data->t_sleep < 0 || (argc == 6 && data->nr_rounds < 1))
		return (error(INPUT));
	return (OK);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (check_input(argc, argv, &data) == ERROR)
		return (ERROR);
	if (initialize_data(&data) == ERROR)
		return (ERROR);
	create_processes(&data);
	if (surveillance(&data) == ERROR)
		return (ERROR);
	clean_up(&data);
	return (OK);
}
