// https://leetcode.com/problems/predict-the-winner/?tab=Description
// Mar 07, 2017

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    bool PredictTheWinner(vector<int>& nums)
    {
        pair<int,int> scorePair = computeScore(nums, 0, nums.size()-1);

        if (scorePair.first < scorePair.second)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
private:
    // Compute score for both players using nums[i]...nums[j]
    // First value: Player #1 's score who gets a chance to choose first at this stage
    pair<int,int> computeScore(vector<int>& nums, int i, int j)
    {
        if (i == j)
        {
            return make_pair(nums[i],0);
        }

        // case: Player #1 chooses nums[i]
        pair<int,int> outputLeft = computeScore(nums, i+1,j);

        // case: PLayer #1: chooses nums[j]
        pair<int,int> outputRight = computeScore(nums, i, j-1);

        // At the next level, the other player gets chance to choose either end of the array
        // As a notation, we put the score of other player first for both the above cases i.e.
        //  1st score is for the player who gets chance to choose first.
        int score_first;
        int score_second;

        // Now choose from left/right path
        if ((nums[i] + outputLeft.second) > (nums[j] + outputRight.second))
        {
            score_first = nums[i] + outputLeft.second;
            score_second = outputLeft.first;
        }
        else
        {
            score_first = nums[j] + outputRight.second;
            score_second = outputRight.first;
        }

        return make_pair(score_first, score_second);
    }
};

int main(int argc, char** argv)
{
    int test_case = 1;
    Solution sln;
    switch (test_case)
    {
    case 0:
        {
            int nums_arr[3] = {1,5,2};
            vector<int> nums(nums_arr, nums_arr+sizeof(nums_arr)/sizeof(nums_arr[0]));
            bool predict_winner = sln.PredictTheWinner(nums);
            cout << "predict winner: " << predict_winner << endl;
            break;
        }
    case 1:
        {
            int nums_arr[4] = {1,5,233,7};
            vector<int> nums(nums_arr, nums_arr+sizeof(nums_arr)/sizeof(nums_arr[0]));
            bool predict_winner = sln.PredictTheWinner(nums);
            cout << "predict winner: " << predict_winner << endl;
            break;
        }
    }
    return 0;
}
