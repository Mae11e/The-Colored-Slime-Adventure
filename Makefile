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

# Recherche automatique des fichiers sources
SOURCES = $(shell find $(SRCDIR) -name "*.cpp")
OBJECTS = $(SOURCES:.cpp=.o)
TOTAL = $(words $(SOURCES))

# Includes
INCLUDES = -I$(INCDIR)

# Règle principale
all: $(TARGET)
	@echo "$(GREEN)✓ Compilation terminée avec succès !$(NC)"

# Compilation avec barre de progression
$(TARGET):
	@echo "$(CYAN)🔨 Compilation des sources...$(NC)"
	@i=0; total=$(TOTAL); \
	barlen=50; \
	for src in $(SOURCES); do \
		obj=$${src%.cpp}.o; \
		mkdir -p $$(dirname $$obj); \
		out=$$( \
			$(CXX) $(CXXFLAGS) $(INCLUDES) -c $$src -o $$obj 2>&1 \
		); \
		if [ $$? -ne 0 ]; then \
			echo "$$out"; exit 1; \
		elif echo "$$out" | grep -q "warning"; then \
			echo "$(YELLOW)[WARNING] $$src :$$out$(NC)"; \
		fi; \
		i=$$((i + 1)); \
		percent=$$((i * 100 / total)); \
		done_len=$$((barlen * i / total)); \
		empty_len=$$((barlen - done_len)); \
		bar_done=$$(printf "%0.s█" $$(seq 1 $$done_len)); \
		bar_empty=$$(printf "%0.s " $$(seq 1 $$empty_len)); \
		printf "\r\033[KProgress: [%-50s] %3d%%" "$$bar_done$$bar_empty" "$$percent"; \
	done; \
	echo ""
	@echo "$(CYAN)🔗 Liaison de l'exécutable...$(NC)"
	@$(CXX) $(OBJECTS) -o $@ $(LIBS)


# Nettoyage
clean:
	@echo "$(RED)🧹 Nettoyage des fichiers temporaires...$(NC)"
	find . -name "*.o" -delete
	rm -f $(TARGET)
	@echo "$(GREEN)✓ Nettoyage terminé !$(NC)"

# Recompilation complète
rebuild: clean all

# Debug
debug: CXXFLAGS += -g -DDEBUG
debug:
	@echo "$(BLUE)🔍 Compilation en mode debug...$(NC)"
	@$(MAKE) $(TARGET)

# Release
release: CXXFLAGS += -O3 -DNDEBUG
release:
	@echo "$(PURPLE)🚀 Compilation en mode release...$(NC)"
	@$(MAKE) $(TARGET)

.PHONY: all clean rebuild debug release
