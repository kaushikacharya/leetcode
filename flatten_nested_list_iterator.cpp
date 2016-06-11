// https://leetcode.com/problems/flatten-nested-list-iterator/
// June 10, 2016

#include <iostream>
#include <stack>
#include <vector>

using namespace std;

/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */
class NestedIterator {
public:
    NestedIterator(vector<NestedInteger> &nestedList) {
        // Push the nestedList in stack so that the first element of list is at the top
        for (vector<NestedInteger>::reverse_iterator rit=nestedList.rbegin(); rit != nestedList.rend(); ++rit)
        {
            stk_.push(*rit);
        }
    }

    int next() {
        NestedInteger topElem = stk_.top();
        stk_.pop();

        return topElem.getInteger();

        /*
        // Following is taken care of in hasNext()
        if (topElem.isInteger())
        {
            return topElem.getInteger();
        }
        else
        {
            const vector<NestedInteger> nestedList = topElem.getList();
            for (vector<NestedInteger>::const_reverse_iterator rit=nestedList.rbegin(); rit != nestedList.rend(); ++rit)
            {
                stk_.push(*rit);
            }
            return next();
        }
        */
    }

    bool hasNext() {
        if (stk_.empty())
        {
            return false;
        }
        else
        {
            // Need to handle empty list as an element in stack
            NestedInteger topElem = stk_.top();
            if (topElem.isInteger())
            {
                return true;
            }
            else
            {
                // top element is a list
                // pop the top element and push the constituents of the top element's list into stack in reverse order
                stk_.pop();
                const vector<NestedInteger> nestedList = topElem.getList();
                for (vector<NestedInteger>::const_reverse_iterator rit=nestedList.rbegin(); rit != nestedList.rend(); ++rit)
                {
                    stk_.push(*rit);
                }

                return hasNext();
            }
        }
    }
private:
    stack<NestedInteger> stk_;
};

/**
 * Your NestedIterator object will be instantiated and called as such:
 * NestedIterator i(nestedList);
 * while (i.hasNext()) cout << i.next();
 */
