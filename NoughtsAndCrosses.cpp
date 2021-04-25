#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define f1(n) for (int i = 0; i < n; i++)
#define f2(n) for (int j = 0; j < n; j++)
#define mmax 100005
#define all(v) v.begin(), v.end()
#define ll long long

struct move
{
    int r, c, score;
};

struct TicTacToe
{
    char player, computer, grid[3][3];
    TicTacToe()
    {
        f1(3)
        {
            f2(3)
            {
                grid[i][j] = ' ';
            }
        }
    }

    bool win()
    {
        int win_states[8][3] = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, {0, 4, 8}, {2, 4, 6}};
        f1(8)
        {
            bool win = true;
            int first_row = win_states[i][0] / 3, first_coloumn = win_states[i][0] % 3;
            f2(3)
            {
                int r = win_states[i][j] / 3, c = win_states[i][j] % 3;
                if (grid[first_row][first_coloumn] == ' ' or grid[first_row][first_coloumn] != grid[r][c])
                {
                    win = false;
                }
            }
            if (win)
            {
                return true;
            }
        }
        return false;
    }

    bool tie()
    {
        if (win())
        {
            return false;
        }
        f1(3)
        {
            f2(3)
            {
                if (grid[i][j] == ' ')
                {
                    return false;
                }
            }
        }
        return true;
    }

    void player_move()
    {
        while (true)
        {
            cout << "Enter an empty cell between(1-9): ";
            int cell;
            cin >> cell;
            int r = (cell - 1) / 3;
            int c = (cell - 1) % 3;

            if (cell >= 1 and cell <= 9 and grid[r][c] == ' ')
            {
                grid[r][c] = player;
                break;
            }
        }
    }

    void computer_move()
    {
        struct move best_move = minimax();
        grid[best_move.r][best_move.c] = computer;
    }

    struct move minimax(bool maximizing_player = true)
    {
        struct move best_move;
        if (win())
        {
            if (maximizing_player)
            {
                best_move.score = -1;
            }
            else
            {
                best_move.score = 1;
            }
            return best_move;
        }
        else if (tie())
        {
            best_move.score = 0;
            return best_move;
        }

        best_move.score = maximizing_player ? -2 : 2;
        f1(3)
        {
            f2(3)
            {
                if (grid[i][j] == ' ')
                {
                    grid[i][j] = maximizing_player ? computer: player;
                    struct move board_state = minimax(!maximizing_player);
                    if (maximizing_player)
                    {
                        if (board_state.score > best_move.score)
                        {
                            best_move.score = board_state.score;
                            best_move.r = i;
                            best_move.c = j;
                        }
                    }
                    else
                    {
                        if (board_state.score < best_move.score)
                        {
                            best_move.score = board_state.score;
                            best_move.r = i;
                            best_move.c = j;
                        }
                    }
                    grid[i][j] = ' ';
                }
            }
        }
        return best_move;
    }

    void play()
    {

        while (true)
        {

            cin >> player;
            if (player == 'x' or player == 'o')
            {
                break;
            }
        }
        computer = player == 'x' ? 'o' : 'x';
        if (player == 'o')
        {
            computer_move();
            print();
        }
        print();

        while (true)
        {
            player_move();
            print();
            if (win())
            {
                cout << "Player win\n";
                return;
            }
            else if (tie())
            {
                cout << "Tie !\n";
                return;
            }
            cout << "Computer is making a move \n";
            computer_move();
            print();
            if (win())
            {
                cout << "Computer win\n";
                return;
            }
            else if (tie())
            {
                cout << "Tie !\n";
                return;
            }
        }
    }

    void print()
    {
        f1(3)
        {
            if (i)
            {
                cout << "-------------" << endl;
            }
            f2(3)
            {
                if (j)
                {
                    cout << "|";
                }
                cout << " ";
                if (grid[i][j] == ' ')
                {
                    cout << 3 * i + j + 1;
                }
                else
                {
                    cout << grid[i][j];
                }

                cout << " ";
            }
            cout << endl;
        }
    }
};

int main()
{
   cout << "Which symbol x or o,  x being the first player \n";
    TicTacToe game;
    game.play();
    return 0;
}