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
        return " ";
}

int whoIsEnemyOf(int i)
{
    return i * (-1);
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

    string player1 = "Player 1（●）";
    string player2 = "Player 2（○）";
    int turn; // 1 = player 1, -1 = player 2
public:
    void printMovePrompt();
    void getMove();
    void makeMove(int row, int col);
    void evalBoard();
    void changeTurn();
    void printBoard();
    void printPrompt();
    bool isGameFinished();
    bool isMoveLegal(int row, int col);
    bool haveNeighbor(int row, int col);
    bool canChangeEnemy(int row, int col);
    int countTurnablePieces(int row, int col, int x, int y);
    int getBoardValue(int row, int col);

    Game();
};

Game::Game()
{
    this->turn = 1;
}

void Game::makeMove(int row, int col)
{
    if (isMoveLegal(row, col))
    {
        for (int d = -1; d <= 1; d++)
        {
            for (int e = -1; e <= 1; e++)
            {
                if (d == 0 && e == 0)
                    continue;
                else
                {
                    int count = this->countTurnablePieces(row, col, d, e);
                    if (count > 0)
                    {
                        for (int i = 0; i <= count; i++)
                        {
                            this->board[row + i * d][col + i * e] = this->turn;
                        }
                    }
                }
            }
        }
    }

    this->changeTurn();
}

void Game::changeTurn()
{
    this->turn = this->turn * (-1);
}

void Game::printMovePrompt()
{
    string player = this->turn > 0 ? this->player1 : this->player2;
    cout << "It is now " << player << "'s turn" << endl
         << "Please input your move. ex) d 4" << endl
         << "> ";
}

void Game::getMove()
{
    char a;
    int b = 0;
    this->printMovePrompt();
    cin >> a >> b;
    int ia = a - 96;
    if (this->isMoveLegal(b, ia))
    {
        this->makeMove(b, ia);
        this->printBoard();
        this->getMove();
    }
    else
    {
        cout << "Ilegal or invalid input. Please try again." << endl;
        this->getMove();
    }
}

bool Game::isMoveLegal(int row, int col)
{
    if (this->board[row][col] != 0)
    {
        return false;
    }
    else if (!(this->haveNeighbor(row, col)))
    {
        return false;
    }
    else if (!this->canChangeEnemy(row, col))
    {
        return false;
    }

    return true;
}

bool Game::haveNeighbor(int row, int col)
{
    return (this->board[row - 1][col - 1] != 0 || this->board[row - 1][col - 1] != 9 || this->board[row - 1][col] != 0 || this->board[row - 1][col] != 9 || this->board[row - 1][col + 1] != 0 || this->board[row - 1][col + 1] != 9 || this->board[row][col - 1] != 0 || this->board[row][col - 1] != 9 || this->board[row][col + 1] != 0 || this->board[row][col + 1] != 0 || this->board[row + 1][col - 1] != 0 || this->board[row + 1][col - 1] != 9 || this->board[row + 1][col] != 0 || this->board[row + 1][col] != 9 || this->board[row + 1][col + 1] != 0 || this->board[row + 1][col + 1] != 0);
}

bool Game::canChangeEnemy(int row, int col)
{
    for (int d = -1; d <= 1; d++)
    {
        for (int e = -1; e <= 1; e++)
        {
            if (d == 0 && e == 0)
                continue;
            else
            {
                if (this->countTurnablePieces(row, col, d, e) > 0)
                    return true;
                else
                    continue;
            }
        }
    }
    return false;
}

int Game::countTurnablePieces(int row, int col, int x, int y)
{
    int count = 0;
    for (int i = 1; i < 9; i++)
    {
        if (this->board[row + i * x][col + i * y] == whoIsEnemyOf(this->turn))
        {
            count++;
        }
        else if (this->board[row + i * x][col + i * y] == this->turn && count > 0)
        {
            return count;
        }
        else if (this->board[row + i * x][col + i * y] == 0 || this->board[row + i * x][col + i * y] == 9)
        {
            return 0;
        }
    }
};

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
    game.getMove();
    return 0;
}