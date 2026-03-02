NAME := push_swap

CC := cc
CFLAGS := -Wall -Wextra -Werror
CPPFLAGS := -Iinclude -Ilibft/include

LIBFT_DIR := libft
LIBFT_A := $(LIBFT_DIR)/libft.a

SRC_DIR      := src
ORDER_DIR    := $(SRC_DIR)/order
THREE_DIR    := $(SRC_DIR)/sort_three
FIVE_IDA_DIR := $(SRC_DIR)/sort_five_ida
LARGE_DIR    := $(SRC_DIR)/sort_large
UTILS_DIR    := $(SRC_DIR)/utils

FILES_ROOT  := push_swap.c \
			   parse.c LIS.c

FILES_ORDER := push.c \
			   swap.c \
			   rotate.c \
			   reverse_rotate.c

FILES_UTILS := free_utils.c \
			   ft_split_ws.c \
			   node_utils.c \
			   zero_keep.c

FILES_THREE := sort_three.c

FILES_FIVE  := ida_dfs.c \
			   ida_ops.c \
			   ida_star.c \
			   ida_utils.c \
			   sort_five.c
			   
FILES_LARGE := compute_best_from_b.c \
			   coord_compress.c \
			   insert_cost.c \
			   insert_utils.c \
			   large_core_utils.c \
			   large_rotate.c \
			   lis_seed.c \
			   push_nonlis.c \
			   sort_large.c 

SRCS := \
  $(addprefix $(SRC_DIR)/,$(FILES_ROOT)) \
  $(addprefix $(ORDER_DIR)/,$(FILES_ORDER)) \
  $(addprefix $(THREE_DIR)/,$(FILES_THREE)) \
  $(addprefix $(FIVE_IDA_DIR)/,$(FILES_FIVE)) \
  $(addprefix $(LARGE_DIR)/,$(FILES_LARGE)) \
  $(addprefix $(UTILS_DIR)/,$(FILES_UTILS))

INC_DIR        := include
LIBFT_INC_DIR  := libft/include
PRINTF_INC_DIR := libft/ft_printf


OBJDIR := obj
OBJS   := $(patsubst %.c,$(OBJDIR)/%.o,$(SRCS))

all: $(NAME)

$(NAME): $(LIBFT_A) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_A) -o $@

$(LIBFT_A):
	$(MAKE) -C $(LIBFT_DIR)

$(OBJDIR)/%.o: %.c 
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(OBJDIR)

fclean:
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -rf $(OBJDIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re


