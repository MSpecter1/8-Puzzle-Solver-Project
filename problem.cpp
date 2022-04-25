#include "problem.h"

using namespace std;

int t1(int state){if (state<10){return state+1;} else return state;}
int t2(int state){if (state<10){return state*2;} else return state;}

problem::problem()
{
    initialState[0][0]=1;
    initialState[0][1]=2;
    initialState[0][2]=0;
    
    initialState[1][0]=4;
    initialState[1][1]=5;
    initialState[1][2]=3;

    initialState[2][0]=7;
    initialState[2][1]=8;
    initialState[2][2]=6;

    //////////////////
    
    goalState[0][0]=1;
    goalState[0][1]=2;
    goalState[0][2]=3;
    
    goalState[1][0]=4;
    initialState[1][1]=5;
    initialState[1][2]=6;

    initialState[2][0]=7;
    initialState[2][1]=8;
    initialState[2][2]=0;
}
