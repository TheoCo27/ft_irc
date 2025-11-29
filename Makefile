# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user <marvin@42.fr>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/30                              #+#    #+#              #
#    Updated: 2025/04/30                              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        := ircserv

CXX         := c++
CXXFLAGS    := -Wall -Wextra -Werror -std=c++98 -Iincludes -g3

SRC_DIR     := src
OBJ_DIR     := obj
TEST_DIR    = test

SRC_FILES   := main.cpp server.cpp client.cpp channel.cpp parser.cpp utils.cpp checker.cpp
#server.cpp client.cpp channel.cpp
SRC         := $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ         := $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.cpp=.o))

# Couleurs (optionnel)
GREEN       := \033[0;32m
RESET       := \033[0m

# Compilation des .cpp vers .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	@$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo "$(GREEN)[Compiled]$(RESET) $<"

# Règle par défaut
all: $(NAME)

# Edition de liens
$(NAME): $(OBJ)
	@$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)
	@echo "$(GREEN)[Linked]$(RESET) $(NAME)"

# Nettoyage des objets
clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(GREEN)[Cleaned]$(RESET) object files"

# Nettoyage complet
fclean: clean
	@rm -f $(NAME)
	@echo "$(GREEN)[Cleaned]$(RESET) binary $(NAME)"

# Recompilation complète
re: fclean all

run:
	./ircserv 6667 theo

test:
	valgrind \
    --leak-check=full \
    --show-leak-kinds=all \
    --track-fds=yes \
    ./ircserv 6667 theo

# **************************************************************************** #
#                               TEST COMMANDS                                  #
# **************************************************************************** #

co:
	bash $(TEST_DIR)/connect.sh

client:
	bash $(TEST_DIR)/client.sh

pass_test:
	bash $(TEST_DIR)/wrong_pass_test.sh
	bash $(TEST_DIR)/pass_test.sh

nickname_test:
	@gnome-terminal -- bash -c "cd $(CURDIR); ./test/nickname_test.sh; exec bash" & \
	bash $(TEST_DIR)/c_for_nick.sh


user_test:
	bash $(TEST_DIR)/user_test.sh

join_test:
	@gnome-terminal -- bash -c "cd $(CURDIR); bash test/join_test.sh; exec bash"
	sleep 2
	bash $(TEST_DIR)/c_for_join.sh


part_test:
	bash $(TEST_DIR)/part_test.sh

invite_test:
	bash $(TEST_DIR)/invite_test.sh

kick_test:
	bash $(TEST_DIR)/kick_test.sh

topic_test:
	bash $(TEST_DIR)/topic_test.sh

privmsg_test:
	bash $(TEST_DIR)/privmsg_test.sh

ping:
	bash $(TEST_DIR)/ping.sh

mode:
	@gnome-terminal -- bash -c "cd $(CURDIR); bash test/c_for_mode.sh; exec bash"
	sleep 2
	bash $(TEST_DIR)/mode.sh

quit:
	bash $(TEST_DIR)/quit.sh
# **************************************************************************** #
#                                   PHONY                                      #
# **************************************************************************** #

.PHONY: all clean fclean re run test \
	co client pass_test nickname_test user_test \
	join_test part_test invite_test kick_test topic_test \
	privmsg_test ping mode quit


