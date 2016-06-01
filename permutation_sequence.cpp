// https://leetcode.com/problems/permutation-sequence/
// June 01, 2016

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class Solution {
public:
    string getPermutation(int n, int k)
    {
       string output_str = "";
       vector<string> vec; // "1",..,"n"
       stringstream ss;
       for (int i = 1; i != (n+1); ++i)
       {
           ss << i;
           vec.push_back(ss.str());
           ss.str(string());
       }

       int num = k-1;
       int denom = 1;
       // denom = (n-1)!
       for (int i = 1; i != n; ++i)
       {
           denom *= i;
       }

       for (int i = 1; i != n; ++i)
       {
           int index = num/denom;
           num = num%denom;
           output_str += vec[index];
           vec.erase(vec.begin()+index);
           denom /= (n-i);
       }
       output_str += vec[0];
       return output_str;
    }
};

int main(int argc, char* argv[])
{
    int n = 3;
    int k = 3;
    Solution sln;
    string permutation_at_position_k = sln.getPermutation(n,k);
    cout << "permutation at position k: " << permutation_at_position_k << endl;
    return 0;
}
