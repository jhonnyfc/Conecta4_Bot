all: 4ray
4ray: connect4WithBot.c
	gcc -Wall -g -o connect4WithBot connect4WithBot.c
