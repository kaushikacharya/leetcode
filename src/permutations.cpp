// https://oj.leetcode.com/problems/permutations/
// Date: Dec 06, 2014

#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int> > permute(vector<int> &arr)
    {
        vector<vector<int> > vec_permutation;
        if (arr.size() == 0)
        {
            return vec_permutation;
        }

        vector<bool> vec_visited;
        vector<int> vec_path; // we store the index here not the elements of arr

        vec_visited.reserve(arr.size());
        vec_path.reserve(arr.size());

        for (int i=0; i != arr.size(); ++i)
        {
            vec_visited.push_back(false);
            vec_path.push_back(0); // dummy value
        }

        stack<pair<int,int> > stk; // first element - index, second element - position
        for (int i=0; i != arr.size(); ++i)
        {
            stk.push(make_pair(i,0));
        }

        int prev_pos = 0;
        while (!stk.empty())
        {
            pair<int,int> elem = stk.top();
            stk.pop();

            int index = elem.first;
            int pos = elem.second;

            if (pos < prev_pos)
            {
                // in the previous iteration we found one permutation
                // reset the visited flag for the elements of the positions which will be renewed
                for (int i=pos; i <= prev_pos; ++i)
                {
                    vec_visited[vec_path[i]] = false;
                }
            }

            vec_path[pos] = index;

            if (pos == (arr.size()-1))
            {
                vector<int> permutation;
                permutation.reserve(arr.size());
                for (int i=0; i != arr.size(); ++i)
                {
                    permutation.push_back(arr[vec_path[i]]);
                }
                vec_permutation.push_back(permutation);
            }
            else
            {
                // push elements in the stack
                for (int i = 0; i != arr.size(); ++i)
                {
                    if ((i != index) && !vec_visited[i])
                    {
                        stk.push(make_pair(i,pos+1));
                    }
                }
            }

            vec_visited[index] = true;
            prev_pos = pos;
        }

        return vec_permutation;
    }
};

int main(int argc, char* argv[])
{
    int arr[] = {1,2,3,5};
    vector<int> vec(arr, arr+sizeof(arr)/sizeof(arr[0]));

    Solution sln;
    vector<vector<int> > permutations = sln.permute(vec);

    for (int i = 0; i != permutations.size(); ++i)
    {
        cout << "permutation #" << i << " ";

        for (int j = 0; j != permutations[i].size(); ++j)
        {
            if (j > 0)
            {
                cout << ",";
            }
            cout << permutations[i][j];
        }

        cout << endl;
    }

    return 0;
}
