/*
A queue is an abstract data type that maintains the order in which elements were added to it, 
allowing the oldest elements to be removed from the front and new elements to be added to the 
rear. This is called a First-In-First-Out (FIFO) data structure because the first element added 
to the queue (i.e., the one that has been waiting the longest) is always the first one to be 
removed.

A basic queue has the following operations:
    Enqueue: add a new element to the end of the queue.
    Dequeue: remove the element from the front of the queue and return it.

In this challenge, you must first implement a queue using two stacks. Then process queries, where 
each query is one of the following 3 types:
1 x: Enqueue element into the end of the queue.
2: Dequeue the element at the front of the queue.
3: Print the element at the front of the queue.

Input Format: The first line contains a single integer, N, denoting the number of queries.
Each line of the subsequent lines contains a single query in the form described in the problem 
statement above. All three queries start with an integer denoting the query type, but only 
query 1 is followed by an additional space-separated value, X, denoting the value to be enqueued.

Sample Input:
10
1 42
2
1 14
3
1 28
3
1 60
1 78
2
2

Sample Output:
14
14

*/


#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

template <class T>
class Stack
{
    vector<T> v;
    public:
    T& front(){return v.back();}
    T& back(){return v.front();}
    size_t size(){return v.size();}
    void push(T&& vv){v.push_back(vv);}
    void push(T&vv){v.push_back(vv);}
    T pop(void){T vv = v.back(); v.pop_back(); return vv;}
};

template<class T>
class Queue
{
    Stack<T> s1;
    Stack<T> s2;
    
    void s2_ready()
    {
        if(s2.size()==0)
            while(s1.size())
                s2.push(s1.pop());
    }

    public:
    T& front(void) 
    {
        s2_ready();
        return s2.front();
    }

    void push(T& vv)
    {
        s1.push(vv);
    }

    T pop(void)
    {
        s2_ready();        
        return s2.pop();
    }
};

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    Queue<long> q;

    int N(0), query(0);
    long x(0);

    cin >> N;
    while(N)
    {
        cin >> query;
        //cout << query << " ";
        switch(query)
        {
            case 1: 
                cin >> x; 
                //cout << x;
                q.push( x);
                break;
            case 2:
                q.pop();
                break;
            case 3:
                cout << q.front() << endl;
            break;
        }
        --N;
        //cout << endl;
    }
    return 0;
}

