// https://leetcode.com/problems/number-of-islands/
// May 03, 2016

#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

void print_grid(vector<vector<char> >& grid)
{
    for(unsigned int row=0; row != grid.size(); ++row)
    {
        for (unsigned int col=0; col != grid[row].size(); ++col)
        {
            cout << grid[row][col];
        }
        // just for testing
        // grid[row][grid[row].size()-1] = '1';
        cout << endl;
    }
}

class Solution {
public:
    int numIslands(vector<vector<char> >& grid)
    {
        grid_ = grid;
        nrow_ = grid_.size();
        // Handle empty grid
        if (nrow_ == 0)
        {
            return 0;
        }
        ncol_ = grid_[0].size();
        // For testing print grid_
        // print_grid(grid_);
        initialize_visit_matrix(grid_);
        // Now compute number of connected components using BFS traversal
        int n_connected_components = 0;
        for(unsigned int row=0; row != grid.size(); ++row)
        {
            for (unsigned int col=0; col != grid[row].size(); ++col)
            {
                if ((grid_[row][col] == '1') && !visitMatrix_[row][col])
                {
                    bool flag = bfs_traversal(row, col);
                    if (flag)
                    {
                        ++n_connected_components;
                    }
                }
            }
        }

        return n_connected_components;
    }
private:
    void initialize_visit_matrix(vector<vector<char> >& grid)
    {
        for(unsigned int row=0; row != grid.size(); ++row)
        {
            vector<bool> vecBool;
            vecBool.reserve(grid[row].size());
            for (unsigned int col=0; col != grid[row].size(); ++col)
            {
                vecBool.push_back(false);
            }
            visitMatrix_.push_back(vecBool);
        }
    }

    // return false if (a) grid[row,col] is already visited
    //                 (b) grid[row,col] == 0 i.e. its in water
    bool bfs_traversal(unsigned int row, unsigned int col)
    {
        if (visitMatrix_[row][col] || grid_[row][col] != '1')
        {
            return false;
        }
        queue<pair<unsigned int, unsigned int> > Q;
        Q.push(make_pair(row, col));
        visitMatrix_[row][col] = true;

        while (!Q.empty())
        {
            pair<unsigned int, unsigned int> pos_coordinate = Q.front();
            Q.pop();

            // Push the adjacent land coordinates horizontally or vertically which are non-visited
            vector<pair<unsigned int, unsigned int> > adjacent_coordinates = get_adjacent_land_coordinates(pos_coordinate.first, pos_coordinate.second);
            for(vector<pair<unsigned int, unsigned int> >::iterator it = adjacent_coordinates.begin(); it != adjacent_coordinates.end(); ++it)
            {
                unsigned int adjacent_row = (*it).first;
                unsigned int adjacent_col = (*it).second;

                if (!visitMatrix_[adjacent_row][adjacent_col])
                {
                    visitMatrix_[adjacent_row][adjacent_col] = true;
                    Q.push(make_pair(adjacent_row, adjacent_col));
                }
            }
        }

        return true;
    }

    vector<pair<unsigned int, unsigned int> > get_adjacent_land_coordinates(unsigned int row, unsigned int col)
    {
        vector<pair<unsigned int, unsigned int> > adjacent_coordinates;

        // checking vertically adjacent coordinates
        if (row > 0)
        {
            if (grid_[row-1][col] == '1')
            {
                adjacent_coordinates.push_back(make_pair(row-1, col));
            }
        }
        if (row < (nrow_-1))
        {
            if (grid_[row+1][col] == '1')
            {
                adjacent_coordinates.push_back(make_pair(row+1, col));
            }
        }

        // checking horizontally adjacent coordinates
        if (col > 0)
        {
            if (grid_[row][col-1] == '1')
            {
                adjacent_coordinates.push_back(make_pair(row, col-1));
            }
        }
        if (col < (ncol_-1))
        {
            if (grid_[row][col+1] == '1')
            {
                adjacent_coordinates.push_back(make_pair(row, col+1));
            }
        }

        return adjacent_coordinates;
    }
private:
    vector<vector<bool> > visitMatrix_;
    vector<vector<char> > grid_;
    unsigned int nrow_;
    unsigned int ncol_;
};


// For testing reference
void modify_grid(vector<vector<char> >& grid)
{
    for(unsigned int row=0; row != grid.size(); ++row)
    {
        grid[row][grid[row].size()-1] = '1';
    }
}

int main(int argc, char* argv[])
{
    vector<vector<char> > grid;

    int i = 0;
    string str;
    while (cin >> str)
    {
        ++i;
        vector<char> vecChar;
        vecChar.reserve(str.size());
        for (unsigned int j=0; j != str.size(); ++j)
        {
            vecChar.push_back(str[j]);
        }
        grid.push_back(vecChar);
        // cout << "i: " << str << endl;
    }

    // modify_grid(grid);
    // print_grid(grid);
    Solution sln;
    int num_islands = sln.numIslands(grid);
    cout << num_islands << endl;

    return 0;
}
