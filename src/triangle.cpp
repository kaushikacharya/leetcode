// https://leetcode.com/problems/triangle/
// May 05, 2016

#include <iostream>
#include <vector>
#include <limits>

using namespace std;

class Solution {
public:
    int minimumTotal(vector<vector<int> >& triangle)
    {
        int nrow = triangle.size();

        if (nrow == 0)
        {
            return 0;
        }

        vector<int> vecMinTotal, vecMinTotalPrev;
        vecMinTotal.reserve(nrow);
        vecMinTotalPrev.reserve(nrow);

        // initialize min total values for row=0
        for(unsigned int i=0; i != nrow; ++i)
        {
            vecMinTotal.push_back(0);
            vecMinTotalPrev.push_back(0);
        }
        vecMinTotal[0] = triangle[0][0];

        // now compute min total values for row>0
        for (int row=1; row != nrow; ++row)
        {
            for (int col=0; col != nrow; ++col)
            {
                vecMinTotalPrev[col] = vecMinTotal[col];
            }
            for (int col=0; col != row+1; ++col)
            {
                int val = numeric_limits<int>::max();
                // col-1, col, col+1

                if (col > 0)
                {
                    if (vecMinTotalPrev[col-1] < val)
                    {
                        val = vecMinTotalPrev[col-1];
                    }
                }
                if (col < row)
                {
                    if (vecMinTotalPrev[col] < val)
                    {
                        val = vecMinTotalPrev[col];
                    }
                }

                /*
                // Following are not adjacent nodes as explained here:
                // https://leetcode.com/discuss/48478/whats-the-meaning-of-adjacent-numbers-on-the-row-below
                if (col < (row-1))
                {
                    if (vecMinTotalPrev[col+1] < val)
                    {
                        val = vecMinTotalPrev[col+1];
                    }
                }
                */

                vecMinTotal[col] = val + triangle[row][col];
            }

            /*
            cout << "row: " << row << endl;
            for (int col=0; col != nrow; ++col)
            {
                cout << vecMinTotal[col] << " ";
            }
            cout << endl;
            */
        }

        int minTotal = numeric_limits<int>::max();
        for (int row=0; row != nrow; ++row)
        {
            if (vecMinTotal[row] < minTotal)
            {
                minTotal = vecMinTotal[row];
            }
        }

        return minTotal;
    }
};

vector<vector<int> > create_triangle()
{
    vector<vector<int> > triangle;
    int test_case_i = 0;

    switch (test_case_i)
    {
    case 0:
        {
            static const int arr0[] = {2};
            // vector<int> vec0(arr0, arr0+sizeof(arr0)/sizeof(arr0[0]));
            cout << "size of arr0: " << sizeof(arr0)/sizeof(arr0[0]) << endl;
            vector<int> vec0 = {2};
            cout << "size of vec0: " << vec0.size() << endl;
            // vector<int> vec0(1,2);
            triangle.push_back(vec0);

            // vector<int> vec1(2,3);
            // vec1[1] = 4;

            vector<int> vec1 = {3, 4};
            triangle.push_back(vec1);

            // vector<int> vec2(3,6);
            // vec2[1] = 5;
            // vec2[2] = 7;

            vector<int> vec2 = {6, 5, 7};
            triangle.push_back(vec2);

            // vector<int> vec3(4,4);
            // vec3[1] = 1;
            // vec3[2] = 8;
            // vec3[3] = 3;

            vector<int> vec3 = {4, 1, 8, 3};
            triangle.push_back(vec3);

            break;
        }
    case 1:
        {
            vector<int> vec0 = {-1};
            triangle.push_back(vec0);
            vector<int> vec1 = {3,2};
            triangle.push_back(vec1);
            vector<int> vec2 = {-3, 1, -1};
            triangle.push_back(vec2);

            break;
        }
    }

    cout << "triangle: " << endl;
    for (unsigned int i = 0; i != triangle.size(); ++i)
    {
        for(unsigned int j = 0; j != triangle[i].size(); ++j)
        {
            cout << triangle[i][j] << " ";
        }
        cout << endl;
    }
    return triangle;
}

int main(int argc, char* argv[])
{
    vector<vector<int> > triangle = create_triangle();
    Solution sln;
    int minTotal = sln.minimumTotal(triangle);
    cout << "min total: " << minTotal << endl;
    return 0;
}

/*
http://stackoverflow.com/questions/1732011/c-max-integer
http://stackoverflow.com/questions/253099/how-do-i-print-the-elements-of-a-c-vector-in-gdb
http://stackoverflow.com/questions/2236197/what-is-the-easiest-way-to-initialize-a-stdvector-with-hardcoded-elements#

Scoping of variable should be done inside case statement:
http://en.cppreference.com/w/cpp/language/switch
*/
