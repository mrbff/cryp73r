NAME := cryp73r

CFLAGS := -lcryptopp -g

CC := g++

SRCS := main.cpp f_iterator.cpp f_encryptor.cpp f_decryptor.cpp f_utils.cpp

OBJS :=  $(SRCS:.cpp=.o)

.cpp.o:
	${CC} -c $< -o ${<:.cpp=.o} $(CFLAGS)

RM :=	rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(CC)  $(OBJS) -o $(NAME) $(CFLAGS)

clean:
	$(RM) *.o

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re