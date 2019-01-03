# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llelievr <llelievr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/07 14:49:27 by llelievr          #+#    #+#              #
#    Updated: 2019/01/03 14:55:02 by llelievr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include src.mk

NAME	= fillit
OBJ		=$(addprefix $(OBJDIR),$(SRC:.c=.o))

# compiler
CC        =gcc
CFLAGS    =-Wall -Werror -Wextra

# ft library
FT        =./libft
FT_LIB    =$(addprefix $(FT), libft.a)
FT_INC    =-I ./libft/includes
FT_LNK    =-L ./libft -lft
FT_TASK =

# directories
SRCDIR    =./srcs/
INCDIR    =./includes/
OBJDIR    =./objs/

all: $(FT_LIB) $(NAME)

dev: CFLAGS =-g
dev: FT_TASK = dev 
dev: re

$(OBJDIR)%.o: $(SRCDIR)%.c
	@if [ ! -d $(dir $@) ]; then mkdir -p $(dir $@); fi
	$(CC) $(CFLAGS) $(FT_INC) -I $(INCDIR) -o $@ -c $<

$(FT_LIB):
	make -j4 -C $(FT)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(FT_LNK) -o $(NAME)

clean:
	rm -rf $(OBJDIR)
	make -C $(FT) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(FT) fclean

get_files:
	$(shell find srcs -type f | sed 's/srcs\///g' | sed 's/^/SRC+=/' > src.mk)

re: fclean all
