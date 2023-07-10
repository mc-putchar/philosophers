# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/16 08:43:01 by mcutura           #+#    #+#              #
#    Updated: 2023/07/10 03:59:37 by mcutura          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := philo
#--- DIRECTORIES ---
SRCDIR := src
INCDIR := inc
OBJDIR := obj
#--- SOURCES ---
_SRCS := main.c error_handler.c init.c utils.c philo.c status_log.c \
	uint_check.c ft_atoi.c ft_sleepms.c grim_reaper.c states.c ft_calloc.c
SRCS := $(addprefix $(SRCDIR)/, $(_SRCS))
#--- OBJECTS ---
OBJS := $(addprefix $(OBJDIR)/, $(_SRCS:.c=.o))
#--- HEADERS ---
HEADERS := $(INCDIR)/philo.h
#--- FLAGS ---
CC := cc
debug: CFLAGS := -Wall -Wextra -I$(INCDIR) -pthread -g -D DEBUG
colors: CFLAGS := -Wall -Wextra -I$(INCDIR) -pthread -D COLORS
CFLAGS := -Wall -Wextra -Werror -I$(INCDIR) -pthread

.PHONY: all clean colors debug fclean re

all: $(NAME)

colors: re

debug: re

$(NAME): $(HEADERS) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	$(RM) $(OBJS)
	$(RM) -r $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all
