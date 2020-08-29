/*
There are values to represent nodes in a graph. They are divided into two sets G and B. 
Each set has exactly N values. Set is represent by G can contain any value between 
1 to N (inclusive). Set represented by B can contain any value between N+1 to 2N (inclusive). 
Same value can be chosen any number of times.

Your task is to print the number of vertices in the smallest and the largest connected 
components of the graph.

Note Single nodes should not be considered in the answer.

Input Format: First line contains an integer N. Each of the next lines contain two 
space-separated integers, Gi Bi.

Output Format: Print two space separated integers, the number of vertices in the smallest 
and the largest components.

Sample Input:
5
1 6 
2 7
3 8
4 9
2 6

Sample Output:
2 4

*/



#include <bits/stdc++.h>

using namespace std;

//Disjoined set functions:
//parent of the set has negative number
//positive number is index of the connected element of the set
int get_parent(vector<int>& s, int a)
{
    while(s[a]>0)
        a = s[a];

    return a;
}

//union:
void u(vector<int>& s, int a, int b)
{
     if(a==b)
        return;

     //if(a>b)
     //   swap(a,b);

    int p_a(get_parent(s, a)), p_b(get_parent(s, b));

    if(p_a == p_b)
        return;

    if(s[p_a] <= s[p_b])
    {
        s[p_a] += s[p_b];
        s[p_b] = p_a;
    }
    else
    {
        s[p_b] += s[p_a];
        s[p_a] = p_b;
    }
}

vector<int> componentsInGraph(vector<vector<int>> gb) 
{
    int N = 15000;
    vector<int> s((N*2) +1, -1); //storage for disjoined set, all are parents of itselves (-1)

	//perform unions on pairs:
    for(auto p : gb)
       u(s, p[0], p[1]);


    vector<int> min_max={INT_MAX, INT_MIN};
    for(int i=1; i<=N; ++i)
    {
        if(s[i] < -1)
        {//any negative number < -1 is a parent of the set
            int v = abs(s[i]);
            if(min_max[0]>v)
                min_max[0] = v;
            
            if(min_max[1] < v)
                min_max[1] = v;
        }
    }

    if(min_max[0] == INT_MAX)
        min_max[0] = 0;

    if(min_max[1] == INT_MIN)
        min_max[1] = 0;

    return min_max;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<vector<int>> gb(n);
    for (int gb_row_itr = 0; gb_row_itr < n; gb_row_itr++) {
        gb[gb_row_itr].resize(2);

        for (int gb_column_itr = 0; gb_column_itr < 2; gb_column_itr++) {
            cin >> gb[gb_row_itr][gb_column_itr];
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    vector<int> result = componentsInGraph(gb);

    for (int SPACE_itr = 0; SPACE_itr < result.size(); SPACE_itr++) {
        fout << result[SPACE_itr];

        if (SPACE_itr != result.size() - 1) {
            fout << " ";
        }
    }

    fout << "\n";

    fout.close();

    return 0;
}
