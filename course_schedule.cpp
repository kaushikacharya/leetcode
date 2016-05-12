// https://leetcode.com/problems/course-schedule/
// May 12, 2016

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites)
    {
        populate_prerequisites_graph(numCourses, prerequisites);

        // run a DFS loop
        isDAG_ = true;
        for (unsigned int course_i=0; (course_i != numCourses) && isDAG_; ++course_i)
        {
            dfs_traversal_recursive(course_i);
        }

        return isDAG_;
    }
private:
    void populate_prerequisites_graph(int numCourses, vector<pair<int, int>>& prerequisites)
    {
        adjacencyList_.reserve(numCourses);
        for (unsigned int course_i=0; course_i != numCourses; ++course_i)
        {
            adjacencyList_.push_back(vector<int>());
        }

        for(vector<pair<int, int>>::iterator it = prerequisites.begin(); it != prerequisites.end(); ++it)
        {
            pair<int,int> prerequisitePair = *it;
            int course1 = prerequisitePair.second;
            int course2 = prerequisitePair.first;
            adjacencyList_[course1].push_back(course2);
        }

        // initialize visited vector
        vecVisited_.reserve(numCourses);
        vecTempVisited_.reserve(numCourses);
        for (unsigned int course_i=0; course_i != numCourses; ++course_i)
        {
            vecVisited_.push_back(false);
            vecTempVisited_.push_back(false);
        }
    }

    void dfs_traversal_recursive(int st_vertex)
    {
        if (vecTempVisited_[st_vertex])
        {
            isDAG_ = false; // There's a cycle in the directed graph.
            return;
        }
        if (vecVisited_[st_vertex])
        {
            return;
        }
        vecTempVisited_[st_vertex] = true;
        for (vector<int>::iterator it = adjacencyList_[st_vertex].begin(); it != adjacencyList_[st_vertex].end(); ++it)
        {
            int neighbor_vertex = *it;
            dfs_traversal_recursive(neighbor_vertex);
        }
        vecTempVisited_[st_vertex] = false;
        vecVisited_[st_vertex] = true;
    }

private:
    // Courses are labeled 0 to n-1
    vector<vector<int> > adjacencyList_;
    vector<bool> vecVisited_; // This stores permanent visit
    vector<bool> vecTempVisited_;
    bool isDAG_;
};

int main(int argc, char* argv[])
{
    int numCourses;
    vector<pair<int, int>> prerequisites;

    numCourses = 2;
    prerequisites.push_back(make_pair(1,0));
    prerequisites.push_back(make_pair(0,1));
    Solution sln;
    bool can_finish = sln.canFinish(numCourses, prerequisites);
    if (can_finish)
    {
        cout << "can finish" << endl;
    }
    else
    {
        cout << "can't finish" << endl;
    }
    return 0;
}

/**
https://en.wikipedia.org/wiki/Topological_sorting

TBD:
    1. Iterative solution
    2. Kahn's algorithm
*/
