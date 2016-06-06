// https://leetcode.com/problems/rotate-image/
// June 04, 2016

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    void rotate(vector<vector<int> >& matrix)
    {
        unsigned int n = matrix.size();

        // outer for loop: iterates layer by layer starting from outermost towards innermost
        // inner for loop: rotates the element of the current layer
        for (unsigned int i=0; i<(n/2); ++i)
        {
            for (unsigned int j=i; j < (n-1-i); ++j)
            {
                int elem1 = matrix[i][j];
                // int elem2 = matrix[j][n-1-i];
                // int elem3 = matrix[n-1-i][n-1-j];
                // int elem4 = matrix[n-1-j][i];
                // elem1->elem2->elem3->elem4->elem1
                matrix[i][j] = matrix[n-1-j][i];
                matrix[n-1-j][i] = matrix[n-1-i][n-1-j];
                matrix[n-1-i][n-1-j] = matrix[j][n-1-i];
                matrix[j][n-1-i] = elem1;
            }
        }
    }
};

void display_matrix(vector<vector<int> >& matrix)
{
    unsigned int n = matrix.size();
    for (unsigned int i=0; i != n; ++i)
    {
        for (unsigned int j = 0; j != n; ++j)
        {
            cout << matrix[i][j] << ",";
        }
        cout << endl;
    }
}

int main(int argc, char* argv)
{
    vector<vector<int> > matrix;
    int n = 6;
    for (int i=0; i != n; ++i)
    {
        vector<int> vec;
        for (int j=0; j != n; ++j)
        {
            vec.push_back(i*n+j);
        }
        matrix.push_back(vec);
    }

    cout << "Initial matrix: " << endl;
    display_matrix(matrix);
    cout << endl;

    Solution sln;
    sln.rotate(matrix);

    cout << "Rotated matrix: " << endl;
    display_matrix(matrix);

    return 0;
}
