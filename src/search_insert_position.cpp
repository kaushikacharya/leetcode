// https://oj.leetcode.com/problems/search-insert-position/
// Date: Nov 26, 2014

#include <iostream>

using namespace std;

class Solution {
public:
    int searchInsert(int A[], int n, int target)
    {
        int min_index = 0;
        int max_index = n-1;
        int pos;

        while (true)
        {
            if (target <= A[min_index])
            {
                pos = min_index;
                break;
            }
            if (target > A[max_index])
            {
                pos = max_index + 1;
                break;
            }

            int mid_index = (min_index + max_index)/2;

            if (target <= A[mid_index])
            {
                max_index = mid_index;
            }
            else
            {
                min_index = mid_index + 1;
            }
        }

        return pos;
    }
};


int main(int argc, char* argv[])
{
    int arr[] = {1,3,5,8,9};
    int n = sizeof(arr)/sizeof(arr[0]);
    int target = 9;
    Solution sln;
    int pos = sln.searchInsert(arr,n,target);
    return 0;
}
