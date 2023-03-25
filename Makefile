NAME		:=	chaselight

OBJ_FOLDER	:=	obj

CC			:=	c++

SRCS		:=	debug/main.cpp \
				ChaseLight.cpp \
				ChaseLightTime.cpp \
				Button.cpp

OBJS		:=	$(SRCS:%.cpp=$(OBJ_FOLDER)/%.o)

DEBUG		=	1
CFLAGS		=	-Wall -Wextra -Werror -std=c++11 -Wfatal-errors -Wconversion
DFLAG		=	-g -D DEBUG=$(DEBUG)

all:	$(NAME)
	./$(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJS): $(OBJ_FOLDER)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CC) -c $(CFLAGS) $(DFLAG) $< -o $@

time: DEBUG = 2
time: re

clean:
	rm -fr $(OBJ_FOLDER)

fclean: clean
	rm -fr $(NAME) $(NAME).dSYM

re: fclean all


val:
	valgrind --leak-check=full -s ./$(NAME)


.PHONY: clean fclean re val $(NAME) time
