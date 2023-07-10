/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 03:57:21 by mcutura           #+#    #+#             */
/*   Updated: 2023/07/10 11:29:47 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <fcntl.h>
# include <semaphore.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <signal.h>
# include <string.h>
# include <limits.h>
# include <errno.h>

# define USAGE "Usage: \
	./philo NP TD TE TS [NE]\n \
	NP = number_of_philosophers\n \
	TD = time_to_die\n \
	TE = time_to_eat\n \
	TS = time_to_sleep\n \
	[NE] optional = [number_of_times_each_philosopher_must_eat]"
# define C_FORK			"has taken a fork"
# define C_EAT			"is eating"
# define C_SLEEP		"is sleeping"
# define C_THINK		"is thinking"
# define C_DIE			"died"
# define PRINT_FORMAT	"%6d %3d %s\n"
# ifdef DEBUG
#  ifdef COLORS
#   undef COLORS
#  endif
#  undef PRINT_FORMAT
#  define PRINT_FORMAT	"%d %d %s\n"
# endif
# ifdef COLORS
#  undef C_FORK
#  undef C_EAT
#  undef C_SLEEP
#  undef C_THINK
#  undef C_DIE
#  define C_FORK		"\033[33mhas taken a fork\033[0m"
#  define C_EAT			"\033[32mis eating\033[0m"
#  define C_SLEEP		"\033[36mis sleeping\033[0m"
#  define C_THINK		"\033[35mis thinking\033[0m"
#  define C_DIE			"\033[1m\033[4m\033[31mdied\033[0m"
# endif

# define MAX_INT_S	"2147483647"

# define TIME_TO_THINK		0

typedef struct s_philo	t_philo;
typedef struct s_data	t_data;
typedef enum e_status	t_status;

enum e_status
{
	READY,
	EATS,
	FULL,
	DEAD
};

struct s_philo
{
	int				id;
	int				meals;
	struct timeval	last_meal;
	struct timeval	start;
	t_status		status;
	t_data			*data;
	pid_t			pid;
	pthread_t		reaper;
	sem_t			*eat;
};

struct s_data
{
	int				philo_n;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_think;
	int				meals;
	struct timeval	start;
	struct s_philo	*philo;
	sem_t			*forks;
	sem_t			*write;
	sem_t			*bad_news;
	sem_t			*phullo;
};

/* Utilities */
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
int		ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_memset(void *ptr, int c, size_t len);
int		get_elapsed_time(struct timeval start);
void	ft_sleepms(int ms);
int		uint_check(char **tab);

/* Error Handling */
int		error_handler(char *msg, int (*f)(), void *arg);
int		destroy_semaphores(t_data *d);
int		shred_data(t_data *d);

/* Init */
int		init_data(t_data *d, int ac, char **av);
int		init_semaphores(t_data *d);
int		init_philos(t_data *d);


/* Philostyle */
void	philo_life(t_philo	*p);
int		philo_eat(t_philo *p);
int		philo_sleep(t_philo *p);
int		philo_think(t_philo *p);
int		philo_die(t_philo *p);
void	*nega_philo(void *arg);

/* Monitoring */
int		status_log(t_philo *p, char *msg);

#endif