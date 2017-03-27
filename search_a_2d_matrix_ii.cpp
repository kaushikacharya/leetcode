// https://leetcode.com/problems/search-a-2d-matrix-ii/#/description
// Mar 26, 2017

#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

class Solution
{
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target)
    {
        // assign values to class variables
        target_ = target;
        nrow_ = matrix.size();

        // case: check null matrix
        if (nrow_ == 0)
        {
            return false;
        }
        ncol_ = matrix[0].size();
        if (ncol_ == 0)
        {
            return false;
        }

        // cout << "nrow: " << nrow_ << " : ncol: " << ncol_ << endl;
        bool found_flag = searchSubMatrix(matrix, 0, nrow_-1, 0, ncol_-1);

        return found_flag;
    }
private:
    bool searchSubMatrix(vector<vector<int>>& matrix, unsigned int rowStart, unsigned int rowEnd, unsigned int colStart, unsigned int colEnd)
    {
        // search target_ in the sub-matrix: matrix[rowStart:rowEnd, colStart:colEnd]
        // Note: inclusive of both end i.e. from rowStart till rowEnd(inclusive) and similarly with columns

        // case: sub-matrix is a single element
        if ( (rowStart==rowEnd) && (colStart==colEnd) )
        {
            return matrix[rowStart][colStart] == target_;
        }
        // cases: check if target_ is less than smallest element of sub-matrix or greater than biggest element of sub-matrix
        if (target_ < matrix[rowStart][colStart])
        {
            return false;
        }
        if (matrix[rowEnd][colEnd] < target_)
        {
            return false;
        }

        // Pick the value at the center of the sub-matrix
        // Based on whether this value is <,=,> target_, we will divide the sub-matrix into further
        // sub-matrices and search those sub-matrices (i.e. divide and conquer approach)
        unsigned int rowMid = (rowStart + rowEnd)/2;
        unsigned int colMid = (colStart + colEnd)/2;
        int x = matrix[rowMid][colMid];

        if (x == target_)
        {
            return true;
        }

        bool found_flag = false;
        if (target_ < x)
        {
            // target_ won't be present in lower right portion of sub-matrix i.e. the one starting from (rowMid,colMid)
            if (colStart < colMid)
            {
                if (rowStart < rowMid)
                {
                    // There are two ways of dividing the rest of the sub-matrix for further search.
                    // Choose the one which will divide the sub-matrix closer to half

                    // method #1: (a) entire left (b) top right quadrant
                    int diffMethod1 = abs( ( (rowEnd - rowStart + 1)*(colMid - colStart) ) - ( (rowMid - rowStart)*(colEnd - colMid + 1) ) );
                    // method #2: (a) lower left quadrant (b) entire top
                    int diffMethod2 = abs( ((colEnd - colStart + 1)*(rowMid - rowStart)) - ((colMid - colStart)*(rowEnd - rowMid + 1)) );

                    if (diffMethod1 < diffMethod2)
                    {
                        // Method #1 provides better split of sub-matrix
                        found_flag = searchSubMatrix(matrix, rowStart, rowEnd, colStart, colMid-1);

                        if (!found_flag)
                        {
                            found_flag = searchSubMatrix(matrix, rowStart, rowMid-1, colMid, colEnd);
                        }
                    }
                    else
                    {
                        // Method #2 provides better split of sub-matrix
                        found_flag = searchSubMatrix(matrix, rowStart, rowMid-1, colStart, colEnd);

                        if (!found_flag)
                        {
                            found_flag = searchSubMatrix(matrix, rowMid, rowEnd, colStart, colMid-1);
                        }
                    }
                }
                else
                {
                    // case: rowStart == rowMid
                    // Only left portion of sub-matrix needs to be searched
                    found_flag = searchSubMatrix(matrix, rowStart, rowEnd, colStart, colMid-1);
                }
            }
            else
            {
                // case: colStart == colMid
                if (rowStart < rowMid)
                {
                    found_flag = searchSubMatrix(matrix, rowStart, rowMid-1, colMid, colEnd);
                }
            }
        }
        else
        {
            // target_ > x
            // target_ won't be present in upper left portion of sub-matrix i.e. the one ending at (rowMid,colMid)
            if (colMid < colEnd)
            {
                if (rowMid < rowEnd)
                {
                    // There are two ways of dividing the rest of the sub-matrix for further search.
                    // Choose the one which will divide the sub-matrix closer to half

                    // method #1: (a) top right portion (b) entire lower half
                    int diffMethod1 = abs( ((rowMid-rowStart+1)*(colEnd-colMid)) - ((rowEnd-rowMid)*(colEnd-colStart+1)) );
                    // method #2: (a) entire right portion (b) lower left portion
                    int diffMethod2 = abs( ((rowEnd-rowStart+1)*(colEnd-colMid)) - ((rowEnd-rowMid)*(colMid-colStart+1)) );

                    if (diffMethod1 < diffMethod2)
                    {
                        // Method #1 provides better split of sub-matrix
                        found_flag = searchSubMatrix(matrix, rowStart, rowMid, colMid+1, colEnd);

                        if (!found_flag)
                        {
                            found_flag = searchSubMatrix(matrix, rowMid+1, rowEnd, colStart, colEnd);
                        }
                    }
                    else
                    {
                        // Method #2 provides better split of sub-matrix
                        found_flag = searchSubMatrix(matrix, rowStart, rowEnd, colMid+1, colEnd);

                        if (!found_flag)
                        {
                            found_flag = searchSubMatrix(matrix, rowMid+1, rowEnd, colStart, colMid);
                        }
                    }
                }
                else
                {
                    // case: rowMid == rowEnd
                    // Only right portion of the sub-matrix needs to be searched
                    found_flag = searchSubMatrix(matrix, rowStart, rowMid, colMid+1, colEnd);
                }
            }
            else
            {
                // case: colMid == colEnd
                if (rowMid < rowEnd)
                {
                    found_flag = searchSubMatrix(matrix, rowMid+1, rowEnd, colStart, colMid);
                }
            }
        }

        return found_flag;
    }
