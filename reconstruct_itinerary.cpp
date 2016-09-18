// https://leetcode.com/problems/reconstruct-itinerary/
// Sept 16, 2016

#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <unordered_map>
#include <cassert>

using namespace std;

class Solution {
public:
    vector<string> findItinerary(vector<pair<string, string>> tickets)
    {
        srcAirport_ = "JFK";
        populate_edges(tickets);
        populate_adjacency_list_in_lexicographic_order();
        // print_adjacency_list();

        // cout << "\ntraversal:\n" << endl;
        vector<int> vecIndexItineraryEdge;
        find_itinerary_backtracking(vecIndexItineraryEdge);
        // cout << "size(vecIndexItineraryEdge) after traversal: " << vecIndexItineraryEdge.size() << endl;

        // Now collect the airports
        vector<string> vecItinerary;
        vecItinerary.push_back(vecEdge_[vecIndexItineraryEdge.front()].from);

        for (vector<int>::iterator it = vecIndexItineraryEdge.begin(); it != vecIndexItineraryEdge.end(); ++it)
        {
            vecItinerary.push_back(vecEdge_[*it].to);
        }

        return vecItinerary;
    }
private:
    void populate_edges(vector<pair<string, string> > tickets)
    {
        for (vector<pair<string, string> >::iterator it = tickets.begin(); it != tickets.end(); ++it)
        {
            string fromAirport = (*it).first;
            string toAirport = (*it).second;
            Edge edge(fromAirport, toAirport);

            edgeToIndexMap_.insert(make_pair(edge,vecEdge_.size()));
            vecEdge_.push_back(edge);
            vecVisited_.push_back(false);
        }
    }

    /*
    bool cmp(int i, int j)
    {
        return i < j;
        // return (vecEdge_[i].to < vecEdge_[j].to);
    }
    */

    void populate_adjacency_list_in_lexicographic_order()
    {
        assert((vecEdge_.size() > 0) && "populate edges before calling populate_adjacency_list()\n");

        // initialize empty adjacency list
        for (int i = 0; i != vecEdge_.size(); ++i)
        {
            adjMatrix_.push_back(vector<Edge>());
        }

        // TBD: use unordered_map to reduce time complexity from O(n^2)
        for (int i = 0; i != vecEdge_.size(); ++i)
        {
            for (int j = 0; j != vecEdge_.size(); ++j)
            {
                if (i == j)
                {
                    continue;
                }

                if (vecEdge_[i].to == vecEdge_[j].from)
                {
                    adjMatrix_[i].push_back(vecEdge_[j]);
                }
            }
        }

        // now sort each of the adjacency list
        for (int i = 0; i != vecEdge_.size(); ++i)
        {
            sort(adjMatrix_[i].begin(), adjMatrix_[i].end(), cmp());
        }
    }

    void print_adjacency_list()
    {
        cout << "n edges: " << vecEdge_.size() << endl;
        for (int i = 0; i != vecEdge_.size(); ++i)
        {
            cout << i << " : " << vecEdge_[i].from << "->" << vecEdge_[i].to << " : ";
            for (int j = 0; j != adjMatrix_[i].size(); ++j)
            {
                // cout << vecEdge_[adjMatrix_[i][j]].from << "->" << vecEdge_[adjMatrix_[i][j]].to << ", ";
                cout << adjMatrix_[i][j].from << "->" << adjMatrix_[i][j].to << ", ";
            }
            cout << endl;
        }
    }

