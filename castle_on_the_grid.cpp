/*
Complete the minimumMoves function. It must print an integer denoting the minimum moves required to get from the starting position to the goal.
minimumMoves has the following parameter(s):
    grid: an array of strings representing the rows of the grid
    startX: an integer
    startY: an integer
    goalX: an integer
    goalY: an integer

Input Format
The first line contains an integer N, the size of the array grid.
Each of the next lines contains a string of length N.
The last line contains four space-separated integers, startX, startY, goalX, goalY.

Print an integer denoting the minimum number of steps required to move the castle to the goal position.

Sample Input:
3
.X.
.X.
...
0 0 0 2

Sample Output:
3
*/

#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);
struct node_t
{
    //using state_t = enum{unknown=0, explored, visited};
    //int state;//0-not visited, 1-explored, 2-visited
    int row, col;//my coords
    int p_row, p_col; //parent's coords
    node_t() : //state(0),
        p_row(-1), p_col(-1){};
};

node_t* get_parent(vector<vector<node_t>> &g, node_t* n)
{
    if(n->p_col == -1 || n->p_row == -1)
        return NULL;

    return &g[n->p_row][n->p_col];
}

// Complete the minimumMoves function below.
int minimumMoves(vector<string> grid, int startX, int startY, int goalX, int goalY) {
    int N = grid.size();
    int res = 0;
    vector<vector<node_t>> g(N, vector<node_t>(N));

    queue<node_t*> q;
    vector<pair<int,int>> neigh = {{0,1}, {0,-1}, {1,0}, {-1,0}};//row,col
    int c,r;

    g[startX][startY].row = startX;
    g[startX][startY].col = startY;

    q.push(&g[startX][startY]);
    while(!q.empty())
    {
        //cout << "(" << q.front()->row << "," << q.front()->col << ")" << endl;
        //q.front()->state = 2;//node_t::state_t::visited;
        grid[q.front()->row][q.front()->col] = '+';
        if(q.front()->row == goalX && q.front()->col == goalY)
            break;//we reached target; 

        for(auto n : neigh)
        {
            for(int i=1; i < N; ++i)
            {
                r = q.front()->row + (n.first * i);
                c = q.front()->col + (n.second * i);

                if(r < 0 || r >= N || c < 0 || c >= N || grid[r][c] == 'X')
                    break;

                if(r == goalX && c == goalY )
                {
                    //we got it!
                    res = 1;
                    break;
                }

                //if(g[r][c].state == 0)
                if(grid[r][c] == '.')
                {//unexplored:
                    //g[r][c].state = 1;//node_t::status_t::explored;
                    grid[r][c] = '?';//explored
                    g[r][c].col = c;
                    g[r][c].row = r;
                    g[r][c].p_col = q.front()->col;
                    g[r][c].p_row = q.front()->row;

                    //cout << "  -(" << g[r][c].row << "," << 
                    //    g[r][c].col << ")" << endl;

                    q.push(&g[r][c]);//add neighbour
                }
            }
            if(res == 1)
                break;

        }
        if(res == 1)
            break;

        q.pop();
    }

    if(!q.empty())
    {
        node_t* parent = get_parent(g, q.front());
        while(parent)
        { 
            ++res;
            parent = get_parent(g, parent);
        }
    }
    return res;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<string> grid(n);

    for (int i = 0; i < n; i++) {
        string grid_item;
        getline(cin, grid_item);

        grid[i] = grid_item;
    }

    string startXStartY_temp;
    getline(cin, startXStartY_temp);

    vector<string> startXStartY = split_string(startXStartY_temp);

    int startX = stoi(startXStartY[0]);

    int startY = stoi(startXStartY[1]);

    int goalX = stoi(startXStartY[2]);

    int goalY = stoi(startXStartY[3]);

    int result = minimumMoves(grid, startX, startY, goalX, goalY);

    fout << result << "\n";

    fout.close();

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}

