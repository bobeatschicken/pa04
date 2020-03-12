#include "Board.h"
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
    string input = argv[1];
    int p1 = 0, p2 = 0;

    int numGames = (int)input.at(p1);
    p1 += 3;
    p2 = p1;
    for (int i = 1; i <= numGames; i++)
    {
        while (input.at(p2) != ' ')
        {
            p2++;
        }
        int boardSize = stoi(input.substr(p1, p2 - p1));
        p1 = p2 + 1;
        p2 = p1;
        while (input.at(p2) != ' ')
        {
            p2++;
        }
        int numLadders = stoi(input.substr(p1, p2 - p1));
        p1 = p2 + 1;
        p2 = p1;
        while (input.at(p2) != 'n')
        {
            p2++;
        }
        int numSnakes = stoi(input.substr(p1, p2 - p1 - 1));
        p1 = p2 + 1;
        p2 = p1;

        cout << "N: " << boardSize << ", L: " << numLadders << ", S: " << numSnakes << endl;
        Board b(boardSize);
        for (int i = 0; i < numLadders - 1; i++)
        {
            while (input.at(p2) != ' ')
            {
                p2++;
            }
            int num1 = stoi(input.substr(p1, p2 - p1));
            p1 = p2 + 1;
            p2 = p1;
            while (input.at(p2) != ' ')
            {
                p2++;
            }
            int num2 = stoi(input.substr(p1, p2 - p1));
            b.addLadder(num1, num2);
            p1 = p2 + 1;
            p2 = p1;
        }
        while (input.at(p2) != ' ')
        {
            p2++;
        }
        int num1 = stoi(input.substr(p1, p2 - p1));
        p1 = p2 + 1;
        p2 = p1;
        while (input.at(p2) != 'n')
        {
            p2++;
        }
        int num2 = stoi(input.substr(p1, p2 - p1 - 1));
        b.addLadder(num1, num2);
        p1 = p2 + 1;
        p2 = p1;

        for (int i = 0; i < numSnakes - 1; i++)
        {
            while (input.at(p2) != ' ')
            {
                p2++;
            }
            int num1 = stoi(input.substr(p1, p2 - p1));
            p1 = p2 + 1;
            p2 = p1;
            while (input.at(p2) != ' ')
            {
                p2++;
            }
            int num2 = stoi(input.substr(p1, p2 - p1));
            b.addSnake(num1, num2);
            p1 = p2 + 1;
            p2 = p1;
        }

        while (input.at(p2) != ' ')
        {
            p2++;
        }
        num1 = stoi(input.substr(p1, p2 - p1));
        p1 = p2 + 1;
        p2 = p1;
        while (p2 < input.length() && input.at(p2) != 'n')
        {
            p2++;
        }
        if (p2 > input.length())
        {
            num2 = stoi(input.substr(p1, p2 - p1));
        }
        else
        {
            num2 = stoi(input.substr(p1, p2 - p1 - 1));
        }
        b.addSnake(num1, num2);
        p1 = p2 + 1;
        p2 = p1;
        cout << "Board Game #" << i << ":" << endl;
        b.findShortestPath();
        if (p2 > input.length())
        {
            return 0;
        }
    }
    // Board b(10);
    // b.addLadder(32, 62);
    // b.addLadder(42, 68);
    // b.addLadder(12, 98);
    // b.addSnake(95, 13);
    // b.addSnake(97, 25);
    // b.addSnake(93, 37);
    // b.addSnake(79, 27);
    // b.addSnake(75, 19);
    // b.addSnake(49, 47);
    // b.addSnake(67, 17);
    Board b(8);
    b.addLadder(8, 11);
    b.addSnake(63, 1);
    // b.printGraph();
    b.findShortestPath();
}