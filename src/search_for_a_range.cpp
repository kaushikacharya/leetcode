// https://oj.leetcode.com/problems/search-for-a-range/
// Date: Nov 12, 2014

#include<iostream>
#include<vector>

using namespace std;

class Solution {
public:
    vector<int> searchRange(int A[], int n, int target)
    {
        target_ = target;
        vector<int> inputVec(A, A+n);
        vec_ = inputVec;

        int lowerBound = searchLowerBound(0,n-1);
        int upperBound = (lowerBound == -1) ? -1 : searchUpperBound(0,n-1);

        vector<int> vec;
        vec.push_back(lowerBound);
        vec.push_back(upperBound);

        return vec;
    }
private:
    int target_;
    vector<int> vec_;
private:
    // recursive, complexity O(log n)
    int searchLowerBound(int i, int j)
    {
        if (i == j)
        {
            if (vec_[i] == target_)
            {
                return i;
            }
            else
            {
                return -1;
            }
        }
        else if (j < i)
        {
            return -1;
        }

        int mid = (i+j)/2;

        if (vec_[mid] < target_)
        {
            return searchLowerBound(mid+1,j);
        }
        else if (vec_[mid] > target_)
        {
            return searchLowerBound(i,mid-1);
        }
        else
        {
            return searchLowerBound(i,mid);
        }
    }

    int searchUpperBound(int i, int j)
    {
        if (i == j)
        {
            if (vec_[i] == target_)
            {
                return i;
            }
            else
            {
                return -1;
            }
        }
        else if (j < i)
        {
            return -1;
        }

        int mid = (i+j+1)/2;

        if (vec_[mid] < target_)
        {
            return searchUpperBound(mid+1,j);
        }
        else if (vec_[mid] > target_)
        {
            return searchUpperBound(i,mid-1);
        }
        else
        {
            return searchUpperBound(mid,j);
        }
    }
};


int main(int argc, char* argv[])
{
    int arr[] = {5, 7, 7, 8, 8, 10};
    int target = 8;

    Solution sln;
    vector<int> vec = sln.searchRange(arr, sizeof(arr)/sizeof(arr[0]), target);

    return 0;
}
