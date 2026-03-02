# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kyanagis <kyanagis@student.42tokyo.jp>     +#+  +:+       +#+        #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/13 02:05:00 by kyanagis          #+#    #+#              #
#    Updated: 2025/07/13 02:05:00 by kyanagis         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



NAME    := libft.a
CC      := cc
CFLAGS  := -Wall -Wextra -Werror -I.
AR      := ar rcs
RM      := rm -f

SRCS := \
ft_atof.c        ft_atoi.c         ft_bzero.c        ft_calloc.c      \
ft_isalnum.c     ft_isalpha.c      ft_isascii.c      ft_isdigit.c     \
ft_isprint.c     ft_itoa.c         ft_lstadd_back.c  ft_lstadd_front.c\
ft_lstclear.c    ft_lstdelone.c    ft_lstiter.c      ft_lstlast.c     \
ft_lstmap.c      ft_lstnew.c       ft_lstsize.c      ft_memchr.c      \
ft_memcmp.c      ft_memcpy.c       ft_memmove.c      ft_memset.c      \
ft_putchar_fd.c  ft_putendl_fd.c   ft_putnbr_fd.c    ft_putstr_fd.c   \
ft_split.c       ft_strchr.c       ft_strcmp.c       ft_strdup.c      \
ft_striteri.c    ft_strjoin.c      ft_strlcat.c      ft_strlcpy.c     \
ft_strlen.c      ft_strmapi.c      ft_strncmp.c      ft_strnstr.c     \
ft_strrchr.c     ft_strtrim.c      ft_substr.c       ft_tolower.c     \
ft_toupper.c                                                     \
ft_printf/ft_format.c ft_printf/ft_printf.c ft_printf/ft_utils.c

OBJS := $(SRCS:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
