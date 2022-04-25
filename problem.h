#ifndef PROBLEM_H
#define PROBLEM_H
#include <stdlib.h>
#include <iostream>

using namespace std;

int t1(int state);
int t2(int state);

class problem{
    public:
        int initialState[3][3];
        int goalState[3][3];
        problem();

        void moveUp();
        void moveDown();
        void moveLeft();
        void moveRight();

        int init = 0;
        int goal = 10;
        int test1(int state){if (state<goal){return state+1;} else return state;}
        int test2(int state){if (state<goal){return state*2;} else return state;}
        
        typedef int (*OperatorFunctions) (int state);
        int numOperators = 2;
        OperatorFunctions Operators[2] = {t1, t2};
};

#endif
