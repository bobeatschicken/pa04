all: snl

snl: Board.cpp Game.cpp
	g++ -o snl Board.cpp Game.cpp