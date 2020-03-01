#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

string convertToPiece(int i)
{
    if (i == 1)
        return "●";
    else if (i == -1)
        return "○";
    else
        return "□";
}

class Game
{
private:
    int board[10][10] = {{9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
                          {9, 0, 0, 0, 0, 0, 0, 0, 0, 9},
                          {9, 0, 0, 0, 0, 0, 0, 0, 0, 9},
                          {9, 0, 0, 0, 0, 0, 0, 0, 0, 9},
                          {9, 0, 0, 0, -1, 1, 0, 0, 0, 9},
                          {9, 0, 0, 0, 1, -1, 0, 0, 0, 9},
                          {9, 0, 0, 0, 0, 0, 0, 0, 0, 9},
                          {9, 0, 0, 0, 0, 0, 0, 0, 0, 9},
                          {9, 0, 0, 0, 0, 0, 0, 0, 0, 9},
                          {9, 9, 9, 9, 9, 9, 9, 9, 9, 9}};

    string player1 = "Player 1";
    string player2 = "Player 2";
    int turn = 1; // 1 = player 1, -1 = player 2
public:
    void printMovePrompt();
    void setPiece(int row, int col);
    void evalBoard();
    void changeTurn();
    void printBoard();
    void printPrompt();
    bool isGameFinished();
    bool isMoveLegal(int row, int col);
    bool haveNeighbor(int row, int col);
    bool canChangeEnemy(int row, int col);

    Game();
};

Game::Game()
{
}

void Game::setPiece(int row, int col)
{
    if (isMoveLegal(row, col))
    {
        this->board[row][col] = turn;
    }
}

bool Game::isMoveLegal(int row, int col)
{
    if (this->board[row][col] != 0)
        return false;
    else if (!(this->haveNeighbor(row, col)))
        return false;
    //else if ()
}

bool Game::haveNeighbor(int row, int col)
{
    return (this->board[row - 1][col - 1] != 0 && this->board[row - 1][col - 1] != 9 
                && this->board[row - 1][col] != 0 && this->board[row - 1][col] != 9
                && this->board[row - 1][col + 1] != 0 && this->board[row - 1][col + 1] != 9 
                && this->board[row][col - 1] != 0 && this->board[row][col - 1] != 9
                && this->board[row][col + 1] != 0 && this->board[row][col + 1] != 0 
                && this->board[row + 1][col - 1] != 0 && this->board[row + 1][col - 1] != 9 
                && this->board[row + 1][col] != 0 && this->board[row + 1][col] != 9 
                && this->board[row + 1][col + 1] != 0 && this->board[row + 1][col + 1] != 0);
}

bool Game::canChangeEnemy(int row, int col)
{
    if ((row > 0 && col > 0 && row < 7 && col < 7))
    {
        return !(this->board[row - 1][col - 1] == 0 && this->board[row - 1][col] == 0 && this->board[row - 1][col + 1] == 0 && this->board[row][col - 1] == 0 && this->board[row][col + 1] == 0 && this->board[row + 1][col - 1] == 0 && this->board[row + 1][col] == 0 && this->board[row + 1][col + 1] == 0);
    }
    else
    {
        if ((row - col) == 0 || abs(row - col) == 7)
        {
            if (row == 0 && col == 0)
                return !(this->board[row][col + 1] == 0 && this->board[row + 1][col + 1] == 0 && this->board[row + 1][col] == 0);
            else if (row == 7 && col == 7)
                return !(this->board[row][col - 1] == 0 && this->board[row - 1][col - 1] == 0 && this->board[row - 1][col] == 0);
            else if (row == 0 && col == 7)
                return !(this->board[row][col - 1] == 0 && this->board[row + 1][col - 1] == 0 && this->board[row + 1][col] == 0);
            else if (row == 7 && col == 0)
                return !(this->board[row - 1][col] == 0 && this->board[row + 1][col - 1] == 0 && this->board[row][col + 1] == 0);
        }
        else
        {
            if (row == 0)
                return !(this->board[row][col - 1] == 0 && this->board[row][col + 1] == 0 && this->board[row + 1][col - 1] == 0 && this->board[row + 1][col] == 0 && this->board[row + 1][col + 1] == 0);
            else if (col == 0)
                return !(this->board[row - 1][col] == 0 && this->board[row + 1][col] == 0 && this->board[row + 1][col + 1] == 0 && this->board[row - 1][col + 1] == 0 && this->board[row][col + 1] == 0);
            else if (row == 7)
                return !(this->board[row][col - 1] == 0 && this->board[row][col + 1] == 0 && this->board[row - 1][col - 1] == 0 && this->board[row - 1][col] == 0 && this->board[row - 1][col + 1] == 0);
            else if (col == 7)
                return !(this->board[row - 1][col] == 0 && this->board[row + 1][col] == 0 && this->board[row - 1][col - 1] == 0 && this->board[row][col - 1] == 0 && this->board[row + 1][col - 1] == 0);
        }
    }
}

void Game::printBoard()
{
    cout << "   a b c d e f g h " << endl
    << "   ----------------" << endl;

    for (int i = 1; i < 9; i++)
    {
        for (int j = 1; j < 9; j++)
        {
            if (j == 1)
                cout << i << "|";
            cout << " " + convertToPiece(this->board[i][j]);
            // cout << this->pieces[i][j];
            if (j == 8)
                cout << " |" << endl;
        }
    }

    cout << "   ----------------" << endl;
}

int main()
{
    Game game = Game();
    game.printBoard();
    return 0;
}