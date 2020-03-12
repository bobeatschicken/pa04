all: sn1

sn1: Board.cpp Game.cpp
	g++ -o game Board.cpp Game.cpp