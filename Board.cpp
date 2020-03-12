#include "Board.h"
#include <vector>
#include <set>
#include <queue>
#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>

Board::Board(int size)
{
    board = new std::vector<std::vector<int> *>;
    previous = new std::vector<int>;
    hasLadder = new std::vector<bool>;
    int numVertices = size * size;

    for (int i = 0; i < numVertices; i++)
    {
        std::vector<int> *adjList = new std::vector<int>;
        int j = i + 1;
        while (j < numVertices && j <= i + 6)
        {
            adjList->push_back(j);
            j++;
        }
        while (adjList->size() < 6 && i != numVertices - 1)
        {
            adjList->push_back(numVertices - 1);
        }
        board->push_back(adjList);
        previous->push_back(-1);
        hasLadder->push_back(false);
    }
    visited = new std::set<int>;
    ladders = new std::unordered_map<int, int>; //(end, start)
    snakes = new std::unordered_map<int, int>;  //(end, start)
}

Board::~Board()
{
    for (int i = 0; i < board->size(); i++)
    {
        delete board->at(i);
    }
    delete board;
}

void Board::addLadder(int start, int end)
{
    int actualStart = start - 1;
    int actualEnd = end - 1;
    ladders->insert(std::pair<int, int>(actualEnd, actualStart));

    //if hasLadder:
    //board->at(actualStart)->push_back(actualEnd)
    //else:
    //board->at(actualStart)->clear()
    //board->at(actualStart)->push_back(actualEnd)
    //hasLadder[actualStart] = 1;
    // board->at(actualStart)->clear();
    // board->at(actualStart)->push_back(actualEnd);
    //set all all the possible paths that lead to actualStart to actualEnd
    int temp = actualStart - 1;

    //if hasLadder:
    //board->at(actualStart)->push_back(actualEnd)
    //else:
    //board->at(actualStart)->clear()
    //board->at(actualStart)->push_back(actualEnd)
    //hasLadder[actualStart] = 1;

    if (hasLadder->at(actualStart))
    {
        board->at(actualStart)->push_back(actualEnd);
    }
    else
    {
        board->at(actualStart)->clear();
        board->at(actualStart)->push_back(actualEnd);
    }

    while (temp >= 0 && temp >= actualStart - 6)
    {
        int pos = find(board->at(temp)->begin(), board->at(temp)->end(), actualStart) - board->at(temp)->begin();
        if (pos < board->at(temp)->size())
        {
            if (!hasLadder)
            {
                board->at(temp)->at(pos) = actualEnd;
            }
            else
            {
                board->at(temp)->push_back(actualEnd);
            }
        }
        temp--;
    }
    hasLadder->at(actualStart) = true;
}

void Board::addSnake(int start, int end)
{
    //could have no ladder when adding snake
    //could already have a ladder when adding snake
    int actualStart = start - 1;
    int actualEnd = end - 1;
    snakes->insert(std::pair<int, int>(actualEnd, actualStart));

    board->at(actualStart)->clear();
    board->at(actualStart)->push_back(actualEnd);
    //set all the possible paths that lead to actualStart to actualEnd
    int temp = actualStart - 1;

    while (temp >= 0 && temp >= actualStart - 6)
    {
        int pos = find(board->at(temp)->begin(), board->at(temp)->end(), actualStart) - board->at(temp)->begin();
        if (pos < board->at(temp)->size())
        {
            board->at(temp)->at(pos) = actualEnd;
        }
        temp--;
    }
}

void Board::findShortestPath()
{
    std::queue<int> q;
    q.push(0);
    visited->insert(0);

    while (!q.empty())
    {
        int vertexX = q.front();
        q.pop();
        for (int i = board->at(vertexX)->size() - 1; i >= 0; i--) //finds all the neighboring vertices of vertexX
        {
            int vertexY = board->at(vertexX)->at(i);
            const bool vertexVisited = visited->find(vertexY) != visited->end();
            if (!vertexVisited)
            {
                previous->at(vertexY) = vertexX;
                q.push(vertexY);
                visited->insert(vertexY);
            }
        }
    }

    std::vector<int> shortestPathVector;
    std::string path = "";
    int pathLength = 0;
    int current = board->size() - 1;
    while (current >= 0)
    {
        int prev = previous->at(current);
        if (current > prev + 6)
        { //took a ladder
            path = " " + std::to_string(ladders->at(current) + 1) + "+" + std::to_string(current + 1) + path;
        }
        else if (prev > current)
        { //took a snake
            path = " " + std::to_string(snakes->at(current) + 1) + "-" + std::to_string(current + 1) + path;
        }
        else
        {
            path = " " + std::to_string(current + 1) + path;
        }
        pathLength++;
        current = prev;
    }
    std::cout << pathLength - 1 << std::endl;
    std::cout << path.substr(1, path.length() - 1) << std::endl;
}

void Board::printGraph()
{
    for (int i = 0; i < board->size(); i++)
    {
        std::cout << "Edge #" << i << ": ";
        for (int j = 0; j < board->at(i)->size(); j++)
        {
            std::cout << board->at(i)->at(j) << " ";
        }
        std::cout << std::endl;
    }
}