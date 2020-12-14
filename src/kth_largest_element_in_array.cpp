// https://leetcode.com/problems/kth-largest-element-in-an-array/
// May 13, 2016

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k)
    {
        vecNums_.reserve(nums.size());
        for (vector<int>::iterator it = nums.begin(); it != nums.end(); ++it)
        {
            vecNums_.push_back(*it);
        }

        int n = nums.size();
        int p = 0;
        int q = nums.size()-1;
        int pivot_pos;

        while (true)
        {
            pivot_pos = partitionNums(p,q);
            if (pivot_pos == (n-k))
            {
                break;
            }
            else if (pivot_pos < (n-k))
            {
                p = pivot_pos+1;
            }
            else
            {
                q = pivot_pos-1;
            }
        }

        return vecNums_[pivot_pos];
    }
private:
    // This picks vecNums_[leftPos] as pivot and places it in appropriate position
    int partitionNums(int leftPos, int rightPos)
    {
        if (leftPos == rightPos)
        {
            return leftPos;
        }

        int pivot = vecNums_[leftPos];
        int i = leftPos + 1;

        for (int j = leftPos+1; j < (rightPos+1); ++j)
        {
            if (vecNums_[j] <= pivot)
            {
                // swap vecNums_[i], vecNums_[j]
                int temp = vecNums_[i];
                vecNums_[i] = vecNums_[j];
                vecNums_[j] = temp;
                ++i;
            }
        }

        // now swap pivot with the elem at pivot's appropriate position
        vecNums_[leftPos] = vecNums_[i-1];
        vecNums_[i-1] = pivot;

        return (i-1);
    }
private:
    vector<int> vecNums_;
};

int main(int argc, char* argv[])
{
    vector<int> vecNums = {5};
    int k = 1;
    Solution sln;
    int kth_largest = sln.findKthLargest(vecNums, k);
    cout << "kth largest element: " << kth_largest << endl;
    return 0;
}
