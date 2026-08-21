#
#	Makefile per il progetto MiniMario.
#

CXX=g++
CXX_FLAGS=-O3 -std=c++17 -Wfatal-errors -I ~/SFML-3.1.0/include
LD_FLAGS=-L ~/SFML-3.1.0/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

.PHONY: clean all

tilemap.o: tilemap.c
	$(CXX) -c $^

%.o: %.cpp
	$(CXX) $(CXX_FLAGS) -c $< -o $@

MiniMario: Mario.o Scene.o Game.o Block.o QuestionBlock.o Coin.o Enemy.o \
	Goomba.o PiranhaPlant.o Koopa.o Powerup.o SuperMushroom.o \
	OneUpMushroom.o CoinPowerup.o Layer.o Menu.o MenuEntry.o tilemap.o main.o
	$(CXX) $(CXX_FLAGS) $^ -o $@ $(LD_FLAGS)

all: MiniMario

clean:
	-rm -f *.o *.gch MiniMario
