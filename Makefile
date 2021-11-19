##
## EPITECH PROJECT, 2019
## makefile
## File description:
## makes files
##

SRCS_DIR	=	src/

SRCS_FILES	=	Component.cpp Factory.cpp Gates.cpp Error.cpp

MAIN_FILE	=	src/main.cpp

SRCS	= $(addprefix $(SRCS_DIR), $(SRCS_FILES))

FILES_O	=	$(SRCS:.c=.o)

MAIN_O	=	$(MAIN_FILE:.c=.o)

CFLAGS += -I include

NAME = nanotekspice

all: $(NAME)

$(NAME): $(FILES_O) $(MAIN_O)
	g++ -o $(NAME) $(MAIN_O) $(FILES_O) $(CFLAGS) -g

debug: $(FILES_O)
	g++ -o $(NAME) $(MAIN_O) $(FILES_O) -Wall -Wextra -Werror -g $(CFLAGS)

tests_run:
	make -C tests tests_run from="$(CURDIR)" files="$(FILES_C)"

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all
