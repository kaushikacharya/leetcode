// https://oj.leetcode.com/problems/word-search/
// Date: Nov 29, 2014

#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    bool exist(vector<vector<char> > &board, string word)
    {
        row_ = board.size();
        col_ = board[0].size();

        populate_graph();

        stack<pair<int,int> > posStk; // 1st elem is pos(in graph), 2nd elem is pos(in word)
        stack<int> pathStk; // This is helpful to reset visited flag for the path which we have backtracked.

        // insert positions corresponding to first char of the word into the stack.
        for (int row=0; row != row_; ++row)
        {
            for (int col=0; col != col_; ++col)
            {
                if (board[row][col] == word[0])
                {
                    int posInGraph = row*col_ + col;
                    posStk.push(make_pair(posInGraph,0));
                }
            }
        }

        bool flag = false;
        while (!posStk.empty())
        {
            pair<int,int> posPair = posStk.top();
            posStk.pop();

            int posGraph = posPair.first;
            int posWord = posPair.second;

            // Handling the case when we have to backtrack the path
            while (pathStk.size() > posWord)
            {
                visitedMatrix_[pathStk.top()] = false;
                pathStk.pop();
            }

            visitedMatrix_[posGraph] = true;
            pathStk.push(posGraph);

            if (posWord == (word.size()-1))
            {
                flag = true;
                break;
            }

            vector<int> vecNeighborPos = adjMatrix_[posGraph];

            for (vector<int>::iterator it = vecNeighborPos.begin(); it != vecNeighborPos.end(); ++it)
            {
                if (!visitedMatrix_[*it])
                {
                    int rowNeighbor = (*it)/col_;
                    int colNeighbor = (*it)%col_;

                    if (board[rowNeighbor][colNeighbor] == word[posWord+1])
                    {
                        posStk.push(make_pair(*it,posWord+1));
                    }
                }
            }
        }

        return flag;
    }
private:
    void populate_graph()
    {
        adjMatrix_.reserve(row_*col_);
        visitedMatrix_.reserve(row_*col_);

        for (int row=0; row != row_; ++row)
        {
            for (int col=0; col != col_; ++col)
            {
                vector<int> vecNeighborPos;

                if (row > 0)
                {
                    vecNeighborPos.push_back((row-1)*col_ + col);
                }
                if (col > 0)
                {
                    vecNeighborPos.push_back(row*col_ + (col-1));
                }
                if (col < (col_-1))
                {
                    vecNeighborPos.push_back(row*col_ + (col+1));
                }
                if (row < (row_-1))
                {
                    vecNeighborPos.push_back((row+1)*col_ + col);
                }

                //cout << "vecNeighborPos size: " << vecNeighborPos.size() << endl;
                adjMatrix_.push_back(vecNeighborPos);
                visitedMatrix_.push_back(false);
            }
        }
    }
private:
    int row_;
    int col_;
private:
    // position is converted from (row,col) to a scalar value
    vector<vector<int> > adjMatrix_;
    vector<bool> visitedMatrix_;
};

int main(int argc, char* argv[])
{
    vector<vector<char> > board;
    vector<string> vecStr = {"ABCE", "SFCS", "ADEE"};
    for (int str_i = 0; str_i != vecStr.size(); ++str_i)
    {
        vector<char> vecChar;
        for (int char_i = 0; char_i != vecStr[str_i].size(); ++char_i)
        {
            vecChar.push_back(vecStr[str_i][char_i]);
        }
        board.push_back(vecChar);
    }

    Solution sln;
    string word = "SEE";
    bool flag = sln.exist(board, word);
    cout << flag << endl;

    return 0;
}
