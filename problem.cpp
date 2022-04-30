#include "problem.h"

using namespace std;

int t1(int state){if (state<10){return state+1;} else return state;}
int t2(int state){if (state<10){return state*2;} else return state;}

std::pair<int, int> getSpaceLocation(int state[3][3]){
    try{
    for (int r = 0; r < 3; r++)
    {
        for (int c = 0; c < 3; c++)
        {
            if(state[r][c] == 0)
            {
                return std::make_pair(r,c);
            }
        }
    }
    }
    catch(exception err){
        cout<<"\tPuzzle does not have a 0!"<<endl;
    }
    return std::make_pair(0,0);
}

int* moveUp(int state[3][3]){
    std::pair<int,int> space = getSpaceLocation(state);
    if (space.first!=0)
    {
        int temp = state[space.first-1][space.second]; //swap
        state[space.first-1][space.second] = state[space.first][space.second];
        state[space.first][space.second] = temp;
    }
    else
    {
        // cout<<"\tCan't move up!"<<endl;
    }
    return 0;
}

int* moveDown(int state[3][3]){
    std::pair<int,int> space = getSpaceLocation(state);
    if (space.first!=2)
    {
        int temp = state[space.first+1][space.second]; //swap
        state[space.first+1][space.second] = state[space.first][space.second];
        state[space.first][space.second] = temp;
    }
    else
    {
        // cout<<"\tCan't move down!"<<endl;
    }
    return 0;
}

int* moveRight(int state[3][3]){
    std::pair<int,int> space = getSpaceLocation(state);
    if (space.second!=2)
    {
        int temp = state[space.first][space.second+1]; //swap
        state[space.first][space.second+1] = state[space.first][space.second];
        state[space.first][space.second] = temp;
    }
    else
    {
        // cout<<"\tCan't move right!"<<endl;
    }
    return 0;
}

int* moveLeft(int state[3][3]){
    std::pair<int,int> space = getSpaceLocation(state);
    if (space.second!=0)
    {
        int temp = state[space.first][space.second-1]; //swap
        state[space.first][space.second-1] = state[space.first][space.second];
        state[space.first][space.second] = temp;
    }
    else
    {
        // cout<<"\tCan't move left!"<<endl;
    }
    return 0;
}

problem::problem()
{   
    //SET INITIAL
    cout<<"Pick a default puzzle: "<<endl;
    cout<<"1. Trivial"<<endl;
    cout<<"2. Very Easy"<<endl;
    cout<<"3. Easy"<<endl;
    cout<<"4. Doable"<<endl;
    cout<<"5. Oh Boy"<<endl;
    cout<<"6. Impossible"<<endl;

    int num;
    cin>>num;

    switch (num)
    {
    case 1:
        //Trivial
        initialState[0][0]=1;
        initialState[0][1]=2;
        initialState[0][2]=3;
        
        initialState[1][0]=4;
        initialState[1][1]=5;
        initialState[1][2]=6;

        initialState[2][0]=7;
        initialState[2][1]=8;
        initialState[2][2]=0;
        break;
    case 2:
        //Very Easy
        initialState[0][0]=1;
        initialState[0][1]=2;
        initialState[0][2]=3;
        
        initialState[1][0]=4;
        initialState[1][1]=5;
        initialState[1][2]=6;

        initialState[2][0]=7;
        initialState[2][1]=0;
        initialState[2][2]=8;
        break;
    case 3:
        //Easy
        initialState[0][0]=1;
        initialState[0][1]=2;
        initialState[0][2]=0;
        
        initialState[1][0]=4;
        initialState[1][1]=5;
        initialState[1][2]=3;

        initialState[2][0]=7;
        initialState[2][1]=8;
        initialState[2][2]=6;
        break;
    case 4:
        //Doable
        initialState[0][0]=0;
        initialState[0][1]=1;
        initialState[0][2]=2;
        
        initialState[1][0]=4;
        initialState[1][1]=5;
        initialState[1][2]=3;

        initialState[2][0]=7;
        initialState[2][1]=8;
        initialState[2][2]=6;
        break;
    case 5:
        //Oh Boy
        initialState[0][0]=8;
        initialState[0][1]=7;
        initialState[0][2]=1;
        
        initialState[1][0]=6;
        initialState[1][1]=0;
        initialState[1][2]=2;

        initialState[2][0]=5;
        initialState[2][1]=4;
        initialState[2][2]=3;
        break;
    case 6:
        //Impossible
        initialState[0][0]=1;
        initialState[0][1]=2;
        initialState[0][2]=3;
        
        initialState[1][0]=4;
        initialState[1][1]=5;
        initialState[1][2]=6;

        initialState[2][0]=8;
        initialState[2][1]=7;
        initialState[2][2]=0;
        break;
    
    default:
        break;
    }

    ////////////////// SET GOAL
    
    goalState[0][0]=1;
    goalState[0][1]=2;
    goalState[0][2]=3;
    
    goalState[1][0]=4;
    goalState[1][1]=5;
    goalState[1][2]=6;

    goalState[2][0]=7;
    goalState[2][1]=8;
    goalState[2][2]=0;
}

