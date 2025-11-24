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
	bash ./run.sh

s:
	./ircserv 6667 theo

.PHONY: all clean fclean re run s
