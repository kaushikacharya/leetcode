// https://leetcode.com/problems/implement-queue-using-stacks/
// June 08, 2016

#include <iostream>
#include <stack>

using namespace std;

class Queue {
public:
    // Push element x to the back of queue.
    void push(int x) {
        stk_.push(x);
    }

    // Removes the element from in front of queue.
    void pop(void) {
        stack<int> temp_stk;

        // populate the elements of stk_ into temp_stk
        while (!stk_.empty())
        {
            int x = stk_.top();
            stk_.pop();
            temp_stk.push(x);
        }

        // Now pop the top element from temp_stk
        temp_stk.pop();

        // Populate back the stack stk_
        while (!temp_stk.empty())
        {
            int x = temp_stk.top();
            temp_stk.pop();
            stk_.push(x);
        }
    }

    // Get the front element.
    int peek(void) {
        stack<int> temp_stk;

        // populate the elements of stk_ into temp_stk
        while (!stk_.empty())
        {
            int x = stk_.top();
            stk_.pop();
            temp_stk.push(x);
        }

        int front_element = temp_stk.top();

        // Populate back the stack stk_
        while (!temp_stk.empty())
        {
            int x = temp_stk.top();
            temp_stk.pop();
            stk_.push(x);
        }

        return front_element;
    }

    // Return whether the queue is empty.
    bool empty(void) {
        return stk_.empty();
    }
private:
    stack<int> stk_;
};

int main(int argc, char* argv[])
{
    Queue q;
    q.push(1);
    q.push(2);
    int front_element = q.peek();
    cout << "peek: " << front_element << endl;
    cout << "pop" << endl;
    q.pop();
    front_element = q.peek();
    cout << "peek: " << front_element << endl;
    cout << "now keep popping till queue becomes empty" << endl;
    while (!q.empty())
    {
        front_element = q.peek();
        cout << "peek: " << front_element << endl;
        q.pop();
    }
    return 0;
}

/**
* Have a look at the two solutions:
* https://leetcode.com/articles/implement-queue-using-stacks/
*/
