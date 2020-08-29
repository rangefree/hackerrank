/*
You are given a list of N numbers A1,A2,..., An. For each element at position i (1<=1<=N), we define Left(i) and Right(1) as:
Left(i) = closest index j such that j < i and Aj>Ai. If no such j exists then Left(i) = 0.
Right(i) = closest index k such that k > i and Ak>Ai. If no such k exists then Right(i) = 0.

We define IndecProduct(i) = Left(i) * Right(i). You need to find out the maximum among all i.

Input Format: The first line contains an integer N, the number of integers. The next line contains the N integers 
describing the list a[1..N].

Output Format: Output the maximum IndecProduct among all indices from 1 to N.

Sample Input:
5
5 4 3 4 5

Sample Output:
8

Expl:
IndecProduct(1) = 0
IndecProduct(2) = 1x5 = 5
IndecProduct(3) = 2x4 = 8
IndecProduct(4) = 1x5 = 5
IndecProduct(5) = 0
*/

#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);


// Complete the solve function below.
uint64_t solve(vector<int> arr) 
{
    if(arr.size() < 3)
    return 0;

    size_t N(arr.size());
    vector<size_t> l(N,0), r(N,0); //Holds Left(i) and Right(i)
    stack<size_t> s; 
    uint64_t p(0);

	// find all Left(i):
    for(int32_t i=0; i<N; ++i )
    {
	//go to first bigger than on the stack:
        while(!s.empty() && arr[s.top()]<=arr[i])
            s.pop();
        
        if(!s.empty())
        {//we found index:
            l[i] = s.top()+1; // Left(i) starts from 1 not 0
            //cout << "l[" << i << "] = " << l[i] << endl;
        }

        s.push(i); //put self on the stack
    }

    while(!s.empty()) s.pop();

	//Find all Right(i):
    for(int32_t i=N-1; i>=0; --i )
    {
        while(!s.empty() && arr[s.top()]<=arr[i])
            s.pop();
        
        if(!s.empty())
        {
            r[i] = s.top()+1;
            //cout << "r[" << i << "] = " << r[i] << endl;
        }
        s.push(i);
    }

    for(int32_t i=0; i<N; ++i)
    {
        if(l[i] && r[i])
            p = max(p, (uint64_t)l[i] * r[i]);
    }
    return p;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int arr_count;
    cin >> arr_count;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string arr_temp_temp;
    getline(cin, arr_temp_temp);

    vector<string> arr_temp = split_string(arr_temp_temp);

    vector<int> arr(arr_count);

    for (int arr_itr = 0; arr_itr < arr_count; arr_itr++) {
        int arr_item = stoi(arr_temp[arr_itr]);

        arr[arr_itr] = arr_item;
    }

    uint64_t result = solve(arr);

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
