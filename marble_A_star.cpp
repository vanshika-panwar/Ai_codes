// A STAR    (PATH COST+HEURISTIC VAL) HEURISTIC FUN IS -MINIMUM NO OF ISOLATED MARBLES
#include <bits/stdc++.h>
using namespace std;
map<vector<vector<int>>, bool> visited;
vector<vector<int>> goal = {
    {2, 2, 0, 0, 0, 2, 2},
    {2, 2, 0, 0, 0, 2, 2},
    {0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0},
    {2, 2, 0, 0, 0, 2, 2},
    {2, 2, 0, 0, 0, 2, 2}};
stack<int> steps;
vector<vector<int>> board = {
    {2, 2, 0, 0, 0, 2, 2},
    {2, 2, 0, 0, 0, 2, 2},
    {0, 0, 1, 0, 0, 0, 0},
    {1, 1, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 0},
    {2, 2, 0, 1, 0, 2, 2},
    {2, 2, 0, 0, 0, 2, 2}};
class node
{
public:
    vector<vector<int>> state;
    vector<node *> child;
    node *parent;
    int path_cost;
    int h_n;
    node() // default constructor
    {
        for (int i = 0; i < 7; i++)
        {
            vector<int> temp;
            for (int j = 0; j < 7; j++)
            {
                temp.push_back(board[i][j]);
            }
            state.push_back(temp);
        }
        parent = NULL;
        path_cost = 0;
        h_n = 28;
    }
    node(vector<vector<int>> ar, node *p, int path_cst, int h_val) //parametrized constructor
    {
        for (int i = 0; i < ar.size(); i++)
        {
            vector<int> temp;
            for (int j = 0; j < ar[0].size(); j++)
            {
                temp.push_back(ar[i][j]);
            }
            this->state.push_back(temp);
        }
        this->parent = p;
        this->path_cost = path_cst + 1;
        this->h_n = h_val;
    }
    bool is_valid_index(int x, int y)
    {
        if (x >= 0 and x < 7 and y >= 0 and y < 7)
            return true;
        else
        {
            return false;
        }
    }
    int compute_h_val(vector<vector<int>> temp) //Heuristic function  (minimum no of isolated pegs)
    {
        int ct = 0;
        int flag = 0;
        for (int i = 0; i < 7; i++)
        {
            for (int j = 0; j < 7; j++)
            {
                if (temp[i][j] == 1)
                {
                    flag = 0;
                    if (is_valid_index(i + 1, j))
                    {
                        if (temp[i + 1][j] == 0)
                        {
                            flag = 1;
                        }
                    }
                    if (is_valid_index(i - 1, j))
                    {
                        if (temp[i - 1][j] == 0)
                        {
                            flag = 1;
                        }
                    }
                    if (is_valid_index(i, j + 1))
                    {
                        if (temp[i][j + 1] == 0)
                        {
                            flag = 1;
                        }
                    }
                    if (is_valid_index(i, j - 1))
                    {
                        if (temp[i][j - 1] == 0)
                        {
                            flag = 1;
                        }
                    }
                    if (flag == 0)
                        ct += 1;
                }
            }
        }
        return ct;
    }
    bool isvalid(vector<vector<int>> temp_board, int row, int col, int dir)
    {
        if (row >= 0 && row < 7 && col >= 0 && col < 7)
        {
            if (temp_board[row][col] == 1)
            {
                switch (dir)
                {
                case 1: //UP
                    if (row - 2 >= 0)
                    {
                        if (temp_board[row - 1][col] == 1 && temp_board[row - 2][col] == 0)
                            return true;
                    }
                    break;
                case 2: //DOWN
                    if (row + 2 < 7)
                    {
                        if (temp_board[row + 1][col] == 1 && temp_board[row + 2][col] == 0)
                            return true;
                    }
                    break;
                case 3: //LEFT
                    if (col - 2 >= 0)
                    {
                        if (temp_board[row][col - 1] == 1 && temp_board[row][col - 2] == 0)
                            return true;
                    }
                    break;
                case 4: //RIGHT
                    if (col + 2 < 7)
                    {
                        if (temp_board[row][col + 1] == 1 && temp_board[row][col + 2] == 0)
                            return true;
                    }
                    break;
                default:
                    return false;
                    break;
                } //end switch
            }
        }
        return false;
    }
    void jump(vector<vector<int>> &temp, int a, int b, int dir)
    {
        switch (dir)
        {
        case 1: //N
            temp[a][b] = 0;
            temp[a - 1][b] = 0;
            temp[a - 2][b] = 1;
            break;
        case 2: //S
            temp[a][b] = 0;
            temp[a + 1][b] = 0;
            temp[a + 2][b] = 1;
            break;
        case 4: //E
            temp[a][b] = 0;
            temp[a][b + 1] = 0;
            temp[a][b + 2] = 1;
            break;
        case 3: //W
            temp[a][b] = 0;
            temp[a][b - 1] = 0;
            temp[a][b - 2] = 1;
            break;
        default:
            cout << "qwerty";
            break;
        }
    }
    void successor()
    {
        for (int a = 0; a < 7; a++)
        {
            for (int b = 0; b < 7; b++)
            {
                for (int c = 1; c <= 4; c++)
                {
                    if (isvalid(this->state, a, b, c))
                    {
                        vector<vector<int>> hold;
                        for (int i = 0; i < 7; i++)
                        {
                            vector<int> tempp;
                            for (int j = 0; j < 7; j++)
                            {
                                tempp.push_back(this->state[i][j]);
                            }
                            hold.push_back(tempp);
                        }
                        jump(hold, a, b, c);
                        int heu_val = compute_h_val(hold);
                        node *c = new node(hold, this, this->path_cost + 1, heu_val);
                        this->child.push_back(c);
                    }
                }
            }
        }
    }
};
int nrpos = 0;
bool visit(vector<vector<int>> a)
{
    if (visited[a] == true)
        return true;
    else
        return false;
}
bool isGoal(vector<vector<int>> a) // checks for the goal state
{
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            if (a[i][j] != goal[i][j])
                return false;
        }
    }
    return true;
}
typedef pair<node *, int> pd;
struct myComp
{
    constexpr bool operator()(
        pair<node *, int> const &a,
        pair<node *, int> const &b)
        const noexcept
    {
        return a.second > b.second;
    }
};
void showboard(vector<vector<int>> board)
{
    int n;
    cout << endl;
    for (int a = 0; a < 7; a++)
    {
        for (int b = 0; b < 7; b++)
        {
            n = board[a][b];
            if (n == 2)
                cout << " ";
            else
                cout << n;
        }
        cout << endl;
    }
}
void printsolution(node *n)
{
    cout << "\nPath  followed is :" << endl;
    stack<node *> temp1;
    stack<node *> temp2;
    while (n != NULL)
    {
        temp2.push(n);
        temp1.push(n);
        n = n->parent;
    }
    int path_length = 0;
    while (!temp1.empty())
    {
        cout << endl;
        showboard(temp1.top()->state);
        temp1.pop();
        cout << endl;
        path_length++;
    }
    cout << "\nPath length is" << path_length - 1;
}

int main()
{
    node *start = new node();
    start->successor();
    int ct = 0;
    priority_queue<pd, vector<pd>, myComp> frontier;
    set<node *> explored;
    frontier.push(make_pair(start, start->h_n + start->path_cost));
    while (!frontier.empty())
    {
        node *n = frontier.top().first;
        if (isGoal(n->state))
        {
            cout << "NO of nodes explored are " << ct << endl;
            cout << "Goal state is:" << endl;
            showboard(goal);
            cout << "start state is:" << endl;
            showboard(start->state);
            printsolution(n);
            return 0;
        }
        else
        {
            showboard(n->state);
            explored.insert(n);
            visited[n->state] = true;
            ct++;
            n->successor();
            vector<node *>::iterator itr;
            for (itr = n->child.begin(); itr != n->child.end(); itr++)
            {
                vector<vector<int>> temp = (*itr)->state;
                if (!visit(temp))
                {
                    frontier.push(make_pair(*itr, ((*itr)->h_n) + (*itr)->path_cost));
                }
            }
        }
        frontier.pop();
    }
}