    void find_itinerary_backtracking(vector<int>& vecIndexItineraryEdge)
    {
        // cout << "size(vecIndexItineraryEdge): " << vecIndexItineraryEdge.size() << endl;
        if (vecIndexItineraryEdge.size() == vecEdge_.size())
        {
            return;
        }

        // get the next edges
        vector<int> vec_index_child_edge;

        if (vecIndexItineraryEdge.empty())
        {
            // collect the edges having "to" as source airport in sorted order
            vector<Edge> vec_child_edge;
            for (int i=0; i != vecEdge_.size(); ++i)
            {
                if (vecEdge_[i].from == srcAirport_)
                {
                    vec_child_edge.push_back(vecEdge_[i]);
                    // vec_index_child_edge.push_back(i);
                }
            }

            sort(vec_child_edge.begin(), vec_child_edge.end(), cmp());

            for (vector<Edge>::iterator it = vec_child_edge.begin(); it != vec_child_edge.end(); ++it)
            {
                unordered_map<Edge,int,EdgeHash,EdgeEqual>::iterator mapIt = edgeToIndexMap_.find(*it);
                vec_index_child_edge.push_back((*mapIt).second);
            }
        }
        else
        {
            int last_edge_index = vecIndexItineraryEdge.back();

            for (vector<Edge>::iterator it = adjMatrix_[last_edge_index].begin(); it != adjMatrix_[last_edge_index].end(); ++it)
            {
                unordered_map<Edge,int,EdgeHash,EdgeEqual>::iterator mapIt = edgeToIndexMap_.find(*it);
                vec_index_child_edge.push_back((*mapIt).second);
            }
        }

        for (vector<int>::iterator it = vec_index_child_edge.begin(); it != vec_index_child_edge.end(); ++it)
        {
            int child_index_edge = *it;
            if (!vecVisited_[child_index_edge])
            {
                // cout << child_index_edge << " : " << vecEdge_[child_index_edge].from << "->" << vecEdge_[child_index_edge].to << endl;
                vecVisited_[child_index_edge] = true;
                vecIndexItineraryEdge.push_back(child_index_edge);
                find_itinerary_backtracking(vecIndexItineraryEdge);
            }
        }

        // backtrack
        if (!vecIndexItineraryEdge.empty() && (vecIndexItineraryEdge.size() < vecEdge_.size()))
        {
            int last_edge_index = vecIndexItineraryEdge.back();
            vecIndexItineraryEdge.pop_back();
            vecVisited_[last_edge_index] = false;
        }
    }
private:
    struct Edge
    {
        string from;
        string to;

        Edge(string fromAirport, string toAirport)
        : from(fromAirport)
        , to(toAirport)
        {
        }
    };

    struct EdgeHash
    {
        size_t operator()(const Edge& e) const
        {
            return hash<string>()(e.from) ^ (hash<string>()(e.to) << 1);
        }
    };

    struct EdgeEqual
    {
        bool operator()(const Edge& lhs, const Edge& rhs) const
        {
            return lhs.from == rhs.from && lhs.to == rhs.to;
        }
    };

    struct cmp
    {
        bool operator()(const Edge& edgeA, const Edge& edgeB)
        {
            return (edgeA.to < edgeB.to);
        }
    };
private:
    string srcAirport_;
    vector<Edge> vecEdge_;
    vector<bool> vecVisited_;
    vector<vector<Edge> > adjMatrix_;
    unordered_map<Edge,int, EdgeHash, EdgeEqual> edgeToIndexMap_; // maps Edge to index in vecEdge_
};

int main(int argc, char** argv)
{
    vector<pair<string, string>> tickets;
    /*
    tickets.push_back(make_pair("JFK","SFO"));
    tickets.push_back(make_pair("JFK","ATL"));
    tickets.push_back(make_pair("SFO","ATL"));
    tickets.push_back(make_pair("ATL","JFK"));
    tickets.push_back(make_pair("ATL","SFO"));
    */

    tickets.push_back(make_pair("JFK","KUL"));
    tickets.push_back(make_pair("JFK","NRT"));
    tickets.push_back(make_pair("NRT","JFK"));
    tickets.push_back(make_pair("KUL","BRP"));

    Solution sln;
    vector<string> vecItinerary = sln.findItinerary(tickets);
    for (vector<string>::iterator it = vecItinerary.begin(); it != vecItinerary.end(); ++it)
    {
        cout << *it << ",";
    }
    cout << endl;
}

/*
Status: wrong answer
Had faced similar issue (comparison functor can't access the variables in the class under which it is nested)
    http://stackoverflow.com/questions/27101829/c-invalid-use-of-non-static-data-member

http://stackoverflow.com/questions/17016175/c-unordered-map-using-a-custom-class-type-as-the-key

http://stackoverflow.com/questions/20049829/how-to-calculate-time-complexity-of-backtracking-algorithm
http://en.cppreference.com/w/cpp/string/basic_string/operator_cmp
*/

