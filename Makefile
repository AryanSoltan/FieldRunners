CC = g++ -std=c++11
CCFLAGS = -l SDL2 -l SDL2_image -l SDL2_ttf -l SDL2_mixer
RSDL_LIBRARY = RSDL-master/src/rsdl.hpp
all: FieldRunners.out

FieldRunners.out: game_class.o main.o Enemy.o GameIcons.o EnemyTable.o SuperTrooper.o rsdl.o Runner.o StubbornRunner.o Scrambler.o Wave.o Tower.o Gattling.o Tesla.o Missile.o Glue.o User.o Shoot.o
	$(CC) rsdl.o game_class.o main.o Enemy.o GameIcons.o EnemyTable.o SuperTrooper.o Runner.o StubbornRunner.o Scrambler.o Wave.o Tower.o Gattling.o Tesla.o Missile.o Glue.o User.o Shoot.o $(CCFLAGS) -o FieldRunners.out

rsdl.o: $(RSDL_LIBRARY) RSDL-master/src/rsdl.cpp
	$(CC) -c RSDL-master/src/rsdl.cpp -o rsdl.o

main.o: $(RSDL_LIBRARY) main.cpp FieldRunners.hpp
	$(CC) -c main.cpp -o main.o

game_class.o: $(RSDL_LIBRARY) FieldRunners.cpp FieldRunners.hpp GameIcons.hpp Enemy.hpp EnemyTable.hpp Wave.hpp Tower.hpp
	$(CC) -c FieldRunners.cpp -o game_class.o

Enemy.o: $(RSDL_LIBRARY) Enemy.cpp Enemy.hpp GameIcons.hpp Shoot.hpp
	$(CC) -c Enemy.cpp -o Enemy.o

GameIcons.o: $(RSDL_LIBRARY) GameIcons.cpp GameIcons.hpp
	$(CC) -c GameIcons.cpp -o GameIcons.o

EnemyTable.o: $(RSDL_LIBRARY) GameIcons.hpp EnemyTable.hpp EnemyTable.cpp Enemy.hpp
	$(CC) -c EnemyTable.cpp -o EnemyTable.o

SuperTrooper.o:  $(RSDL_LIBRARY) GameIcons.hpp Enemy.hpp SuperTrooper.hpp SuperTrooper.cpp
	$(CC) -c SuperTrooper.cpp -o SuperTrooper.o

Runner.o:  $(RSDL_LIBRARY) GameIcons.hpp Enemy.hpp Runner.hpp Runner.cpp
	$(CC) -c Runner.cpp -o Runner.o

StubbornRunner.o:  $(RSDL_LIBRARY) GameIcons.hpp Enemy.hpp StubbornRunner.hpp StubbornRunner.cpp
	$(CC) -c StubbornRunner.cpp -o StubbornRunner.o

Scrambler.o:  $(RSDL_LIBRARY) GameIcons.hpp Enemy.hpp Scrambler.hpp Scrambler.cpp
	$(CC) -c Scrambler.cpp -o Scrambler.o

Wave.o: Wave.cpp Wave.hpp Enemy.hpp SuperTrooper.hpp StubbornRunner.hpp Runner.hpp Scrambler.hpp EnemyTable.hpp  $(RSDL_LIBRARY)
	$(CC) -c Wave.cpp -o Wave.o

Tower.o: Tower.cpp Tower.hpp GameIcons.hpp  $(RSDL_LIBRARY) Wave.hpp Enemy.hpp
	$(CC) -c Tower.cpp -o Tower.o

Gattling.o: Gattling.cpp Gattling.hpp Tower.hpp $(RSDL_LIBRARY)
	$(CC) -c Gattling.cpp -o Gattling.o

Tesla.o: Tesla.cpp Tesla.hpp Tower.hpp Wave.hpp $(RSDL_LIBRARY)
	$(CC) -c Tesla.cpp -o Tesla.o

Missile.o: Missile.cpp Missile.hpp Tower.hpp Wave.hpp  $(RSDL_LIBRARY)
	$(CC) -c Missile.cpp -o Missile.o

Glue.o: Glue.cpp Glue.hpp Tower.hpp Wave.hpp $(RSDL_LIBRARY)
	$(CC) -c Glue.cpp -o Glue.o

User.o: User.cpp User.hpp Tower.hpp Gattling.hpp Wave.hpp $(RSDL_LIBRARY)
	$(CC) -c User.cpp -o User.o
Shoot.o: Shoot.cpp Shoot.hpp GameIcons.hpp
	$(CC) -c Shoot.cpp -o Shoot.o
clean:
	rm *.out *.o
