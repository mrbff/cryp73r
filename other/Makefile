NAME1 := keygen

NAME2 := crypter

NAME3 := decrypter

CFLAGS := -lcryptopp

CC := g++

SRCS1 := keygen.cpp
SRCS2 := crypter.cpp
SRCS3 := decrypter.cpp

OBJS1 :=  $(SRCS1:.cpp=.o)
OBJS2 :=  $(SRCS2:.cpp=.o)
OBJS3 :=  $(SRCS3:.cpp=.o)

.cpp.o:
	${CC} -c $< -o ${<:.cpp=.o} $(CFLAGS)

RM :=	rm -f

all: $(NAME1) $(NAME2) $(NAME3)

$(NAME1): $(OBJS1)
	$(CC)  $(OBJS1) -o $(NAME1) $(CFLAGS)

$(NAME2): $(OBJS2)
	$(CC) $(OBJS2) -o $(NAME2) $(CFLAGS)

$(NAME3): $(OBJS3)
	$(CC) $(OBJS3) -o $(NAME3) $(CFLAGS)

clean:
	$(RM) *.o

fclean: clean
	$(RM) $(NAME1) $(NAME2) $(NAME3)

re: fclean all

.PHONY: all clean fclean re