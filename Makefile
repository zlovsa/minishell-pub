# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcarolee <mcarolee@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/07 19:13:40 by mcarolee          #+#    #+#              #
#    Updated: 2021/04/23 00:34:05 by mcarolee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_FILES	= minishell.c ft_echo.c ft_env.c ft_pwd.c list.c parsecmd.c \
				ft_exit.c ft_cd.c ft_unset.c ft_export.c \
				redirections.c signals.c args.c lexic.c utility.c \
				findexec.c exec.c inoutpipe.c

NAME	= minishell

CC		= gcc
RM		= rm -f

CFLAGS	= -Wall -Wextra -Werror
LFLAGS	= -L libft -lft

LFTDIR = ./libft/
INCLUDES_DIR = ./incl
SRCS_DIR = ./srcs
OBJS_DIR = ./objs

SRCS = $(addprefix $(SRCS_DIR)/, $(SRC_FILES))
OBJS = $(patsubst $(SRCS_DIR)/%.c,$(OBJS_DIR)/%.o, $(SRCS))
DEPS = $(OBJS:.o=.d)

LFT = $(LFTDIR)libft.a

all:		$(NAME)

-include $(DEPS)
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDES_DIR) -I$(LFTDIR) -MMD -MP -c -o $@ $<

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

$(NAME):	$(OBJS)
			make -C $(LFTDIR)
			$(CC) -g $(CFLAGS) $(LFLAGS) -I$(INCLUDES_DIR) -I$(LFTDIR) -MMD -MP -ltermcap -o $(NAME) $(OBJS)

clean:
			if [ -d "$(OBJS_DIR)" ]; then rm -rfv $(OBJS_DIR); fi
			make clean -C $(LFTDIR)

fclean:		clean
			if [ -f "$(NAME)" ]; then rm -rfv $(NAME); fi
			make fclean -C $(LFTDIR)
			
re:			fclean all

.PHONY:		all clean fclean re