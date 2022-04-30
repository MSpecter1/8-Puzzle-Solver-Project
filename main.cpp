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
// https://stackoverflow.com/questions/2874441/deleting-elements-from-stdset-while-iterating

using std::cin;
using std::cout;
using std::string;
using std::endl;

int UniformCostSearch(problem);
int AStarMisplacedTileSearch(problem);
int AStarEuclideanDistanceSearch(problem);
int TestUniformCostSearch(problem);

struct state{
    int val;
    int cost;
    bool operator<(const state& rhs) const
    {
        return val < rhs.val;
    }
};

struct stateObject{
    int state[3][3];
    int cost;
    int depth;
    bool operator<(const stateObject& rhs) const
    {
        //return cost < rhs.cost;
        if (state[0][0]<rhs.state[0][0]||state[0][1]<rhs.state[0][1]||state[0][2]<rhs.state[0][2]||
            state[1][0]<rhs.state[1][0]||state[1][1]<rhs.state[1][1]||state[1][2]<rhs.state[1][2]||
            state[2][0]<rhs.state[2][0]||state[2][1]<rhs.state[2][1]||state[2][2]<rhs.state[2][2]){
            return true;
        }
        return false;
    }
    
    bool operator==(const stateObject& rhs)
    {
        if( state[0][0]==rhs.state[0][0]&&state[0][1]==rhs.state[0][1]&&state[0][2]==rhs.state[0][2]&&
            state[1][0]==rhs.state[1][0]&&state[1][1]==rhs.state[1][1]&&state[1][2]==rhs.state[1][2]&&
            state[2][0]==rhs.state[2][0]&&state[2][1]==rhs.state[2][1]&&state[2][2]==rhs.state[2][2])
        {
            return true;
        }
        return false;
    }
};


int test(problem newProblem){

    stateObject cur = {{newProblem.initialState[0][0], newProblem.initialState[0][1], newProblem.initialState[0][2],
                        newProblem.initialState[1][0], newProblem.initialState[1][1], newProblem.initialState[1][2],
                        newProblem.initialState[2][0], newProblem.initialState[2][1], newProblem.initialState[2][2]
                        }, 0};

    newProblem.displayState(cur.state); cout<<endl;
    cout<<"EDIST: "<<newProblem.findEuclideanDistanceHeuristic(cur.state)<<endl;
    // std::set<stateObject> explored;
    // explored.insert(cur); //add leaf to explored state

    // for(int i=0; i<newProblem.numOperators; i++) //loop through all operators
    //     {
    //         int temp[3][3] = {  cur.state[0][0], cur.state[0][1], cur.state[0][2], //create a copy of cur
    //                             cur.state[1][0], cur.state[1][1], cur.state[1][2],
    //                             cur.state[2][0], cur.state[2][1], cur.state[2][2]
    //         };
    //         newProblem.Operators[i](temp);
    //         stateObject node = {{   temp[0][0], temp[0][1], temp[0][2], //initialize with temp
    //                                 temp[1][0], temp[1][1], temp[1][2],
    //                                 temp[2][0], temp[2][1], temp[2][2]
    //                             }, cur.cost+1}; // cur.cost+1 cost is just current cost+1 since this is uniform cost search (closest to initial first)
    //         if(node==cur){cout<<"SAME STATEOBJECT!!!"<<endl;}

    //         if((explored.find(node)==explored.end())){ //Only expand if not found inside explored set or frontier set
    //             cout<<"\tExpanding node with method "<<i<<endl;
    //         }
    //     }

    return 0;
}


int main() {
    problem *temp = new problem();
    
    UniformCostSearch(*temp);
    // AStarMisplacedTileSearch(*temp);
    // AStarEuclideanDistanceSearch(*temp);
    // test(*temp);
    return 0;
}

class Compare{
    public:
        bool operator()(stateObject s1, stateObject s2)
        {
            return s1.cost>s2.cost; //smaller first, s1<s2 for greater first
        }
};

class TestCompare{
    public:
        bool operator()(state s1, state s2)
        {
            return s1.cost>s2.cost; //smaller first, s1<s2 for greater first
        }
};

