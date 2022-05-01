#include <iostream>
#include <queue>
#include <set>
#include <vector>

#include "problem.h"

//Resources
// https://en.cppreference.com/w/cpp/container/set/find
// https://stackoverflow.com/questions/15601973/stl-priority-queue-of-c-with-struct
// https://stackoverflow.com/questions/2874441/deleting-elements-from-stdset-while-iterating

using std::cin;
using std::cout;
using std::endl;

int UniformCostSearch(problem);
int AStarMisplacedTileSearch(problem);
int AStarEuclideanDistanceSearch(problem);

struct stateObject{ //object to store an array state of a puzzle, cost and depth
    int state[3][3]; // array state
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

int main() {

    cout<<"Welcome to 862151198 8 Puzzle Solver."<<"\nType 1 to use a default puzzle or Type 2 to enter your own puzzle."<<endl;
    int puzzleChoice; 
    cin>>puzzleChoice;

    cout<<endl;
    problem *problemObject;
    switch (puzzleChoice)
    {
    case 1:
        problemObject = new problem();
        break;
    case 2:
        cout<<"Enter your puzzle using a 0 to represent a blank space and with spaces between numbers"<<endl;
        int inputArr[3][3];
    	for(int i=0; i<3;i++){
            cout<<"Enter row "<< i+1 <<": "<<endl;
            for (int j =0; j<3; j++) 
            {
                int num;
                cin>>num;
                inputArr[i][j]=num;
                if (cin.peek()==' ') //check for space
                {cin.ignore();}
            }
        }
        cout<<"\nYour Custom Puzzle:"<<endl;
        problemObject->displayState(inputArr);
        problemObject = new problem(inputArr);
        break;
    
    default:
        cout<<"Please Enter a valid choice!"<<endl;
        break;
    }
    cout<<endl;

    cout<<"Enter your choice of an algorithm:"<<endl;
    cout<<"1. Uniform Cost Search"<<endl;
    cout<<"2. A* Search with Misplaced Tile Heuristic"<<endl;
    cout<<"3. A* Search with Euclidean Distance Heuristic"<<endl;
    int algorithmChoice;
    cin>>algorithmChoice; cout<<endl;

    switch (algorithmChoice)
    {
    case 1:
        UniformCostSearch(*problemObject);
        break;
    case 2:
        AStarMisplacedTileSearch(*problemObject);
        break;
    case 3:
        AStarEuclideanDistanceSearch(*problemObject);
        break;
    
    default:
        cout<<"Please Enter a valid choice!"<<endl;
        break;
    }
    return 0;
}

class Compare{ //comparator class for use with the priority queue frontier
    public:
        bool operator()(stateObject s1, stateObject s2)
        {
            return s1.cost>s2.cost; //smaller first, s1<s2 for greater first
        }
};

int UniformCostSearch(problem newProblem){
    int expandedNodes = 0;
    int maxQSize = 0;
    
    stateObject solution; 

    std::priority_queue<stateObject, std::vector<stateObject>, Compare> frontier; //frontier priority queue
    std::set<stateObject> frontierSet; //set in order to keep track of states inside frontier

    //initialize frontier
    stateObject init = {{newProblem.initialState[0][0], newProblem.initialState[0][1], newProblem.initialState[0][2], //initialize
                    newProblem.initialState[1][0], newProblem.initialState[1][1], newProblem.initialState[1][2],
                    newProblem.initialState[2][0], newProblem.initialState[2][1], newProblem.initialState[2][2]
                    }, 0, 0};
    frontier.push(init);
    frontierSet.insert(init);

    if (maxQSize<frontier.size()){maxQSize=frontier.size();} // update max queue size if current size is larger

    std::set<stateObject> explored; //initialize explored states as empty
    while(!frontier.empty()) 
    {   

        // get a state from the frontier
        stateObject cur = frontier.top();
        frontier.pop();
        for (auto it=frontierSet.begin(); it != frontierSet.end();)
        {
            if(cur==*it){it=frontierSet.erase(it);}else{++it;};
        }

        cout<<"State to Expand: " << endl;
        newProblem.displayState(cur.state);
        cout<<"With cost of "<<cur.cost<<endl;
        
        //GOAL TEST
        if(newProblem.findMisplacedTilesCNT(cur.state)==0)
        {
            solution = cur; //solution found
            cout<<endl;
            cout<<"Solution Found!"<<endl; 
            cout<<"Search Review: "<<endl;
            cout<<"\tNodes Expanded: "<<expandedNodes<<endl;
            cout<<"\tMaximum Queue Size: "<<maxQSize<<endl;
            cout<<"\tSolution Depth: "<<solution.depth<<endl;
            return 0;
        } 
        //

        explored.insert(cur); //add leaf to explored state

        bool expanded = false; //bool to check if node was expanded
        for(int i=0; i<newProblem.numOperators; i++) //loop through all operators
        {
            int temp[3][3] = {  cur.state[0][0], cur.state[0][1], cur.state[0][2], //create a copy of cur
                                cur.state[1][0], cur.state[1][1], cur.state[1][2],
                                cur.state[2][0], cur.state[2][1], cur.state[2][2]
            };
            newProblem.Operators[i](temp); //perform operation
            stateObject node = {{   temp[0][0], temp[0][1], temp[0][2], //initialize with temp
                                    temp[1][0], temp[1][1], temp[1][2],
                                    temp[2][0], temp[2][1], temp[2][2]
                                }, cur.cost+1, cur.depth+1}; // cur.cost+1 cost is just current cost+1 since this is uniform cost search (closest to initial first)

                //check if explored is in frontier
                bool isExplored = false;
                for (auto it=explored.begin(); it != explored.end(); ++it){
                    if(node==*it){isExplored=true;};
                }
                bool isInFrontier = false;
                for (auto it=frontierSet.begin(); it != frontierSet.end(); ++it){
                    if(node==*it){isInFrontier=true;};
                }
            if(!isExplored&&!isInFrontier){ //Only expand if not found inside explored set or frontier set

                frontier.push(node); 
                frontierSet.insert(node);

                if (maxQSize<frontier.size()){maxQSize=frontier.size();}
                expanded = true;
            }
        }

        if (expanded){
            cout<<"Expanding..."<<endl;
            expandedNodes++;
            }
        cout<<"\n";
    }

    cout<<"Search Review: "<<endl;
    cout<<"\tNodes Expanded: "<<expandedNodes<<endl;
    cout<<"\tMaximum Queue Size: "<<maxQSize<<endl;
    cout<<"\tNo Solution found"<<endl;
    return 0;
}

int AStarMisplacedTileSearch(problem newProblem){
    int expandedNodes = 0;
    int maxQSize = 0;
    
    stateObject solution;

    std::priority_queue<stateObject, std::vector<stateObject>, Compare> frontier; //priority queue
    std::set<stateObject> frontierSet; //set in order to keep track of states inside frontier

    //initialize frontier
    stateObject init = {{newProblem.initialState[0][0], newProblem.initialState[0][1], newProblem.initialState[0][2], //initialize
                    newProblem.initialState[1][0], newProblem.initialState[1][1], newProblem.initialState[1][2],
                    newProblem.initialState[2][0], newProblem.initialState[2][1], newProblem.initialState[2][2]
                    }, newProblem.findMisplacedTilesCNT(init.state), 0};

    frontier.push(init);
    frontierSet.insert(init);

    if (maxQSize<frontier.size()){maxQSize=frontier.size();} // update max queue size if current size is larger

    std::set<stateObject> explored; //initialize explored states as empty
    while(!frontier.empty()) 
    { 
        // get a state from the frontier
        stateObject cur = frontier.top();
        frontier.pop();
        for (auto it=frontierSet.begin(); it != frontierSet.end();)
        {
            if(cur==*it){it=frontierSet.erase(it);}else{++it;};
        }

        cout<<"State To Expand: " << endl;
        newProblem.displayState(cur.state);
        cout<<"With a g(n) of "<<cur.depth<<" and a h(n) of "<<cur.cost-cur.depth<<" for a total cost of "<<cur.cost<<endl;
        
        explored.insert(cur); //add leaf to explored state

        //GOAL TEST
        if(newProblem.findMisplacedTilesCNT(cur.state)==0)
        {
            solution = cur; //solution found
            cout<<endl;
            cout<<"Solution Found!"<<endl; 
            cout<<"Search Review: "<<endl;
            cout<<"\tNodes Expanded: "<<expandedNodes<<endl;
            cout<<"\tMaximum Queue Size: "<<maxQSize<<endl;
            cout<<"\tSolution Depth: "<<solution.depth<<endl;
            return 0;
        } 
        //

        bool expanded = false; //bool to check if node was expanded
        for(int i=0; i<newProblem.numOperators; i++) //loop through all operators
        {
            int temp[3][3] = {  cur.state[0][0], cur.state[0][1], cur.state[0][2], //create a copy of cur
                                cur.state[1][0], cur.state[1][1], cur.state[1][2],
                                cur.state[2][0], cur.state[2][1], cur.state[2][2]
            };
            newProblem.Operators[i](temp); //perform operation
            stateObject node = {{   temp[0][0], temp[0][1], temp[0][2], //initialize with temp
                                    temp[1][0], temp[1][1], temp[1][2],
                                    temp[2][0], temp[2][1], temp[2][2]
                                }, newProblem.findMisplacedTilesCNT(temp)+cur.depth+1, cur.depth+1}; // cur.cost+1 cost is just current cost+1 since this is uniform cost search (closest to initial first)
                
                //check if explored is in frontier
                bool isExplored = false;
                for (auto it=explored.begin(); it != explored.end(); ++it){
                    if(node==*it){isExplored=true;};
                }
                bool isInFrontier = false;
                for (auto it=frontierSet.begin(); it != frontierSet.end(); ++it){
                    if(node==*it){isInFrontier=true;};
                }

            if(!isExplored&&!isInFrontier){ //Only expand if not found inside explored set or frontier set
                frontier.push(node); 
                frontierSet.insert(node);
                expanded = true;
            }
        }
        if (maxQSize<frontier.size()){maxQSize=frontier.size();}

        if (expanded){
            cout<<"Expanding..."<<endl;
            expandedNodes++;
            }
        cout<<"\n";
    }

    cout<<"Search Review: "<<endl;
    cout<<"\tNodes Expanded: "<<expandedNodes<<endl;
    cout<<"\tMaximum Queue Size: "<<maxQSize<<endl;
    cout<<"\tNo Solution found"<<endl;
    return 0;
}

int AStarEuclideanDistanceSearch(problem newProblem){
    int expandedNodes = 0;
    int maxQSize = 0;
    
    stateObject solution;

    std::priority_queue<stateObject, std::vector<stateObject>, Compare> frontier; //priority queue
    std::set<stateObject> frontierSet; //set in order to keep track of states inside frontier

    //initialize frontier
    stateObject init = {{newProblem.initialState[0][0], newProblem.initialState[0][1], newProblem.initialState[0][2], //initialize
                    newProblem.initialState[1][0], newProblem.initialState[1][1], newProblem.initialState[1][2],
                    newProblem.initialState[2][0], newProblem.initialState[2][1], newProblem.initialState[2][2]
                    }, newProblem.findMisplacedTilesCNT(init.state), 0};
    frontier.push(init);
    frontierSet.insert(init);

    if (maxQSize<frontier.size()){maxQSize=frontier.size();} // update max queue size if current size is larger

    std::set<stateObject> explored; //initialize explored states as empty
    while(!frontier.empty()) 
    {  
        // get a state from the frontier
        stateObject cur = frontier.top();
        frontier.pop();
        for (auto it=frontierSet.begin(); it != frontierSet.end();)
        {
            if(cur==*it){it=frontierSet.erase(it);}else{++it;};
        }

        cout<<"State to Expand: " << endl;
        newProblem.displayState(cur.state);
        cout<<"With a g(n) of "<<cur.depth<<" and a h(n) of "<<cur.cost-cur.depth<<" for a total cost of "<<cur.cost<<endl;
        
        explored.insert(cur); //add leaf to explored state

        //GOAL TEST
        if(newProblem.findMisplacedTilesCNT(cur.state)==0)
        {
            solution = cur; //solution found
            cout<<endl;
            cout<<"Solution Found!"<<endl; 
            cout<<"Search Review: "<<endl;
            cout<<"\tNodes Expanded: "<<expandedNodes<<endl;
            cout<<"\tMaximum Queue Size: "<<maxQSize<<endl;
            cout<<"\tSolution Depth: "<<solution.depth<<endl;
            return 0;
        } 
        //

        bool expanded = false; //bool to check if node was expanded
        for(int i=0; i<newProblem.numOperators; i++) //loop through all operators
        {
            int temp[3][3] = {  cur.state[0][0], cur.state[0][1], cur.state[0][2], //create a copy of cur
                                cur.state[1][0], cur.state[1][1], cur.state[1][2],
                                cur.state[2][0], cur.state[2][1], cur.state[2][2]
            };
            newProblem.Operators[i](temp); //perform operation
            stateObject node = {{   temp[0][0], temp[0][1], temp[0][2], //initialize with temp
                                    temp[1][0], temp[1][1], temp[1][2],
                                    temp[2][0], temp[2][1], temp[2][2]
                                }, int(newProblem.findEuclideanDistanceHeuristic(temp))+cur.depth+1, cur.depth+1}; // cur.cost+1 cost is just current cost+1 since this is uniform cost search (closest to initial first)

                //check if explored is in frontier
                bool isExplored = false;
                for (auto it=explored.begin(); it != explored.end(); ++it){
                    if(node==*it){isExplored=true;};
                }
                bool isInFrontier = false;
                for (auto it=frontierSet.begin(); it != frontierSet.end(); ++it){
                    if(node==*it){isInFrontier=true;};
                }


            if(!isExplored&&!isInFrontier){ //Only expand if not found inside explored set or frontier set
                frontier.push(node); 
                frontierSet.insert(node);
                expanded = true;
            }
        }
        
        if (maxQSize<frontier.size()){maxQSize=frontier.size();}

        if (expanded){
            cout<<"Expanding..."<<endl;
            expandedNodes++;
            }
        cout<<"\n";
    }

    cout<<"Search Review: "<<endl;
    cout<<"\tNodes Expanded: "<<expandedNodes<<endl;
    cout<<"\tMaximum Queue Size: "<<maxQSize<<endl;
    cout<<"\tNo Solution found"<<endl;
    return 0;
}
