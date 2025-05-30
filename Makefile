# Couleurs
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
PURPLE = \033[0;35m
CYAN = \033[0;36m
WHITE = \033[0;37m
NC = \033[0m # No Color

# Nom de l'exécutable
TARGET = game

# Compilateur
CXX = g++

# Flags de compilation
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

# Dossiers
SRCDIR = src
INCDIR = include

# Bibliothèques SFML
LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network

# Recherche automatique des fichiers sources (récursive)
SOURCES = $(shell find $(SRCDIR) -name "*.cpp")
OBJECTS = $(SOURCES:.cpp=.o)

# Includes
INCLUDES = -I$(INCDIR)

# Règle principale
all: $(TARGET)
	@echo "$(GREEN)✓ Compilation terminée avec succès !$(NC)"

# Création de l'exécutable
$(TARGET): $(OBJECTS)
	@echo "$(CYAN)🔗 Liaison de l'exécutable...$(NC)"
	$(CXX) $(OBJECTS) -o $@ $(LIBS)

# Compilation des fichiers objets
%.o: %.cpp
	@echo "$(YELLOW)🔨 Compilation de $<...$(NC)"
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Nettoyage
clean:
	@echo "$(RED)🧹 Nettoyage des fichiers temporaires...$(NC)"
	find . -name "*.o" -delete
	rm -f $(TARGET)
	@echo "$(GREEN)✓ Nettoyage terminé !$(NC)"

# Recompilation complète
rebuild: clean all

# Debug (avec symboles de débogage)
debug: CXXFLAGS += -g -DDEBUG
debug: 
	@echo "$(BLUE)🔍 Compilation en mode debug...$(NC)"
	@$(MAKE) $(TARGET)

# Release (optimisation maximale)
release: CXXFLAGS += -O3 -DNDEBUG
release:
	@echo "$(PURPLE)🚀 Compilation en mode release...$(NC)"
	@$(MAKE) $(TARGET)

# Règles qui ne correspondent pas à des fichiers
.PHONY: all clean rebuild debug release