int UniformCostSearch(problem newProblem){
    int expandedNodes = 0;
    int maxQSize = 0;
    
    stateObject solution;

    std::priority_queue<stateObject, vector<stateObject>, Compare> frontier;
    std::set<stateObject> frontierSet; //set in order to keep track of states inside frontier

    stateObject init = {{newProblem.initialState[0][0], newProblem.initialState[0][1], newProblem.initialState[0][2], //initialize
                    newProblem.initialState[1][0], newProblem.initialState[1][1], newProblem.initialState[1][2],
                    newProblem.initialState[2][0], newProblem.initialState[2][1], newProblem.initialState[2][2]
                    }, 0, 0};

    frontier.push(init);
    frontierSet.insert(init);

    if (maxQSize<frontier.size()){maxQSize=frontier.size();}

    std::set<stateObject> explored; //initialize explored states as empty
    while(!frontier.empty()) 
    {
        // cout<<"Queue: "<<endl;
        // for (auto it=frontierSet.begin(); it != frontierSet.end(); ++it){
        //     newProblem.displayState(it->state);
        //     cout<<"COST: "<<it->cost<<endl;
        // }
        // cout<<endl;     

        stateObject cur = frontier.top();
        frontier.pop();
        for (auto it=frontierSet.begin(); it != frontierSet.end();)
        {
            if(cur==*it){it=frontierSet.erase(it);}else{++it;};
        }

        //GOAL TEST
        if(newProblem.findMisplacedTilesCNT(cur.state)==0)
        {
            solution = cur; //solution found
            cout<<"\tSolution Found!"<<endl; 
            cout<<"Search Review: "<<endl;
            cout<<"\tNodes Expanded: "<<expandedNodes<<endl;
            cout<<"\tMaximum Queue Size: "<<maxQSize<<endl;
            cout<<"\tSolution Depth: "<<solution.depth<<endl;
            return 0;
        } 
        //

        cout<<"Current State: " << endl;
        newProblem.displayState(cur.state);
        cout<<"With cost of "<<cur.cost<<endl;
        
        explored.insert(cur); //add leaf to explored state

        // cout<<"\n--------EXPLORED SET: --------------"<<endl;
        // for (auto it=explored.begin(); it != explored.end(); ++it){
        //     newProblem.displayState(it->state);
        //     cout<<"COST: "<<it->cost<<endl;
        //     cout<<endl;
        // }
        // cout<<"-------------------"<<endl;
        // cout<<endl;  

        bool expanded = false; //bool to check if node was expanded
        for(int i=0; i<newProblem.numOperators; i++) //loop through all operators
        {
            int temp[3][3] = {  cur.state[0][0], cur.state[0][1], cur.state[0][2], //create a copy of cur
                                cur.state[1][0], cur.state[1][1], cur.state[1][2],
                                cur.state[2][0], cur.state[2][1], cur.state[2][2]
            };
            newProblem.Operators[i](temp);
            stateObject node = {{   temp[0][0], temp[0][1], temp[0][2], //initialize with temp
                                    temp[1][0], temp[1][1], temp[1][2],
                                    temp[2][0], temp[2][1], temp[2][2]
                                }, cur.cost+1, cur.depth+1}; // cur.cost+1 cost is just current cost+1 since this is uniform cost search (closest to initial first)

                bool isExplored = false;
                for (auto it=explored.begin(); it != explored.end(); ++it){
                    if(node==*it){isExplored=true;};
                }
                bool isInFrontier = false;
                for (auto it=frontierSet.begin(); it != frontierSet.end(); ++it){
                    if(node==*it){isInFrontier=true;};
                }


            //if((explored.find(node)==explored.end() && frontierSet.find(node)==frontierSet.end())){ //Only expand if not found inside explored set or frontier set
            if(!isExplored&&!isInFrontier){ //Only expand if not found inside explored set or frontier set
                cout<<"\tExpanding node with method "<<i<<endl;
                //newProblem.displayState(node.state);
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
    cout<<"\tSolution Depth: "<<solution.depth<<endl;
    return 0;
}

int AStarMisplacedTileSearch(problem newProblem){
    int expandedNodes = 0;
    int maxQSize = 0;
    
    stateObject solution;
    // vector<stateObject> solutionVector; 

    std::priority_queue<stateObject, vector<stateObject>, Compare> frontier; //priority queue
    std::set<stateObject> frontierSet; //set in order to keep track of states inside frontier

    stateObject init = {{newProblem.initialState[0][0], newProblem.initialState[0][1], newProblem.initialState[0][2], //initialize
                    newProblem.initialState[1][0], newProblem.initialState[1][1], newProblem.initialState[1][2],
                    newProblem.initialState[2][0], newProblem.initialState[2][1], newProblem.initialState[2][2]
                    }, newProblem.findMisplacedTilesCNT(init.state), 0};

    frontier.push(init);
    frontierSet.insert(init);

    if (maxQSize<frontier.size()){maxQSize=frontier.size();}

    std::set<stateObject> explored; //initialize explored states as empty
    while(!frontier.empty()) 
    { 
        // cout<<"Queue: "<<endl;
        // for (auto it=frontierSet.begin(); it != frontierSet.end(); ++it){
        //     newProblem.displayState(it->state);
        //     cout<<"COST: "<<it->cost<<endl;
        // }
        // cout<<endl;    

        stateObject cur = frontier.top();
        frontier.pop();
        // frontierSet.erase(cur);
        for (auto it=frontierSet.begin(); it != frontierSet.end();)
        {
            if(cur==*it){it=frontierSet.erase(it);}else{++it;};
        }

        cout<<"Current State: " << endl;
        newProblem.displayState(cur.state);
        cout<<"With cost of "<<cur.cost<<endl;
        
        explored.insert(cur); //add leaf to explored state

        //GOAL TEST
        if(newProblem.findMisplacedTilesCNT(cur.state)==0)
        {
            solution = cur; //solution found
            // solutionVector.push_back(cur);
            cout<<"\tSolution Found!"<<endl; 
            cout<<"Search Review: "<<endl;
            cout<<"\tNodes Expanded: "<<expandedNodes<<endl;
            cout<<"\tMaximum Queue Size: "<<maxQSize<<endl;
            cout<<"\tSolution Depth: "<<solution.depth<<endl;
            return 0;
        } 
        //

        // cout<<"\n--------EXPLORED SET: --------------"<<endl;
        // for (auto it=explored.begin(); it != explored.end(); ++it){
        //     newProblem.displayState(it->state);
        //     cout<<"COST: "<<it->cost<<endl;
        //     cout<<endl;
        // }
        // cout<<"-------------------"<<endl;
        // cout<<endl;  

        bool expanded = false; //bool to check if node was expanded
        for(int i=0; i<newProblem.numOperators; i++) //loop through all operators
        {
            int temp[3][3] = {  cur.state[0][0], cur.state[0][1], cur.state[0][2], //create a copy of cur
                                cur.state[1][0], cur.state[1][1], cur.state[1][2],
                                cur.state[2][0], cur.state[2][1], cur.state[2][2]
            };
            newProblem.Operators[i](temp);
            stateObject node = {{   temp[0][0], temp[0][1], temp[0][2], //initialize with temp
                                    temp[1][0], temp[1][1], temp[1][2],
                                    temp[2][0], temp[2][1], temp[2][2]
                                }, newProblem.findMisplacedTilesCNT(temp)+cur.depth+1, cur.depth+1}; // cur.cost+1 cost is just current cost+1 since this is uniform cost search (closest to initial first)

                bool isExplored = false;
                for (auto it=explored.begin(); it != explored.end(); ++it){
                    if(node==*it){isExplored=true;};
                }
                bool isInFrontier = false;
                for (auto it=frontierSet.begin(); it != frontierSet.end(); ++it){
                    if(node==*it){isInFrontier=true;};
                }


            //if((explored.find(node)==explored.end() && frontierSet.find(node)==frontierSet.end())){ //Only expand if not found inside explored set or frontier set
            if(!isExplored&&!isInFrontier){ //Only expand if not found inside explored set or frontier set
                cout<<"\tExpanding node with method "<<i<<endl;
                //newProblem.displayState(node.state);
                frontier.push(node); 
                frontierSet.insert(node);
                expanded = true;
            }
        }

        cout<<"FRONTIER SIZE: "<<frontier.size()<<endl;
        if (maxQSize<frontier.size()){maxQSize=frontier.size();}

        if (expanded){expandedNodes++;}
        cout<<"\n";
    }

    cout<<"Search Review: "<<endl;
    cout<<"\tNodes Expanded: "<<expandedNodes<<endl;
    cout<<"\tMaximum Queue Size: "<<maxQSize<<endl;
    cout<<"\tSolution Depth: "<<solution.depth<<endl;
    // for(int i=0; i<solutionVector.size(); i++){
    //     cout<<"\tSolution Depth #"<<i<<": "<<solutionVector[i].cost<<endl;
    // }
    return 0;
}

int AStarEuclideanDistanceSearch(problem newProblem){
    int expandedNodes = 0;
    int maxQSize = 0;
    
    stateObject solution;
    // vector<stateObject> solutionVector; 

    std::priority_queue<stateObject, vector<stateObject>, Compare> frontier; //priority queue
    std::set<stateObject> frontierSet; //set in order to keep track of states inside frontier

    stateObject init = {{newProblem.initialState[0][0], newProblem.initialState[0][1], newProblem.initialState[0][2], //initialize
                    newProblem.initialState[1][0], newProblem.initialState[1][1], newProblem.initialState[1][2],
                    newProblem.initialState[2][0], newProblem.initialState[2][1], newProblem.initialState[2][2]
                    }, newProblem.findMisplacedTilesCNT(init.state), 0};

    frontier.push(init);
    frontierSet.insert(init);

    if (maxQSize<frontier.size()){maxQSize=frontier.size();}

    std::set<stateObject> explored; //initialize explored states as empty
    while(!frontier.empty()) 
    { 
        // cout<<"Queue: "<<endl;
        // for (auto it=frontierSet.begin(); it != frontierSet.end(); ++it){
        //     newProblem.displayState(it->state);
        //     cout<<"COST: "<<it->cost<<endl;
        // }
        // cout<<endl;    

        stateObject cur = frontier.top();
        frontier.pop();
        // frontierSet.erase(cur);
        for (auto it=frontierSet.begin(); it != frontierSet.end();)
        {
            if(cur==*it){it=frontierSet.erase(it);}else{++it;};
        }

        cout<<"Current State: " << endl;
        newProblem.displayState(cur.state);
        cout<<"With cost of "<<cur.cost<<endl;
        
        explored.insert(cur); //add leaf to explored state

        //GOAL TEST
        if(newProblem.findMisplacedTilesCNT(cur.state)==0)
        {
            solution = cur; //solution found
            // solutionVector.push_back(cur);
            cout<<"\tSolution Found!"<<endl; 
            cout<<"Search Review: "<<endl;
            cout<<"\tNodes Expanded: "<<expandedNodes<<endl;
            cout<<"\tMaximum Queue Size: "<<maxQSize<<endl;
            cout<<"\tSolution Depth: "<<solution.depth<<endl;
            return 0;
        } 
        //

        // cout<<"\n--------EXPLORED SET: --------------"<<endl;
        // for (auto it=explored.begin(); it != explored.end(); ++it){
        //     newProblem.displayState(it->state);
        //     cout<<"COST: "<<it->cost<<endl;
        //     cout<<endl;
        // }
        // cout<<"-------------------"<<endl;
        // cout<<endl;  

        bool expanded = false; //bool to check if node was expanded
        for(int i=0; i<newProblem.numOperators; i++) //loop through all operators
        {
            int temp[3][3] = {  cur.state[0][0], cur.state[0][1], cur.state[0][2], //create a copy of cur
                                cur.state[1][0], cur.state[1][1], cur.state[1][2],
                                cur.state[2][0], cur.state[2][1], cur.state[2][2]
            };
            newProblem.Operators[i](temp);
            stateObject node = {{   temp[0][0], temp[0][1], temp[0][2], //initialize with temp
                                    temp[1][0], temp[1][1], temp[1][2],
                                    temp[2][0], temp[2][1], temp[2][2]
                                }, newProblem.findEuclideanDistanceHeuristic(temp)+cur.depth+1, cur.depth+1}; // cur.cost+1 cost is just current cost+1 since this is uniform cost search (closest to initial first)

                bool isExplored = false;
                for (auto it=explored.begin(); it != explored.end(); ++it){
                    if(node==*it){isExplored=true;};
                }
                bool isInFrontier = false;
                for (auto it=frontierSet.begin(); it != frontierSet.end(); ++it){
                    if(node==*it){isInFrontier=true;};
                }


            //if((explored.find(node)==explored.end() && frontierSet.find(node)==frontierSet.end())){ //Only expand if not found inside explored set or frontier set
            if(!isExplored&&!isInFrontier){ //Only expand if not found inside explored set or frontier set
                cout<<"\tExpanding node with method "<<i<<endl;
                //newProblem.displayState(node.state);
                frontier.push(node); 
                frontierSet.insert(node);
                expanded = true;
            }
        }
        
        cout<<"FRONTIER SIZE: "<<frontier.size()<<endl;
        if (maxQSize<frontier.size()){maxQSize=frontier.size();}

        if (expanded){expandedNodes++;}
        cout<<"\n";
    }

    cout<<"Search Review: "<<endl;
    cout<<"\tNodes Expanded: "<<expandedNodes<<endl;
    cout<<"\tMaximum Queue Size: "<<maxQSize<<endl;
    cout<<"\tSolution Depth: "<<solution.depth<<endl;
    // for(int i=0; i<solutionVector.size(); i++){
    //     cout<<"\tSolution Depth #"<<i<<": "<<solutionVector[i].cost<<endl;
    // }
    return 0;
}




int TestUniformCostSearch(problem newProblem){
    int expandedNodes = 0;
    int maxQSize = 0;
    
    state solution;

    std::priority_queue<state, vector<state>, TestCompare> frontier;
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
        for(int i=0; i<newProblem.numTestOperators; i++) //loop through all operators
        {
            state node = {newProblem.TestOperators[i](cur.val), cur.cost+1}; //cost is just current cost+1 since this is uniform cost search (closest to initial first)
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
