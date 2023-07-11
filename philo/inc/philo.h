/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 07:52:33 by mcutura           #+#    #+#             */
/*   Updated: 2023/07/11 15:19:14 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
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
# define PRINT_FORMAT	"%d %d %s\n"
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
#  define PRINT_FORMAT	"%6d %3d %s\n"
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
	FULL
};

typedef struct s_data
{
	int				philo_n;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_think;
	int				meals;
	int				full_philos;
	struct timeval	start;
	struct s_philo	*philo;
	pthread_mutex_t	write;
	pthread_mutex_t	bad_news;
	pthread_t		grim_reaper;
	int				sim_end;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				meals;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	right_fork;
	t_status		status;
	struct timeval	last_meal;
	t_data			*data;
	pthread_t		thread;
	pthread_mutex_t	hunger;
}	t_philo;

/* Utilities */
int		ft_isdigit(int c);
int		ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		get_elapsed_time(struct timeval start);
void	ft_memset(void *ptr, int c, size_t len);
int		ft_atoi(const char *nptr);
int		uint_check(char **tab);
void	ft_sleepms(int ms);
void	*ft_calloc(size_t nmemb, size_t size);

/* Error Handling */
int		error_handler(char *str, int (*f)(), void *arg);
int		free_data(t_data *data);

/* Init */
int		init_data(t_data *data, int ac, const char **av);
int		init_philo(t_data *data);
int		init_threads(t_data *data);

/* Philostyle */
void	*philo_life(void *philo);
int		forking(t_philo *p);
int		eating(t_philo *p);
int		sleeping(t_philo *p);
int		thinking(t_philo *p);
int		is_dead(t_philo *p);

/* Monitoring */
int		status_log(t_philo *p, char *msg);
void	*grim_reaper(void *data);

#endif