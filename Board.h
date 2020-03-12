#include <vector>
#include <set>
#include <unordered_map>
class Board
{
public:
    Board(int size);
    ~Board();
    void addLadder(int start, int end);
    void addSnake(int start, int end);
    void findShortestPath();
    void printGraph();

private:
    std::vector<std::vector<int> *> *board;
    std::set<int> *visited;
    std::vector<int> *previous;
    std::unordered_map<int, int> *ladders;
    std::unordered_map<int, int> *snakes;
    std::vector<bool> *hasLadder;
};