// https://leetcode.com/problems/reconstruct-itinerary/
// Sept 16, 2016

#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<string> findItinerary(vector<pair<string, string>> tickets)
    {
        sort_and_create_map(tickets);
        create_adjacency_matrix(tickets);
        // print_adjacency_matrix();

        string st_airport =  "JFK";
        unordered_map<string, int>::iterator mapIt = mapAirportToIndex_.find(st_airport);
        int st_airport_index = (*mapIt).second;

        vector<int> vecItineraryIndex;
        vecItineraryIndex.push_back(st_airport_index);
        int final_size = tickets.size() + 1;
        find_itinerary_backtracking(vecItineraryIndex, st_airport_index, final_size);

        vector<string> vecItinerary;
        for (vector<int>::iterator it = vecItineraryIndex.begin(); it != vecItineraryIndex.end(); ++it)
        {
            vecItinerary.push_back(vecAirportSorted_[*it]);
        }

        return vecItinerary;
    }
private:
    void sort_and_create_map(vector<pair<string, string>> tickets)
    {
        // Collect the set of airports
        set<string> airports;
        for (vector<pair<string, string>>::iterator it = tickets.begin(); it != tickets.end(); ++it)
        {
            airports.insert((*it).first);
            airports.insert((*it).second);
        }

        {
            set<string>::iterator it;
            int i;
            for (it = airports.begin(), i = 0; it != airports.end(); ++it, ++i)
            {
                string airport = (*it);
                mapAirportToIndex_.insert(make_pair(airport, i));
                vecAirportSorted_.push_back(airport);
            }
        }

        /*
        for (set<string>::iterator it = airports.begin(); it != airports.end(); ++it)
        {
            unordered_map<string, int>::iterator map_it = mapAirportToIndex_.find(*it);
            cout << *it << " : " << map_it->second << endl;
        }
        */

    }

    void create_adjacency_matrix(vector<pair<string, string> > tickets)
    {
        // initialize empty vectors
        for (int i = 0; i != vecAirportSorted_.size(); ++i)
        {
            adjMatrix_.push_back(vector<int>());
            vecPosNext_.push_back(0);
        }

        for (vector<pair<string, string> >::iterator tIt = tickets.begin(); tIt != tickets.end(); ++tIt)
        {
            string fromAirport = (*tIt).first;
            string toAirport = (*tIt).second;
            unordered_map<string, int>::iterator mapIt = mapAirportToIndex_.find(fromAirport);
            int fromAirportIndex = (*mapIt).second;
            mapIt = mapAirportToIndex_.find(toAirport);
            int toAirportIndex = (*mapIt).second;

            adjMatrix_[fromAirportIndex].push_back(toAirportIndex);
        }

        // sort each rows of the adjacent matrix
        for (vector<vector<int> >::iterator it = adjMatrix_.begin(); it != adjMatrix_.end(); ++it)
        {
            sort((*it).begin(), (*it).end());
        }
    }

    void print_adjacency_matrix()
    {
        for (int row = 0; row != vecAirportSorted_.size(); ++row)
        {
            cout << vecAirportSorted_[row] << " : ";
            for (vector<int>::iterator it = adjMatrix_[row].begin(); it != adjMatrix_[row].end(); ++it)
            {
                cout << vecAirportSorted_[*it] << ",";
            }
            cout << endl;
        }
    }

    void find_itinerary_backtracking(vector<int>& vecItinerary, int curFromAirport, int final_size)
    {
        // cout << "entering with fromAirport: " << curFromAirport << " : " << vecAirportSorted_[curFromAirport] <<
        // " :: size(vecItinerary): " << vecItinerary.size() << " :: next pos: " << vecPosNext_[curFromAirport] << endl;

        if (vecItinerary.size() == final_size)
        {
            // cout << "itenary found" << endl;
            return;
        }

        for (int childIndex = vecPosNext_[curFromAirport]; childIndex != adjMatrix_[curFromAirport].size(); ++childIndex)
        {
            int nextAirport = adjMatrix_[curFromAirport][childIndex];

            vecItinerary.push_back(nextAirport);
            ++vecPosNext_[curFromAirport];

            find_itinerary_backtracking(vecItinerary, nextAirport, final_size);
            // cout << "after return from func: " << "curFromAirport: " << curFromAirport << " : " << vecAirportSorted_[curFromAirport] << endl;

            if (vecItinerary.size() == final_size)
            {
                return;
            }

            vecItinerary.pop_back();
        }

        // expanding curFromAirport didn't worked in finding the path. Hence backtracking
        // cout << "expanding didn't worked: " << "curFromAirport: " << curFromAirport << " : " << vecAirportSorted_[curFromAirport] << endl;
        vecPosNext_[curFromAirport] = 0;
        vecItinerary.pop_back();
    }

private:
    vector<vector<int> > adjMatrix_;
    vector<string> vecAirportSorted_;
    unordered_map<string, int> mapAirportToIndex_;
    vector<int> vecPosNext_; // for each row of the adjacency matrix, this represents the next "to" airport to explore
};

int main(int argc, char** argv)
{
    vector<pair<string, string>> tickets;
    /*
    tickets.push_back(make_pair("JFK","BFO"));
    tickets.push_back(make_pair("JFK","ATL"));
    tickets.push_back(make_pair("BFO","ATL"));
    tickets.push_back(make_pair("ATL","JFK"));
    tickets.push_back(make_pair("ATL","BFO"));
    */
    tickets.push_back(make_pair("JFK","KUL"));
    tickets.push_back(make_pair("JFK","NRT"));
    tickets.push_back(make_pair("NRT","JFK"));

    Solution sln;
    vector<string> vecItinerary = sln.findItinerary(tickets);
    for (vector<string>::iterator it = vecItinerary.begin(); it != vecItinerary.end(); ++it)
    {
        cout << *it << ",";
    }
    cout << endl;
}

/*
Status: Run time error
TBD: Change approach: consider edges as nodes of graph
*/

