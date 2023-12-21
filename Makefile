# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zwina <zwina@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/05 15:48:21 by zwina             #+#    #+#              #
#    Updated: 2022/03/05 15:48:26 by zwina            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:= fdf
CCWI			:= gcc -Wall -Wextra -Werror -Iincludes

OS := $(shell uname)
ifeq ($(OS), Linux)
MINILIBX_LINK := -lm -lz -lmlx_Linux -L./libs -lXext -lX11
else
MINILIBX_LINK := -lm -lmlx -framework OpenGL -framework AppKit
endif

SRCS_UTILITIES	:= src/utilities/fdf_utils_1.c \
				   src/utilities/fdf_utils_2.c \
				   src/utilities/ft_strlen.c \
				   src/utilities/ft_strncmp.c \
				   src/utilities/ft_split.c \
				   src/utilities/ft_putchar_fd.c \
				   src/utilities/ft_putstr_fd.c \
				   src/utilities/ft_putendl_fd.c \
				   src/utilities/ft_atoi.c \
				   src/utilities/ft_atoi_16.c \
				   src/utilities/ft_lstnew_bonus.c \
				   src/utilities/ft_lstadd_back_bonus.c \
				   src/utilities/ft_lstsize_bonus.c \
				   src/utilities/ft_lstlast_bonus.c
GET_NEXT_LINE	:= src/get_next_line/get_next_line.c \
				   src/get_next_line/get_next_line_utils.c
SRCS			:= $(GET_NEXT_LINE) \
				   $(SRCS_UTILITIES) \
				   src/check_errors.c \
				   src/fdf.c \
				   src/setup_the_map/get_map.c \
				   src/setup_the_map/setup_map.c \
				   src/run_the_fdf/draw_map.c \
				   src/run_the_fdf/run_fdf.c
SRCS_BO			:= $(GET_NEXT_LINE) \
				   $(SRCS_UTILITIES) \
				   src/check_errors.c \
				   src/fdf.c \
				   src/setup_the_map/get_map.c \
				   src/setup_the_map/setup_map.c \
				   src/run_the_fdf/draw_map.c \
				   src/run_the_fdf/run_fdf_bonus.c \
				   src/events_bonus/events.c \
				   src/events_bonus/events_utils1.c \
				   src/events_bonus/events_utils2.c
				   
OBJS			:= $(SRCS:src/%.c=bin/%.o)
OBJS_BO			:= $(SRCS_BO:src/%.c=bin/%.o)

LIBOBJ			:= bin/libs/libobj.a
LIBOBJ_LINK		:= -L./bin/libs -lobj
LIBOBJ_BO		:= bin/libs/libobj_bo.a
LIBOBJ_BO_LINK	:= -L./bin/libs -lobj_bo

### mandatory
all : $(NAME)

$(NAME) : bin $(LIBOBJ)
	@$(CCWI) $(LIBOBJ_LINK) $(MINILIBX_LINK) -o $(NAME)
	@printf "\e[38;5;220m\t ______   _____     ______ \
	\n\t/\  ___\ /\  __-.  /\  ___\ \
	\n\t\ \  __\ \ \ \/\ \ \ \  __\ \
	\n\t \ \_\    \ \____-  \ \_\   \
	\n\t  \/_/     \/____/   \/_/   is REDY.\e[0m\n"
	@rm -rf $(LIBOBJ_BO)

$(LIBOBJ) : $(OBJS)
	@ar -rsc $@ $^

### bonus
bonus : $(LIBOBJ_BO)

$(LIBOBJ_BO) : bin $(OBJS_BO)
	@ar -rsc $@ $(OBJS_BO)
	@$(CCWI) $(LIBOBJ_BO_LINK) $(MINILIBX_LINK) -o $(NAME)
	@printf "\e[38;5;220m\t ______   _____     ______ \
	\n\t/\  ___\ /\  __-.  /\  ___\ \
	\n\t\ \  __\ \ \ \/\ \ \ \  __\ \
	\n\t \ \_\    \ \____-  \ \_\   \
	\n\t  \/_/     \/____/   \/_/   ( B O N U S ) is REDY.\e[0m\n"
	@rm -rf $(LIBOBJ)

### objects
bin/%.o : src/%.c
	@$(CCWI) -c $< -o $@

bin :
	@mkdir bin
	@mkdir bin/get_next_line
	@mkdir bin/utilities
	@mkdir bin/setup_the_map
	@mkdir bin/run_the_fdf
	@mkdir bin/events_bonus
	@mkdir bin/libs
	@printf "\e[38;5;190m\t==>>directory of binaries is created.\e[0m\n"

### cleaning
clean :
	@rm -rf bin
	@printf "\e[38;5;190m\t==>>directory of binaries is cleaned.\e[0m\n"

fclean : clean
	@rm -f $(NAME)
	@printf "\e[38;5;127m\t ______   _____     ______ \
	\n\t/\  ___\ /\  __-.  /\  ___\ \
	\n\t\ \  __\ \ \ \/\ \ \ \  __\ \
	\n\t \ \_\    \ \____-  \ \_\   \
	\n\t  \/_/     \/____/   \/_/   is REMOVED.\e[0m\n"

re : fclean all

.PHONY : clean
