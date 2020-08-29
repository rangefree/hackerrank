/*

*/

#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

int get_parent(const vector<int>& v, int a)
{
    while(v[a]>-1)
        a=v[a];

    return a;
}

bool u(vector<int>& v, int a, int b, bool no_loops = true)
{
    size_t p_a(get_parent(v, a)), p_b(get_parent(v, b));
    
    if(p_a == p_b)
    {
        if(no_loops)
            return false;
        else 
            return true;
    }
    
    v[p_a] += v[p_b];
    v[p_b] = p_a;
    return true;
}


// Complete the roadsAndLibraries function below.
long roadsAndLibraries(int n, int c_lib, int c_road, vector<vector<int>> cities) {
    vector<int> v(n, -1);
    for(auto c : cities)
    {
         u(v, c[0]-1, c[1]-1);
    }

    long cost(0);
    for(int n : v)
    {
        if(n<0)
        {
            if(n == -1)
                cost += c_lib; //no roads to the city => build library
            else
                cost += min(abs(n)*c_lib, c_lib + (abs(n+1)*c_road)); n represent count of cities and n-1 roads, choose whatever smaller
        }
    }
    return cost;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int q;
    cin >> q;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string nmC_libC_road_temp;
        getline(cin, nmC_libC_road_temp);

        vector<string> nmC_libC_road = split_string(nmC_libC_road_temp);

        int n = stoi(nmC_libC_road[0]);

        int m = stoi(nmC_libC_road[1]);

        int c_lib = stoi(nmC_libC_road[2]);

        int c_road = stoi(nmC_libC_road[3]);

        vector<vector<int>> cities(m);
        for (int i = 0; i < m; i++) {
            cities[i].resize(2);

            for (int j = 0; j < 2; j++) {
                cin >> cities[i][j];
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        long result = roadsAndLibraries(n, c_lib, c_road, cities);

        fout << result << "\n";
    }

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
