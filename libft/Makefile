# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llelievr <llelievr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/07 14:49:27 by llelievr          #+#    #+#              #
#    Updated: 2019/01/09 15:14:08 by llelievr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include src.mk

CC = gcc
NAME =libft.a
CFLAGS=-Wall -Werror -Wextra -I ./includes -flto -O3 -ffast-math
OBJ=$(addprefix $(OBJDIR),$(SRC:.c=.o))

SRCDIR	=./srcs/
INCDIR	=./includes/
OBJDIR	=./objs/

ERR="\e[1;31m"
SUCCESS="\e[1;32m"
WARN="\e[1;33m"
INFO="\e[1;36m"
RESET="\e[1;0m"

all: $(NAME)

$(NAME): $(OBJ)
	@printf $(INFO)"CREATING LIBRARY ($(NAME)) "$(RESET)"\n"
	@ar cr $(NAME) $(OBJ)

$(OBJDIR)%.o: $(SRCDIR)%.c
	@if [ ! -d $(dir $@) ]; then mkdir -p $(dir $@); fi
	@printf "%s" $<
	@$(CC) $(CFLAGS) -c -o $@ $<
	@printf "%*s\e[1;36m%s\e[1;0m]\n" $$((80 - $(shell echo $< | awk '{print length}'))) "[" "DONE"

dev: CFLAGS += -g
dev: re

clean:
	@echo "Cleaning objs"
	@rm -rf $(OBJDIR)

fclean: clean
	@echo "Cleaning library"
	@rm -f $(NAME)

get_files:
	$(shell find srcs -type f | sed 's/srcs\///g' | sed 's/^/SRC+=/' > src.mk)

re: fclean all

.PHONY: all clean fclean re
