// https://oj.leetcode.com/problems/find-minimum-in-rotated-sorted-array/
// Date: Nov 27, 2014

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int findMin(vector<int> &vec)
    {
        int n = vec.size();

        if (vec[0] < vec[n-1])
        {
            // case: array remains sorted i.e. full rotation.
            return vec[0];
        }

        // divide and conquer approach
        int min_index = 0;
        int max_index = n-1;

        while (true)
        {
            if ((max_index-min_index) <= 1)
            {
                min_index = max_index;
                break;
            }

            int mid_index = (min_index + max_index)/2;

            if (vec[min_index] < vec[mid_index])
            {
                min_index = mid_index;
            }
            else
            {
                max_index = mid_index;
            }
        }

        return vec[min_index];
    }
};

int main(int argc, char* argv[])
{
    int arr[] = {4,5,6,7,0,2};
    vector<int> vec(arr, arr+sizeof(arr)/sizeof(arr[0]));
    Solution sln;
    int min_val = sln.findMin(vec);
    cout << min_val << endl;
    return 0;
}
