##
## EPITECH PROJECT, 2024
## nanotekspice
## File description:
## Makefile
##

CC = g++

CPPFLAGS += -Wall -Wextra -std=c++20 -iquote ./include

SRC =	main.cpp						\
		src/Thread/ScopeLock.cpp				\
		src/Thread/Mutex.cpp					\
		src/Thread/SafeQueue.cpp				\
		src/Thread/ConditionVariable.cpp		\
		src/Thread/ThreadPool.cpp		\
		src/Reception.cpp				\
		src/Parser.cpp					\
		src/IPC/NamedPipeInput.cpp		\
		src/IPC/NamedPipeOutput.cpp		\
		src/IPC/NamedPipe.cpp			\
		src/IPC/ANamedPipeEntry.cpp		\
		src/IPC/StreamChecker.cpp		\
		src/Kitchen.cpp					\
		src/Process/Process.cpp			\
		src/Factory.cpp					\
		src/APizza.cpp					\
		src/Fridge.cpp					\
		src/Logger.cpp					\
		src/Cooks.cpp					\


NAME = plazza

OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ)

clean:
	$(RM) $(OBJ)
	$(RM) */*.o
	$(RM) *.o
	$(RM) kitchen*

fclean: clean
	$(RM) $(NAME)

re: fclean
re: all

.PHONY: all clean fclean re
