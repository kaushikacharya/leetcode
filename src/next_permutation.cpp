// https://oj.leetcode.com/problems/next-permutation/
// Date: Dec 16, 2014

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    void nextPermutation(vector<int> &vec)
    {
        if (vec.size() <= 1)
        {
            return;
        }
        // start iterating backwards
        int st_pos = vec.size()-2;
        while (st_pos > 0)
        {
            if (vec[st_pos] < vec[st_pos+1])
            {
                break;
            }
            else
            {
                --st_pos;
            }
        }


        if (vec[st_pos] < vec[st_pos+1])
        {
            // find the smallest elem in vec[st_pos,...,end] which is > vec[st_pos]
            // Then swap these elements
            for (int i = vec.size()-1; i != st_pos; --i)
            {
                if (vec[st_pos] < vec[i])
                {
                    swap(vec[st_pos], vec[i]);
                    break;
                }
            }
            /*
            int swap_pos = vec.size()-1;
            for (int i=(vec.size()-1); i >= (st_pos+1); --i)
            {
                if ((vec[i] > vec[st_pos]) && (vec[i] < vec[swap_pos]))
                {
                    swap_pos = i;
                }
            }
            swap(vec[st_pos], vec[swap_pos]);
            */
            ++st_pos;
        }

        // Now reverse the elements
        int en_pos = vec.size()-1;
        for (int i=0; i <= (en_pos-st_pos)/2; ++i)
        {
            swap(vec[st_pos+i], vec[en_pos-i]);
        }
    }
};

int main(int argc, char* argv[])
{
    int arr[] = {1,1,5};
    vector<int> vec(arr, arr+sizeof(arr)/sizeof(arr[0]));
    Solution sln;
    sln.nextPermutation(vec);

    for (vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it == vec.begin())
        {
            cout << *it;
        }
        else
        {
            cout << "," << *it;
        }
    }

    return 0;
}
