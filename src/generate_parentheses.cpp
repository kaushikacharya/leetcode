// https://oj.leetcode.com/problems/generate-parentheses/
// Date: Nov 16, 2014

#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    vector<string> generateParenthesis(int n)
    {
        vector<string> vec;
        if (n == 0)
        {
            return vec;
        }

        queue<TreeNode*> Q;
        TreeNode* node = new TreeNode("(",1,0);
        Q.push(node);

        while (!Q.empty())
        {
            node = Q.front();
            Q.pop();

            // check if the "node" is a leaf node
            if ( (node->count_left_parenthesis == n) & (node->count_right_parenthesis == n) )
            {
                vec.push_back(node->str);
            }
            else
            {
                if (node->count_left_parenthesis < n)
                {
                    TreeNode* leftNode = new TreeNode(node->str+"(", node->count_left_parenthesis+1, node->count_right_parenthesis);
                    Q.push(leftNode);
                }
                if (node->count_right_parenthesis < node->count_left_parenthesis)
                {
                    TreeNode* rightNode = new TreeNode(node->str+")", node->count_left_parenthesis, node->count_right_parenthesis+1);
                    Q.push(rightNode);
                }
            }
        }

        return vec;
    }
private:
    struct TreeNode
    {
        string str;
        int count_left_parenthesis;
        int count_right_parenthesis;
        TreeNode(string s, int count_left, int count_right): str(s), count_left_parenthesis(count_left),
                            count_right_parenthesis(count_right) {}
    };
};

int main(int argc, char* argv[])
{
    int n = 2;
    Solution sln;
    vector<string> vec = sln.generateParenthesis(n);

    for (int i = 0; i != vec.size(); ++i)
    {
        cout << vec[i] << endl;
    }

    return 0;
}
