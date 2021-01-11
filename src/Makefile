CPPFLAGS = -I/usr/include/irrlicht
CXXFLAGS = -Wall -Wextra -O2 -g -std=c++11 -Wno-unused

irrlicht: main.o MyEventReceiver.o personnage.o Weapon.o Map.o Camera.o Billboard.o Collision.o Vague.o ennemis.o
	g++ $^ -o $@ -lIrrlicht -Wno-unused

clean:
	rm -f *.o

mrproper: clean
	rm -f irrlicht
