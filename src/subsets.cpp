// https://oj.leetcode.com/problems/subsets/
// Date: Nov 20, 2014

#include <iostream>
#include <algorithm>
#include <stack>
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int> > subsets(vector<int> &S)
    {
        vector<vector<int> > vecOfvec;

        vecOfvec.push_back(vector<int>());

        if (S.size() == 0)
        {
            return vecOfvec;
        }

        sort(S.begin(), S.end());

        stack<vector<int> > stk; // this stores the indices not the elements of vector S.
        for (int i=0; i != S.size(); ++i)
        {
            vector<int> vec;
            vec.push_back(i);
            stk.push(vec);
        }

        while (!stk.empty())
        {
            vector<int> elem = stk.top();
            stk.pop();

            vector<int> vec;
            for (vector<int>::iterator it = elem.begin(); it != elem.end(); ++it)
            {
                vec.push_back(S[*it]);
            }
            vecOfvec.push_back(vec);

            int i = elem.back();
            while ((i+1) < S.size())
            {
                vector<int> newElem = elem;
                newElem.push_back(i+1);
                stk.push(newElem);
                ++i;
            }
        }

        return vecOfvec;
    }
};

int main(int argc, char* argv[])
{
    int arr[] = {1,3,0};
    vector<int> vec(arr, arr+sizeof(arr)/sizeof(arr[0]));

    Solution sln;
    vector<vector<int> > sub_sets = sln.subsets(vec);

    cout << "size: " << sub_sets.size() << endl;
    for (int i = 0; i != sub_sets.size(); ++i)
    {
        cout << "elem #" << i << " : ";
        for (int j = 0; j != sub_sets[i].size(); ++j)
        {
            cout << sub_sets[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}

/*
https://oj.leetcode.com/discuss/9213/my-solution-using-bit-manipulation
Tried using bit manipulation but running time N*2^N
*/