private:
    unsigned int nrow_;
    unsigned int ncol_;
    int target_;
};

int main(int argc, char** argv)
{
    vector<vector<int> > matrix;
/*
    {
        int arr[5] = {1,4,7,11,15};
        vector<int> vec(arr, arr+sizeof(arr)/sizeof(arr[0]));
        matrix.push_back(vec);
    }
    {
        int arr[5] = {2,   5,  8, 12, 19};
        vector<int> vec(arr, arr+sizeof(arr)/sizeof(arr[0]));
        matrix.push_back(vec);
    }
    {
        int arr[5] = {3,   6,  9, 16, 22};
        vector<int> vec(arr, arr+sizeof(arr)/sizeof(arr[0]));
        matrix.push_back(vec);
    }
    {
        int arr[5] = {10, 13, 14, 17, 24};
        vector<int> vec(arr, arr+sizeof(arr)/sizeof(arr[0]));
        matrix.push_back(vec);
    }
    {
        int arr[5] = {18, 21, 23, 26, 30};
        vector<int> vec(arr, arr+sizeof(arr)/sizeof(arr[0]));
        matrix.push_back(vec);
    }
*/
    int target = 20;
    Solution sln;
    bool found_flag = sln.searchMatrix(matrix, target);
    cout << "found: " << found_flag << endl;

    return 0;
}

/*
It seems better to take 3 equal parts as done in
https://discuss.leetcode.com/topic/33240/java-an-easy-to-understand-divide-and-conquer-method
instead of 2 unequal parts(which I have done)

TBD: O(m+n) solution: https://discuss.leetcode.com/topic/20064/my-concise-o-m-n-java-solution
*/
