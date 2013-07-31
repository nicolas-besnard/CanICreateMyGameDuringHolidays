NAME		=	exec

SRCS_DIR	=	../src
CXX		=	g++

RM		=	rm -f

CXXFLAGS	=	-W -Wextra -Wall
CXXFLAGS	+=	-I../src/ -I../src/debug -I../src/utilities -I../src/managers -I../src/resources -I../src/loaders -I../src/entities -I../src/components/

LDFLAGS		=	-L/usr/lib -lallegro -lallegro_dialog -lallegro_primitives -lallegro_ttf -lallegro_font -lallegro_image

SRCS		=	$(wildcard $(SRCS_DIR)/*.cpp)		\
			$(wildcard $(SRCS_DIR)/debug/*.cpp)	\
			$(wildcard $(SRCS_DIR)/managers/*.cpp)	\
			$(wildcard $(SRCS_DIR)/resources/*.cpp)	\
			$(wildcard $(SRCS_DIR)/loaders/*.cpp)	\
			$(wildcard $(SRCS_DIR)/entities/*.cpp)	\
			$(wildcard $(SRCS_DIR)/components/*.cpp)	\
			$(wildcard *.cpp)

OBJS		=	$(SRCS:.cpp=.o)

ECHO		=	echo -e

all		:	$(NAME)

$(NAME)		:	$(OBJS)
			@$(CXX) $(OBJS) -o $(NAME) $(LDFLAGS)
			@$(ECHO) '\033[1;37;44m> Compiled {\033[4m$(NAME)}\033[0m'

clean		:
			-@$(RM) $(OBJS)
			@$(ECHO) '\033[1;37;41m> Directory cleaned\033[0m'

fclean		:	clean
			-@$(RM) $(NAME)
			@$(ECHO) '\033[1;37;41m> Remove executable\033[0m'

re		:	fclean all

.PHONY		:	all clean re

-include $(DEPS)