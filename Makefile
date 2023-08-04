
NAME	= ircserv

DIR_SRCS = srcs

DIR_OBJS = objects

SRCS	= main.cpp Server/Server.cpp User/User.cpp Utils/helper.cpp Channel/Channel.cpp\
		  $(addprefix Commands/, nick.cpp pass.cpp pong.cpp user.cpp \
		  quit.cpp command.cpp mode.cpp join.cpp privmsg.cpp whois.cpp \
		  part.cpp topic.cpp oper.cpp who.cpp notice.cpp die.cpp kill.cpp \
		  kick.cpp invite.cpp)

OBJS	= $(SRCS:%.cpp=$(DIR_OBJS)/%.o)

CC		= c++

RM		= rm -rf

MKDIR	= mkdir -p

CFLAGS	= -Wall -Werror -Wextra -pedantic -std=c++98

all: $(NAME)

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(DIR_OBJS)/%.o : $(DIR_SRCS)/%.cpp
			${MKDIR} ${dir $@}
		${CC} ${CFLAGS} -c $< -o $@

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME} ${DIR_OBJS}

re: fclean all

rc: re
	${RM} ${OBJS} && clear && ./ircserv 6667 lol

rv: re
	${RM} ${OBJS} && clear && valgrind --leak-check=full ./ircserv 6667 lol

v: all
	valgrind --leak-check=full ./ircserv 6667 lol

.PHONY: all clean fclean re rc rv v
