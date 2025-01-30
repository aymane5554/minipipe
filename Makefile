CC = cc
CFLAFS = -Wall -Wextra -Werror
SRCS = main.c init.c get_input.c utils.c
OBJS = $(SRCS:%.c=%.o)
NAME = pipe

all:$(NAME)

lib/libft/libft.a: include/libft.h include/get_next_line.h
	cd lib/libft && make all bonus && cd ../..

%.o : %.c include/pipe.h
	$(CC) $(CFLAGS) -I include/ -c $< -o $@

$(NAME) : $(OBJS) lib/libft/libft.a
	$(CC) $(CFLAFS) $(OBJS) -I include lib/libft/libft.a -o $(NAME)

clean:
	rm -f $(OBJS) && cd lib/libft && make clean && cd ../..

fclean: clean
	rm -f pipe lib/libft/libft.a

re: fclean all

.PHONY: clean