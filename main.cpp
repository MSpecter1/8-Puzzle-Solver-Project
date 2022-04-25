#include <iostream>
#include <sstream>
#include <queue>
#include <vector>
#include <algorithm>
#include <set>

#include "problem.h"

//Resources
// https://en.cppreference.com/w/cpp/container/set/find
// https://stackoverflow.com/questions/15601973/stl-priority-queue-of-c-with-struct

using std::cin;
using std::cout;
using std::string;
using std::endl;

int UniformCostSearch(problem);

struct state{
    int val;
    int cost;
    bool operator<(const state& rhs) const
    {
        return val < rhs.val;
    }
};

int main() {
    problem *temp = new problem();
    
    UniformCostSearch(*temp);

    return 0;
}

class Compare{
    public:
        bool operator()(state s1, state s2)
        {
            return s1.cost>s2.cost; //smaller first, s1<s2 for greater first
        }
};

int UniformCostSearch(problem newProblem){
    int expandedNodes = 0;
    int maxQSize = 0;
    
    state solution;

    std::priority_queue<state, vector<state>, Compare> frontier;
    std::set<state> frontierSet; //set in order to keep track of states inside frontier
    state init = {newProblem.init, 0};
    frontier.push(init);
    frontierSet.insert(init);

    if (maxQSize<frontier.size()){maxQSize=frontier.size();}

    std::set<state> explored; //initialize explored states as empty
    while(!frontier.empty())
    {
        cout<<"Queue: ";
        for (auto it=frontierSet.begin(); it != frontierSet.end(); ++it){
            cout<<"("<<it->val<<", "<<it->cost<<"), ";
        }
        cout<<endl;     

        state cur = frontier.top();
        frontier.pop();
        frontierSet.erase(cur);

        cout<<"Current State: " << cur.val<<" with cost of "<<cur.cost<<endl;
        if(cur.val==newProblem.goal)
        {
            solution = cur; //solution found
            cout<<"\tSolution Found!"<<endl; 
        }
        explored.insert(cur); //add leaf to explored state

        bool expanded = false; //bool to check if node was expanded
        for(int i=0; i<newProblem.numOperators; i++) //loop through all operators
        {
            state node = {newProblem.Operators[i](cur.val), cur.cost+1}; //cost is just current cost+1 since this is uniform cost search (closest to initial first)
            if((explored.find(node)==explored.end() && frontierSet.find(node)==frontierSet.end())){ //Only expand if not found inside explored set or frontier set
                cout<<"\tExpanding "<< cur.val <<" to " << node.val <<endl;
                frontier.push(node); 
                frontierSet.insert(node);

                if (maxQSize<frontier.size()){maxQSize=frontier.size();}
                expanded = true;
            }
        }

        if (expanded){expandedNodes++;}
        cout<<"\n";
    }

    cout<<"Search Review: "<<endl;
    cout<<"\tNodes Expanded: "<<expandedNodes<<endl;
    cout<<"\tMaximum Queue Size: "<<maxQSize<<endl;
    cout<<"\tSolution Depth: "<<solution.cost<<endl;
    return 0;
}


