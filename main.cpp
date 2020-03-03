#include <iostream>
#include <iomanip>
#include <string>
#include <game.cpp>

using namespace std;

int main()
{
    Game game = Game();
    game.printBoard();
    game.getMove();
    return 0;
}