/*
Let us describe the problem in one dimensional space. We have in total N 
skyscrapers aligned from left to right. The i-th skyscraper has a height of Hi. 
A flying route can be described as (i,j) with i != j, which means, Jim starts 
his HZ42 at the top of the skyscraper i and lands on the skyscraper j. Since 
HZ42 can only fly horizontally, Jim will remain at the height Hi only. Thus 
the path can be valid, only if each of the skyscrapers is not strictly greater 
than Hi and if the height of the skyscraper he starts from and arrives on have 
the same height (Hi = Hj).

Help Jim in counting the number of valid paths represented by ordered pairs.

Input Format: The first line contains N, the number of skyscrapers. The next 
line contains N space separated integers representing the heights of the 
skyscrapers.

Output Format: Print an integer that denotes the number of valid routes.

Sample Input 1:
6
3 2 1 2 3 3

Sample Output 1:
8


Sample Input 2:
3
1 1000 1

Sample Output 2:
0

*/

#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// Complete the solve function below.
uint64_t solve(vector<int> arr) {

    stack<pair<int,uint32_t>> s;
    uint64_t cnt(0);
    for(int h : arr)
    {
        if(!s.empty() && h > s.top().first)
            s.pop();

        if(!s.empty() && h == s.top().first)
        {
            cnt += ++s.top().second;
        }
        else
            s.push(make_pair(h,(uint32_t)0));
    }    
    return cnt * 2;
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

