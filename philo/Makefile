NAME		=	philo

CC			=	cc

FLAG		=	-Wall -Wextra -Werror -g3

C_FILE		= srcs/philo.c srcs/utils.c srcs/parse.c  srcs/init.c srcs/protected.c \
			srcs/attribute_manager.c srcs/routine.c  srcs/utils2.c srcs/monitor.c


OBJS		=	$(C_FILE:.c=.o)


.c.o:
	@printf "\r\033[K[philo] \033[0;32mBuilding : $<\033[0m\n"
	@$(CC) $(FLAG) -c $< -o $@

all:	$(NAME)


$(NAME): $(OBJS)
	@printf "\r\033[K[philo] \033[0;32mLinking...\033[0m"
	@$(CC) $(OBJS) -o $(NAME) -lm -lpthread
	@printf "\r\033[K[philo] \033[0;32mDone!\033[0m\n"

clean:
	@rm -f $(OBJS) 
	@printf "[philo] \033[1;31mCleaned .o!\033[0m\n"

fclean: clean
	@rm -f $(NAME) $(OBJS)
	@printf "[philo] \033[1;31mCleaned all!\033[0m\n"

re: fclean all

.PHONY: all clean fclean re