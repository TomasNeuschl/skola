
OBJS = main.o Bonus.o Character.o Display.o Enemy.o EnemyFlock.o Game.o Laser.o Player.o

CC = g++

COMPILER_FLAGS = -w -Wall -std=c++11 -pedantic -Wno-long-long -O0 -ggdb -g

OBJ_NAME = neusctom

all : compile doc

compile : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) -o $(OBJ_NAME) -lncurses

main.o : $($(CC) -MM src/main.cpp) src/main.cpp
	$(CC) $(COMPILER_FLAGS) -c src/main.cpp -o main.o

Bonus.o : $($(CC) -MM src/Bonus.cpp) src/Bonus.cpp
	$(CC) $(COMPILER_FLAGS) -c src/Bonus.cpp -o Bonus.o

Character.o : $($(CC) -MM src/Character.cpp) src/Character.cpp
	$(CC) $(COMPILER_FLAGS) -c src/Character.cpp -o Character.o

Display.o : $($(CC) -MM src/Display.cpp) src/Display.cpp
	$(CC) $(COMPILER_FLAGS) -c src/Display.cpp -o Display.o

Enemy.o : $($(CC) -MM src/Enemy.cpp) src/Enemy.cpp
	$(CC) $(COMPILER_FLAGS) -c src/Enemy.cpp -o Enemy.o

EnemyFlock.o : $($(CC) -MM src/EnemyFlock.cpp) src/EnemyFlock.cpp
	$(CC) $(COMPILER_FLAGS) -c src/EnemyFlock.cpp -o EnemyFlock.o

Game.o : $($(CC) -MM src/Game.cpp) src/Game.cpp
	$(CC) $(COMPILER_FLAGS) -c src/Game.cpp -o Game.o

Laser.o : $($(CC) -MM src/Laser.cpp) src/Laser.cpp
	$(CC) $(COMPILER_FLAGS) -c src/Laser.cpp -o Laser.o

Player.o : $($(CC) -MM src/Player.cpp) src/Player.cpp
	$(CC) $(COMPILER_FLAGS) -c src/Player.cpp -o Player.o

doc :
	doxygen Doxyfile

.PHONY: doc

clean :
	rm -rf *.o doc neusctom

.PHONY: clean

run :
	./neusctom
