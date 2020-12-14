// https://oj.leetcode.com/problems/merge-intervals/
// Date: Nov 30, 2014

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Interval
{
    int start;
    int end;
    Interval(): start(0), end(0) {}
    Interval(int s, int e): start(s), end(e) {}
};

class Solution {
public:
    vector<Interval> merge(vector<Interval> &intervals)
    {
        if (intervals.empty())
        {
            return intervals;
        }
        sort(intervals.begin(), intervals.end(), comp());

        /*
        for (vector<Interval>::iterator it = intervals.begin(); it != intervals.end(); ++it)
        {
            cout << (*it).start << endl;
        }
        */

        vector<Interval> vecMergeInterval;
        vecMergeInterval.push_back(intervals[0]);

        for (vector<Interval>::iterator it = intervals.begin()+1; it != intervals.end(); ++it)
        {
            if ((*it).start <= vecMergeInterval.back().end)
            {
                if (vecMergeInterval.back().end < (*it).end)
                {
                    vecMergeInterval.back().end = (*it).end;
                }
            }
            else
            {
                vecMergeInterval.push_back(*it);
            }
        }

        return vecMergeInterval;
    }
private:
    struct comp
    {
        bool operator()(Interval intv1, Interval intv2)
        {
            return intv1.start < intv2.start;
        }
    };
};

int main(int argc, char* argv[])
{
    int arr[] = {1,3,8,10,2,6,15,18};
    int n = sizeof(arr)/sizeof(arr[0]);
    vector<Interval> intervals;
    for (int i = 0; i != n; i=i+2)
    {
        Interval intv(arr[i], arr[i+1]);
        intervals.push_back(intv);
    }

    Solution sln;
    intervals = sln.merge(intervals);

    for (vector<Interval>::iterator it = intervals.begin(); it != intervals.end(); ++it)
    {
        cout << (*it).start << ":" << (*it).end << endl;
    }

    return 0;
}
