// https://oj.leetcode.com/problems/interleaving-string/
// Date: Nov 27, 2014

#include <iostream>
#include <string>
#include <set>
#include <cassert>

using namespace std;

class Solution {
public:
    bool isInterleave(string s1, string s2, string s3)
    {
        if ((s1.size()+s2.size()) != s3.size())
        {
            return false;
        }
        if (s3.size() == 0)
        {
            return true;
        }

        set<pair<int,int> > pair_set;

        // populate combination for position #1
        if (s2.size() > 0)
        {
            if (s2[0] == s3[0])
            {
                pair_set.insert(make_pair(-1,0));
            }
        }
        if (s1.size() > 0)
        {
            if (s1[0] == s3[0])
            {
                pair_set.insert(make_pair(0,-1));
            }
        }
        if (pair_set.size() == 0)
        {
            return false;
        }

        bool flag = true;
        for (int k=1; k != s3.size(); ++k)
        {
            set<pair<int,int> > success_pair_set;
            set<pair<int,int> > failed_pair_set;

            for (set<pair<int,int> >::iterator it = pair_set.begin(); it != pair_set.end(); ++it)
            {
                int p = (*it).first;
                int q = (*it).second;

                assert(((p+q+2) == k) && "p,q incorrect");

                // s1[p],s2[q+1]
                if ((q+1) < s2.size())
                {
                    if ( (success_pair_set.find(make_pair(p,q+1)) == success_pair_set.end()) &&
                      (failed_pair_set.find(make_pair(p,q+1)) == failed_pair_set.end()) )
                    {
                        if (s2[q+1] == s3[p+q+2])
                        {
                            success_pair_set.insert(make_pair(p,q+1));
                        }
                        else
                        {
                            failed_pair_set.insert(make_pair(p,q+1));
                        }
                    }
                }

                // a1[p+1],s2[q]
                if ((p+1) < s1.size())
                {
                    if ( (success_pair_set.find(make_pair(p+1,q)) == success_pair_set.end()) &&
                        (failed_pair_set.find(make_pair(p+1,q)) == failed_pair_set.end()) )
                    {
                        if (s1[p+1] == s3[p+q+2])
                        {
                            success_pair_set.insert(make_pair(p+1,q));
                        }
                        else
                        {
                            failed_pair_set.insert(make_pair(p+1,q));
                        }
                    }
                }
            }

            if (success_pair_set.empty())
            {
                flag = false;
                break;
            }
            else
            {
                pair_set = success_pair_set;
            }
        }

        return flag;
    }
};

int main(int argc, char* argv[])
{
    string s1 = "aabcc";
    string s2 = "dbbca";
    string s3 = "aadbbcbcac";
    Solution sln;
    bool flag = sln.isInterleave(s1,s2,s3);
    cout << flag << endl;
    return 0;
}

/*
C++11 does not provide a hash for pairs (or tuples), even of hashable types.
http://stackoverflow.com/questions/21288345/unordered-set-of-pairs-compilation-error
*/
