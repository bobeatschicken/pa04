all: game

game: Board.cpp Game.cpp
	g++ -o game Board.cpp Game.cpp