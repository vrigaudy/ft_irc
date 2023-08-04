
NAME	= ircserv

DIR_SRCS = srcs

DIR_OBJS = objects

SRCS	= main.cpp Server/Server.cpp User/User.cpp Utils/helper.cpp Channel/Channel.cpp\
		  $(addprefix Commands/, nick.cpp pass.cpp pong.cpp user.cpp \
		  quit.cpp command.cpp mode.cpp join.cpp privmsg.cpp whois.cpp \
		  part.cpp topic.cpp oper.cpp who.cpp notice.cpp die.cpp kill.cpp \
		  kick.cpp invite.cpp)

INCLUDES = ./includes/Channel.hpp \
    ./includes/Exception.hpp \
    ./includes/Messages.hpp \
    ./includes/Server.hpp \
    ./includes/User.hpp

OBJS	= $(SRCS:%.cpp=$(DIR_OBJS)/%.o)

CC		= c++

RM		= rm -rf

MKDIR	= mkdir -p

CFLAGS	= -Wall -Werror -Wextra -std=c++98

all: $(NAME)

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(DIR_OBJS)/%.o : $(DIR_SRCS)/%.cpp ${INCLUDES}
			${MKDIR} ${dir $@}
		${CC} ${CFLAGS} -c $< -o $@

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME} ${DIR_OBJS}

re: fclean all

.PHONY: all clean fclean re
