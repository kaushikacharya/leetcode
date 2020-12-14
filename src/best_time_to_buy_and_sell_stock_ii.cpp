// https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/
// June 15, 2016

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices)
    {
        if (prices.empty())
        {
            return 0;
        }

        vector<int> prevVec;
        vector<int> curVec;

        // index: 0 - represents the max profit at today's EOD if we have nil share
        // index: 1 - represents the max profit at today's EOD if we have one share left with us
        curVec.push_back(0);
        curVec.push_back(-1*prices[0]);
        prevVec = curVec;

        for (vector<int>::iterator it = prices.begin()+1; it != prices.end(); ++it)
        {
            int today_price = *it;
            // situations for having nil shares at today's EOD
            // (a) not buying any share today and continuing with yesterday's max profit of nil share
            // (b) selling share today which we had acquired in past
            curVec[0] = max(prevVec[0], today_price+prevVec[1]);
            // Now computing max profit for situation having one share at today's EOD
            curVec[1] = max(prevVec[0]-today_price, prevVec[1]);
            // Now storing for next iteration
            prevVec = curVec;
        }

        return curVec[0];
    }
};

int main(int argc, char* argv[])
{
    Solution sln;
    vector<int> prices = {1,2,3,4,5};
    int max_profit = sln.maxProfit(prices);
    cout << "max profit: " << max_profit << endl;
    return 0;
}

/**
* Doubt cleared here:
* https://leetcode.com/discuss/59964/a-question-about-best-time-to-buy-and-sell-stock-ii?show=59964#q59964
*
* Alternate solution:
* https://leetcode.com/discuss/42176/three-lines-in-c-with-explanation
*/
