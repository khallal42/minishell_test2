NAME = minishell
COM = gcc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -fsanitize=undefined -fsanitize=null -g3

RM = rm -rf
LIBFT = libft/libft.a

FUN=	main.c	\
		expande.c	\
		err_msg.c	\
		break_cmd.c	\
		ft_list.c	\
		divide_vers_2.c	\
		multiple_pipe.c \
		ft_strjoin0.c\
		ft_strlen0.c \
		mul_pipe.c \
		ft_pwd.c	\
		break_helper_1.c	\
		open_files.c	\
		here_doc.c \
		get_next_line.c\
		get_next_line_utils.c \
		export.c\
		ft_exit.c	\
		expande_helper_1.c	\
		expande_helper_2.c	\
		builtin.c \
		ft_env.c \
		mi_utils.c \
		ft_unset.c \
		one_commande.c \
		open_in_out_file.c \
		ft_cd.c \
		ft_echo.c \

OBJ= $(FUN:.c=.o)

all: $(NAME) $(LIBFT)

$(NAME): $(OBJ) $(LIBFT)
	$(COM) $(CFLAGS)  -lreadline $(OBJ) $(LIBFT) -o $(NAME)  


$(LIBFT):
	make all -C ./libft

clean:
	$(RM) $(OBJ)
	make clean -C ./libft

fclean:
	$(RM) $(NAME)
	make fclean -C ./libft

re:	fclean all
