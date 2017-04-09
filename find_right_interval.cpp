// https://leetcode.com/problems/find-right-interval/#/description
// Apr 09, 2017

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct Interval
{
    int start;
    int end;
    Interval(): start(0), end(0){}
    Interval(int s, int e): start(s), end(e){}
};

struct cmp
{
    bool operator()(const pair<Interval,unsigned int>& x, const pair<Interval,unsigned int>& y) const
    {
        return x.first.start < y.first.start;
    }
};


class Solution
{
public:
    vector<int> findRightInterval(vector<Interval>& intervals)
    {
        vector<int> vecMinRightIndex;
        if (intervals.size() == 1)
        {
            vecMinRightIndex.push_back(-1);
            return vecMinRightIndex;
        }
        else if (intervals.empty())
        {
            return vecMinRightIndex;
        }

        // vector<pair<Interval, unsigned int> > vecIntervalWithIndex;
        for (vector<Interval>::iterator it=intervals.begin(); it != intervals.end(); ++it)
        {
            pair<Interval,unsigned int> interalWithIndex = make_pair(*it, it-intervals.begin());
            vecIntervalWithIndex_.push_back(interalWithIndex);
        }

        sort(vecIntervalWithIndex_.begin(), vecIntervalWithIndex_.end(), cmp());

        /*
        for (vector<pair<Interval,unsigned int> >::iterator it = vecIntervalWithIndex_.begin(); it != vecIntervalWithIndex_.end(); ++it)
        {
            cout << (*it).second << " : " << (*it).first.start << "," << (*it).first.end << endl;
        }
        */
        for (vector<Interval>::iterator it=intervals.begin(); it != intervals.end(); ++it)
        {
            int interval_end = (*it).end;
            int right_index = find_right_interval(interval_end, 0, intervals.size()-1);
            if (right_index == -1)
            {
                vecMinRightIndex.push_back(right_index);
            }
            else
            {
                vecMinRightIndex.push_back(vecIntervalWithIndex_[right_index].second);
            }
        }

        return vecMinRightIndex;
    }

private:
    int find_right_interval(int interval_end, unsigned int i, unsigned int j)
    {
        // assumption: vecIntervalWithIndex_ is sorted wrt start of the interval
        // Find the interval which is closest right of the intervals:: vecIntervalWithIndex_[i] : vecIntervalWithIndex_[j]

        // Edge cases
        if (vecIntervalWithIndex_[j].first.start < interval_end)
        {
            return -1; // No interval present on right of the given interval
        }
        if (interval_end <= vecIntervalWithIndex_[i].first.start)
        {
            return i;
        }

        if (j-i == 1)
        {
            // mid_index will comes as i
            // Hence needs to be taken as edge case
            // In this situation there will be 3 cases. Two cases are handled above.
            return j;
        }
        unsigned int mid_index = (i+j)/2;

        if (vecIntervalWithIndex_[mid_index].first.start < interval_end)
        {
            return find_right_interval(interval_end, mid_index, j);
        }
        else
        {
            return find_right_interval(interval_end, i, mid_index);
        }
    }
private:
    vector<pair<Interval, unsigned int> > vecIntervalWithIndex_; // index: refers to the index of the interval in the input vector of intervals
};

int main(int argc, char** argv)
{
    int test_case = 2;
    vector<Interval> intervals;

    switch (test_case)
    {
    case 0:
        {
            Interval intv0 = Interval(3,4);
            Interval intv1 = Interval(2,3);
            Interval intv2 = Interval(1,2);

            intervals.push_back(intv0);
            intervals.push_back(intv1);
            intervals.push_back(intv2);
            break;
        }
    case 1:
        {
            Interval intv0 = Interval(1,4);
            Interval intv1 = Interval(2,3);
            Interval intv2 = Interval(3,4);

            intervals.push_back(intv0);
            intervals.push_back(intv1);
            intervals.push_back(intv2);
            break;
        }
    case 2:
        {
            Interval intv0 = Interval(1,4);
            intervals.push_back(intv0);
            break;
        }
    }

    Solution sln;
    vector<int> vecMinRightIndex = sln.findRightInterval(intervals);
    for (vector<int>::iterator it = vecMinRightIndex.begin(); it != vecMinRightIndex.end(); ++it)
    {
        cout << *it << ",";
    }

    return 0;
}

/*
  Approach: Sorting + Binary search
  i.e. approach #3 of https://leetcode.com/articles/find-right-interval/
*/
