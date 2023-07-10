# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/10 05:43:22 by mcutura           #+#    #+#              #
#    Updated: 2023/07/10 05:49:57 by mcutura          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := philo_bonus
#--- DIRECTORIES ---
SRCDIR := src
INCDIR := inc
OBJDIR := obj
#--- SOURCES ---
_SRCS := main.c error_handler.c ft_atoi.c ft_sleepms.c uint_check.c utils.c \
		init.c philo.c philo_actions.c status_log.c
SRCS := $(addprefix $(SRCDIR)/, $(_SRCS))
#--- OBJECTS ---
OBJS := $(addprefix $(OBJDIR)/, $(_SRCS:.c=.o))
#--- HEADERS ---
HEADERS := $(addprefix $(INCDIR)/, philo_bonus.h)
#--- FLAGS ---
CC := cc
debug: CFLAGS := -Wall -Wextra -I$(INCDIR) -pthread -g -D DEBUG
colors: CFLAGS := -Wall -Wextra -I$(INCDIR) -pthread -D COLORS
CFLAGS := -Wall -Wextra -Werror -I$(INCDIR) -pthread
#--- COMMANDS ---
MKDIR := mkdir -p
RMDIR := rm -rf

.PHONY: all clean colors debug fclean re

all: $(NAME)

colors: re

debug: re

$(NAME): $(HEADERS) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	$(MKDIR) $(OBJDIR)

clean:
	$(RM) $(OBJS)
	$(RMDIR) $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all
