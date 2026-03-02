# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kyanagis <kyanagis@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/03 06:35:02 by kyanagis          #+#    #+#              #
#    Updated: 2025/09/03 06:35:11 by kyanagis         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC      := cc
CFLAGS  := -Wall -Wextra -Werror -MMD -MP
AR      := ar
RM      := rm -rf


NAME    := pipex


OBJDIR          := obj
OBJDIR_BONUS := obj_bonus



INCFLAGS        := -Iinclude -Ilibft
INCFLAGS_BONUS  := -Iinclude_bonus -Ilibft


LIBFT_DIR := libft
LIBFT     := $(LIBFT_DIR)/libft.a

SRCS := \
src/main.c \
src/execute_pipeline.c \
src/init_pipex.c \
src/child/child_die.c \
src/child/child_exec.c \
src/child/child_io.c \
src/child/child_side.c \
src/lexer/handle_gen.c \
src/lexer/handle_lexer.c \
src/lexer/tokenize.c \
src/utils/exit_helper.c \
src/utils/utils.c

SRCS_BONUS := \
bonus/main_bonus.c \
bonus/execute_pipeline_bonus.c \
bonus/init_pipex_bonus.c \
bonus/here_doc_bonus.c \
bonus/child_bonus/child_die_bonus.c \
bonus/child_bonus/child_exec_bonus.c \
bonus/child_bonus/child_io_bonus.c \
bonus/child_bonus/child_side_bonus.c \
bonus/lexer_bonus/handle_gen_bonus.c \
bonus/lexer_bonus/handle_lexer_bonus.c \
bonus/lexer_bonus/tokenize_bonus.c \
bonus/utils_bonus/exit_helper_bonus.c \
bonus/utils_bonus/utils_bonus.c


OBJS       := $(SRCS:%=$(OBJDIR)/%.o)
OBJS_BONUS := $(SRCS_BONUS:%=$(OBJDIR_BONUS)/%.o)
DEPS       := $(OBJS:.o=.d)
DEPS_BONUS := $(OBJS_BONUS:.o=.d)

.PHONY: all bonus clean fclean re libft norm

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $@

bonus: $(LIBFT) $(OBJS_BONUS)
	$(CC) $(CFLAGS) $(OBJS_BONUS) $(LIBFT) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)


$(OBJDIR)/%.c.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCFLAGS) -c $< -o $@


$(OBJDIR_BONUS)/%.c.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCFLAGS_BONUS) -c $< -o $@

clean:
	$(RM) $(OBJDIR) $(OBJDIR_BONUS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(RM) $(LIBFT)

re: fclean all