problem::problem(int init[3][3])
{   
    // SET INITIAL
    initialState[0][0]=init[0][0];
    initialState[0][1]=init[0][1];
    initialState[0][2]=init[0][2];
    
    initialState[1][0]=init[1][0];
    initialState[1][1]=init[1][1];
    initialState[1][2]=init[1][2];

    initialState[2][0]=init[2][0];
    initialState[2][1]=init[2][1];
    initialState[2][2]=init[2][2];

    ////////////////// SET GOAL
    
    goalState[0][0]=1;
    goalState[0][1]=2;
    goalState[0][2]=3;
    
    goalState[1][0]=4;
    goalState[1][1]=5;
    goalState[1][2]=6;

    goalState[2][0]=7;
    goalState[2][1]=8;
    goalState[2][2]=0;
}

void problem::displayState(const int state[3][3]){
    for (int r = 0; r < 3; r++)
    {
        for (int c = 0; c < 3; c++)
        {
            cout<<state[r][c]<<" ";
        }
        cout<<endl;
    }
}

int problem::findMisplacedTilesCNT(int state[3][3]){
    int misplacedTileCnt = 0;
    for (int r = 0; r < 3; r++)
    {
        for (int c = 0; c < 3; c++)
        {
            if(state[r][c]!=goalState[r][c]){
                misplacedTileCnt++;
            }
        }
    }
    return misplacedTileCnt;
}

std::pair<int, int> getLocation(int n, int state[3][3]){
    try{
    for (int r = 0; r < 3; r++)
    {
        for (int c = 0; c < 3; c++)
        {
            if(state[r][c] == n)
            {
                return std::make_pair(r,c);
            }
        }
    }
    }
    catch(exception err){
        cout<<"\tCant find!"<<endl;
    }
    return std::make_pair(0,0);
}

double problem::findEuclideanDistance(int x,int y, int state[3][3]){
    if(state[x][y]!=goalState[x][y]){
        std::pair<int,int> goallocation = getLocation(state[x][y], goalState);
        // cout<<goallocation.first-x<<", "<<goallocation.second-y<<";    ";
        // cout<<pow(goallocation.first-x, 2)<<", "<<pow(goallocation.second-y,2)<<endl;
        // cout<<endl;
        // cout<<"state: "<<state[x][y]<<", " <<sqrt(pow(goallocation.first-x, 2) + pow(goallocation.second-y,2)) <<endl;
        return sqrt(pow(goallocation.first-x, 2) + pow(goallocation.second-y,2));
    }
    else{
        return 0;
    }
}

double problem::findEuclideanDistanceHeuristic(int state[3][3]){
    double total=0;
    for (int r = 0; r < 3; r++)
    {
        for (int c = 0; c < 3; c++)
        {
            total+=findEuclideanDistance(r,c,state);
        }
    }
    return total; 
}