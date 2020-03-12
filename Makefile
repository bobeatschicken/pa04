all: sn1

sn1: Board.cpp Game.cpp
	g++ -o sn1 Board.cpp Game.cpp