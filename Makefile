 # CCF212 - Algoritmos e Estruturas de Dados II - 2026/1
 # Trabalho Pratico I - Grupo TP1-AEDS2
 #
 # Integrantes:
 #   Arthur Emanoel Alecrim Correia  - 6582
 #   Ryan Italo de Andrade Ananias   - 6588
 #   Thomaz Augusto Araujo Silva     - 6577
 #   Alejandro Mateus Escobar Cavalcante - 6598
 
CC      = gcc
CFLAGS  = -Wall -Wextra -g
LIBS    = -lm

# Arquivos fonte
SRCS = main.c \
       loader.c \
       lista.c \
       hash/hash.c \
       hash/indice_hash.c \
       hash/tfidf_hash.c \
       patricia/patricia.c \
       patricia/indice_patricia.c \
       patricia/tfidf_patricia.c

OBJS = $(SRCS:.c=.o)
TARGET = programa

all: $(TARGET)

run: $(TARGET)
	./$(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all run clean