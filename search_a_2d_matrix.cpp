// https://oj.leetcode.com/problems/search-a-2d-matrix/
// Date: Nov 15, 2014

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    bool searchMatrix(vector<vector<int> > &matrix, int target)
    {
        int m = matrix.size();
        int n = matrix[0].size();

        // first identify the row which could possibly have the target
        int row_i = 0;
        int row_j = m-1;
        int row_selected;
        bool flag_target = false;

        while (row_i <= row_j)
        {
            int row_mid = (row_i + row_j)/2;

            if (target < matrix[row_mid][0])
            {
                row_j = row_mid - 1;
            }
            else if (matrix[row_mid][n-1] < target)
            {
                row_i = row_mid + 1;
            }
            else
            {
                // target could be in this row
                row_selected = row_mid;
                flag_target = true;
                break;
            }
        }

        if (flag_target == false)
        {
            return flag_target;
        }

        // Now check if the target is present in selected row
        flag_target = false;
        int col_i = 0;
        int col_j = n-1;

        while (col_i <= col_j)
        {
            int col_mid = (col_i + col_j)/2;

            if (target < matrix[row_selected][col_mid])
            {
                col_j = col_mid-1;
            }
            else if (matrix[row_selected][col_mid] < target)
            {
                col_i = col_mid+1;
            }
            else
            {
                flag_target = true;
                break;
            }
        }

        return flag_target;
    }
};

int main(int argc, char* argv[])
{
    vector<vector<int> > matrix;
    matrix.reserve(3);

    int arr[] = {1, 3, 5, 7};
    vector<int> vec(arr, arr+sizeof(arr)/sizeof(arr[0]));
    matrix.push_back(vec);
    int arr1[] = {10, 11, 16, 20};
    vector<int> vec1(arr1, arr1+sizeof(arr1)/sizeof(arr1[0]));
    matrix.push_back(vec1);
    int arr2[] = {23, 30, 34, 50};
    vector<int> vec2(arr2, arr2+sizeof(arr2)/sizeof(arr2[0]));
    matrix.push_back(vec2);
    //cout << matrix[0][2] << " : " << matrix[1][2] << " : " << matrix[2][2] << endl;

    Solution sln;
    bool flag = sln.searchMatrix(matrix, 0);

    return 0;
}
